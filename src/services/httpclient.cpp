#include "httpclient.h"

#include <QBuffer>
#include <QFile>
#include <QUrlQuery>

HttpClient::HttpClient(QObject* parent)
    : QObject(parent)
    , m_networkManager(new QNetworkAccessManager(this))
{
    QObject::connect(m_networkManager, &QNetworkAccessManager::finished, this, &HttpClient::onResponseReceived);
}

void HttpClient::initiateRequest(RequestPtr request)
{
    qDebug() << "Initiating a request to " << request->url();

    request->setLoading(true);

    QNetworkRequest nr;
    QElapsedTimer timer;
    timer.start();
    request->setRequestTimer(timer);
    nr.setAttribute(QNetworkRequest::User, QVariant::fromValue(request));
    nr.setAttribute(QNetworkRequest::FollowRedirectsAttribute, true);
    nr.setMaximumRedirectsAllowed(10);

    for (auto&& h : request->headers()->paramList()) {
        if (h.key().isEmpty() && h.value().isEmpty())
            continue;

        nr.setRawHeader(h.key().toUtf8(), h.value().toUtf8());
    }

    nr.setUrl(request->url());

    // We may need to switch to the qiodevice api when we support binary file uploads.
    QIODevice* body = nullptr;

    switch (request->activeBody()) {
    case Request::RequestBody::None:
        break;
    case Request::RequestBody::Raw: {
        auto bts = new QByteArray();
        *bts = request->body().toUtf8();
        body = new QBuffer(bts, this);
        break;
    }
    case Request::RequestBody::Form: {
        // TODO: This probably doesn't correctly handle multipart form data.
        auto bts = new QByteArray();
        *bts = request->bodyForm()->urlEncode().toUtf8();
        body = new QBuffer(bts, this);
        break;
    }
    case Request::RequestBody::UrlEncoded: {
        auto bts = new QByteArray();
        *bts = request->bodyUrlEncoded()->urlEncode().toUtf8();
        body = new QBuffer(bts, this);
        break;
    }
    case Request::RequestBody::Binary: {
        try {
            auto file = new QFile(request->bodyBinary(), this);
            file->open(QIODevice::ReadOnly);
            body = file;
        } catch (std::exception& e) {
            qWarning() << "Failed to open binary file " << e.what();
        }
        break;
    }
    }

    request->setNetworkReply(m_networkManager->sendCustomRequest(nr, request->method().toUtf8(), body));
}

// TODO: Store responses in /tmp file system
void HttpClient::onResponseReceived(QNetworkReply* reply)
{

    auto v = reply->request().attribute(QNetworkRequest::User);
    auto req = v.value<RequestPtr>();

    req->setLoading(false);

    ResponsePtr res(new Response(req.toWeakRef(), req.get()));
    res->setResponseTime(req->requestTimer().nsecsElapsed());

    // Show content based errors.
    if (reply->error() >= QNetworkReply::ConnectionRefusedError && reply->error() <= QNetworkReply::UnknownProxyError) {

        qWarning() << reply->errorString();
        res->setContentType("text/plain; charset=UTF-8");
        res->setBody("Error: " + reply->errorString().toUtf8());
        emit responseReceived(res);
        return;
    }

    auto answer = reply->readAll();

    QList<QPair<QString, QString>> headers;
    for (const auto& p : reply->rawHeaderPairs())
        headers.append(QPair<QString, QString>(p.first, p.second));

    auto ct = reply->header(QNetworkRequest::ContentTypeHeader);
    if (!ct.isNull())
        res->setContentType(ct.toString());

    auto status = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
    res->setStatusCode(status);
    auto statusLine = reply->attribute(QNetworkRequest::HttpReasonPhraseAttribute).toString();
    res->setStatusLine(statusLine);

    res->setHeaders(headers);
    res->setBody(answer);
    req->setResponse(res);
    emit responseReceived(res);
}
