#ifndef REQUEST_H
#define REQUEST_H

#include <QObject>
#include <QDateTime>
#include <QSharedPointer>
#include "paramtablemodel.h"
#include "response.h"

class Response;

typedef QSharedPointer<Response> ResponsePtr;

class Request : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString url READ url WRITE setUrl NOTIFY urlChanged)
    Q_PROPERTY(QString method READ method WRITE setMethod NOTIFY methodChanged)
    Q_PROPERTY(QString body READ body WRITE setBody NOTIFY bodyChanged)
    Q_PROPERTY(QDateTime startRequestTime READ startRequestTime WRITE setStartRequestTime NOTIFY startRequestTimeChanged)
    Q_PROPERTY(ParamTableModelPtr headers READ headers WRITE setHeaders NOTIFY headersChanged)
    Q_PROPERTY(ParamTableModelPtr params READ params WRITE setParams NOTIFY paramsChanged)
    Q_PROPERTY(ResponsePtr response READ response WRITE setResponse NOTIFY responseChanged)
public:
    explicit Request(QObject *parent = nullptr);

    const QString &method() const;
    void setMethod(const QString &newMethod);

    const QString &url() const;
    void setUrl(const QString &newUrl);

    const QDateTime &startRequestTime() const;

    const QString &name() const;
    void setName(const QString &newName);

    const QString displayName();
    void setStartRequestTime(const QDateTime &newStartRequestTime);

    const QString &body() const;
    void setBody(const QString &newBody);

    ParamTableModelPtr params() const;
    void setParams(ParamTableModelPtr newParams);

    ParamTableModelPtr headers() const;
    void setHeaders(ParamTableModelPtr newHeaders);

    ResponsePtr response() const;
    void setResponse(ResponsePtr newResponse);

signals:
    void nameChanged();
    void urlChanged();
    void methodChanged();
    void startRequestTimeChanged();
    void bodyChanged();
    void paramsChanged();
    void headersChanged();

    void responseChanged();

private:
    QString m_url;
    QString m_method;
    QString m_name;
    QDateTime m_startRequestTime;
    QString m_body;
    ParamTableModelPtr m_params;
    ParamTableModelPtr m_headers;
    ResponsePtr m_response;
};

typedef QSharedPointer<Request> RequestPtr;

Q_DECLARE_METATYPE(Request*)
Q_DECLARE_METATYPE(QSharedPointer<Request>)

#endif // REQUEST_H
