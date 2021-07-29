#include "response.h"

Response::Response(QWeakPointer<Request> request, QObject* parent)
    : QObject(parent)
    , m_request(request)
    , m_contentType("")
    , m_headers()
    , m_responseTime(0)
    , m_statusCode(0)
    , m_statusLine()
{
}

Response::~Response()
{
}

const QByteArray& Response::body() const
{
    return m_body;
}

void Response::setBody(const QByteArray& newBody)
{
    m_body = newBody;
}

const QString& Response::contentType() const
{
    return m_contentType;
}

void Response::setContentType(const QString& newContentType)
{
    m_contentType = newContentType;
}

const qint64& Response::responseTime() const
{
    return m_responseTime;
}

void Response::setResponseTime(const qint64& newResponseTime)
{
    m_responseTime = newResponseTime;
}

const QList<QPair<QString, QString>>& Response::headers() const
{
    return m_headers;
}

void Response::setHeaders(const QList<QPair<QString, QString>>& newHeaders)
{
    m_headers = newHeaders;
}

int Response::statusCode() const
{
    return m_statusCode;
}

void Response::setStatusCode(int newStatusCode)
{
    if (m_statusCode == newStatusCode)
        return;
    m_statusCode = newStatusCode;
    emit statusCodeChanged();
}

const QString& Response::statusLine() const
{
    return m_statusLine;
}

void Response::setStatusLine(const QString& newStatusLine)
{
    if (m_statusLine == newStatusLine)
        return;
    m_statusLine = newStatusLine;
    emit statusLineChanged();
}
