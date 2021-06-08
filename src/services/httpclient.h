#ifndef HTTPCLIENT_H
#define HTTPCLIENT_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>

#include "src/models/request.h"
#include "src/models/response.h"

class HttpClient : public QObject
{
    Q_OBJECT
public:
    explicit HttpClient(QObject *parent = nullptr);

    void initiateRequest(RequestPtr request);
signals:
    void responseReceived(ResponsePtr response);
private slots:
    void onResponseReceived(QNetworkReply *reply);
private:
    QNetworkAccessManager *m_networkManager;
};

#endif // HTTPCLIENT_H
