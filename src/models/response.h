#ifndef RESPONSE_H
#define RESPONSE_H

#include "paramtablerow.h"
#include "request.h"

#include <QList>
#include <QObject>
#include <QWeakPointer>
#include <QSharedPointer>

class Request;

typedef QList<QPair<QString, QString>> HeaderList;

class Response : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QByteArray body READ body WRITE setBody NOTIFY bodyChanged)
    Q_PROPERTY(qint64 responseTime READ responseTime WRITE setResponseTime NOTIFY responseTimeChanged)
    Q_PROPERTY(HeaderList headers READ headers WRITE setHeaders NOTIFY headersChanged)
    Q_PROPERTY(QString contentType READ contentType WRITE setContentType NOTIFY contentTypeChanged)
public:
    explicit Response(QWeakPointer<Request> request, QObject *parent = nullptr);
    ~Response();

    const QByteArray &body() const;
    void setBody(const QByteArray &newBody);

    const QString &contentType() const;
    void setContentType(const QString &newContentType);

    const qint64 &responseTime() const;
    void setResponseTime(const qint64 &newResponseTime);

    const HeaderList &headers() const;
    void setHeaders(const HeaderList &newHeaders);

signals:
    void bodyChanged();
    void responseTimeChanged();
    void headersChanged();
    void contentTypeChanged();
private:
    QWeakPointer<Request> m_request;
    QByteArray m_body;
    QString m_contentType;
    // In ms
    qint64 m_responseTime;
    HeaderList m_headers;
};

typedef QSharedPointer<Response> ResponsePtr;

Q_DECLARE_METATYPE(Response*)
Q_DECLARE_METATYPE(QSharedPointer<Response>)

#endif // RESPONSE_H
