#include "httpclient.h"

HttpClient::HttpClient(QObject *parent) : QObject(parent)
  , m_networkManager(new QNetworkAccessManager(this))
{
    QObject::connect(m_networkManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(onResponseReceived(QNetworkReply*)));
}

void HttpClient::initiateRequest(RequestPtr request)
{
    qDebug() << "Initiating a request to " << request->url();

    QNetworkRequest nr;
    request->setStartRequestTime(QDateTime::currentDateTimeUtc());
    nr.setAttribute(QNetworkRequest::User, QVariant::fromValue(request));
    nr.setAttribute(QNetworkRequest::FollowRedirectsAttribute, true);
    nr.setMaximumRedirectsAllowed(10);
    nr.setUrl(request->url());
    m_networkManager->sendCustomRequest(nr, request->method().toUtf8());
}

// TODO: Store responses in /tmp file system
void HttpClient::onResponseReceived(QNetworkReply *reply)
{
    auto v = reply->request().attribute(QNetworkRequest::User);
    auto req = v.value<RequestPtr>();
    ResponsePtr res(new Response(req.toWeakRef(), req.get()));
    QDateTime now(QDateTime::currentDateTimeUtc());
    res->setResponseTime(req->startRequestTime().msecsTo(now));

    if (reply->error()) {
        qWarning() << reply->errorString();
        res->setBody("Error: " + reply->errorString().toUtf8());
        emit responseReceived(res);
        return;
    }

    auto answer = reply->readAll();

    QList<QPair<QString, QString>> headers;
    for (const auto &p : reply->rawHeaderPairs())
        headers.append(QPair<QString, QString>(p.first, p.second));

    auto ct = reply->header(QNetworkRequest::ContentTypeHeader);
    if (!ct.isNull()) res->setContentType(ct.toString());

    res->setHeaders(headers);
    res->setBody(answer);
    req->setResponse(res);
    emit responseReceived(res);
}
