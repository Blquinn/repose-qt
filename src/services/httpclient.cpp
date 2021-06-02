#include "httpclient.h"

HttpClient::HttpClient(QObject *parent) : QObject(parent)
  , m_networkManager(new QNetworkAccessManager(this))
{
    QObject::connect(m_networkManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(onResponseReceived(QNetworkReply*)));
}

void HttpClient::initiateRequest(Request *request)
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
    // TODO: Handle errors.
    if (reply->error()) {
        qDebug() << reply->errorString();
        return;
    }

    QObject *obj = qvariant_cast<QObject*>(reply->request().attribute(QNetworkRequest::User));
    Request *req = qobject_cast<Request*>(obj);

    auto answer = reply->readAll();

    auto res = new Response(req, req);
    QDateTime now(QDateTime::currentDateTimeUtc());
    res->setResponseTime(req->startRequestTime().msecsTo(now));

    QList<QPair<QString, QString>> headers;
    foreach (const auto &p, reply->rawHeaderPairs())
        headers.append(QPair<QString, QString>(p.first, p.second));

    auto ct = reply->header(QNetworkRequest::ContentTypeHeader);
    if (!ct.isNull()) res->setContentType(ct.toString());

    res->setHeaders(headers);
    res->setBody(answer);
    emit responseReceived(res);
}
