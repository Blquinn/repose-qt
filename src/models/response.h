#ifndef RESPONSE_H
#define RESPONSE_H

#include "paramtablerow.h"
#include "request.h"

#include <QList>
#include <QObject>
#include <QWeakPointer>

class Response : public QObject
{
    Q_OBJECT
public:
    explicit Response(Request *request, QObject *parent = nullptr);
    ~Response();

    Request *request() const;

    const QByteArray &body() const;
    void setBody(const QByteArray &newBody);

    const QString &contentType() const;
    void setContentType(const QString &newContentType);

    const qint64 &responseTime() const;
    void setResponseTime(const qint64 &newResponseTime);

    const QList<QPair<QString, QString> > &headers() const;
    void setHeaders(const QList<QPair<QString, QString> > &newHeaders);

signals:
private:
    Request *m_request;
    QByteArray m_body;
    QString m_contentType;
    // In ms
    qint64 m_responseTime;
    QList<QPair<QString, QString>> m_headers;
};

Q_DECLARE_METATYPE(Response*)

#endif // RESPONSE_H
