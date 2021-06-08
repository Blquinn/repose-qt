#include "response.h"

Response::Response(QWeakPointer<Request> request, QObject *parent) : QObject(parent)
    , m_request(request)
    , m_contentType("")
    , m_headers()
    , m_responseTime(0)
{
}

Response::~Response()
{
}

//Request *Response::request() const
//{
//    return m_request;
//}

const QByteArray& Response::body() const
{
    return m_body;
}

void Response::setBody(const QByteArray &newBody)
{
    m_body = newBody;
}

const QString &Response::contentType() const
{
    return m_contentType;
}

void Response::setContentType(const QString &newContentType)
{
    m_contentType = newContentType;
}

const qint64 &Response::responseTime() const
{
    return m_responseTime;
}

void Response::setResponseTime(const qint64 &newResponseTime)
{
    m_responseTime = newResponseTime;
}

const QList<QPair<QString, QString>> &Response::headers() const
{
    return m_headers;
}

void Response::setHeaders(const QList<QPair<QString, QString> > &newHeaders)
{
    m_headers = newHeaders;
}
