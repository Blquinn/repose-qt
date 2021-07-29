#ifndef RESPONSE_H
#define RESPONSE_H

#include "paramtablerow.h"
#include "request.h"

#include <QList>
#include <QObject>
#include <QSharedPointer>
#include <QWeakPointer>

class Request;

typedef QList<QPair<QString, QString>> HeaderList;

class Response : public QObject {
public:
    Q_OBJECT
    Q_PROPERTY(QByteArray body READ body WRITE setBody NOTIFY bodyChanged)
    Q_PROPERTY(qint64 responseTime READ responseTime WRITE setResponseTime NOTIFY responseTimeChanged)
    Q_PROPERTY(HeaderList headers READ headers WRITE setHeaders NOTIFY headersChanged)
    Q_PROPERTY(QString contentType READ contentType WRITE setContentType NOTIFY contentTypeChanged)
    Q_PROPERTY(int statusCode READ statusCode WRITE setStatusCode NOTIFY statusCodeChanged)
    Q_PROPERTY(QString statusLine READ statusLine WRITE setStatusLine NOTIFY statusLineChanged)
public:
    explicit Response(QWeakPointer<Request> request, QObject* parent = nullptr);
    ~Response();

    const QByteArray& body() const;
    void setBody(const QByteArray& newBody);

    const QString& contentType() const;
    void setContentType(const QString& newContentType);

    const qint64& responseTime() const;
    void setResponseTime(const qint64& newResponseTime);

    const HeaderList& headers() const;
    void setHeaders(const HeaderList& newHeaders);

    int statusCode() const;
    void setStatusCode(int newStatusCode);

    const QString& statusLine() const;
    void setStatusLine(const QString& newStatusLine);
signals:
    void bodyChanged();
    void responseTimeChanged();
    void headersChanged();
    void contentTypeChanged();
    void statusCodeChanged();
    void statusLineChanged();

private:
    QWeakPointer<Request> m_request;
    QByteArray m_body;
    QString m_contentType;
    // In ns
    qint64 m_responseTime;
    int m_statusCode;
    QString m_statusLine;
    HeaderList m_headers;
};

typedef QSharedPointer<Response> ResponsePtr;

Q_DECLARE_METATYPE(Response*)
Q_DECLARE_METATYPE(QSharedPointer<Response>)

#endif // RESPONSE_H
