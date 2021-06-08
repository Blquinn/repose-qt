#include "request.h"

Request::Request(QObject *parent) : QObject(parent)
  , m_name("")
  , m_url("")
  , m_method("")
  , m_body("")
  , m_startRequestTime()
  , m_params(new ParamTableModel())
  , m_headers(new ParamTableModel())
{

}

const QString &Request::method() const
{
    return m_method;
}

const QString &Request::url() const
{
    return m_url;
}

const QDateTime &Request::startRequestTime() const
{
    return m_startRequestTime;
}

const QString &Request::name() const
{
    return m_name;
}

const QString Request::displayName()
{
    if (m_name != "") return m_name;
    if (m_url != "") return QString("%1 - %1").arg(m_method, m_url);
    return "New Request";
}

void Request::setName(const QString &newName)
{
    if (m_name == newName)
        return;
    m_name = newName;
    emit nameChanged();
}

void Request::setUrl(const QString &newUrl)
{
    if (m_url == newUrl)
        return;
    m_url = newUrl;
    emit urlChanged();
}

void Request::setMethod(const QString &newMethod)
{
    if (m_method == newMethod)
        return;
    m_method = newMethod;
    emit methodChanged();
}

void Request::setStartRequestTime(const QDateTime &newStartRequestTime)
{
    if (m_startRequestTime == newStartRequestTime)
        return;
    m_startRequestTime = newStartRequestTime;
    emit startRequestTimeChanged();
}

const QString &Request::body() const
{
    return m_body;
}

void Request::setBody(const QString &newBody)
{
    if (m_body == newBody)
        return;
    m_body = newBody;
    emit bodyChanged();
}

ParamTableModelPtr Request::params() const
{
    return m_params;
}

void Request::setParams(ParamTableModelPtr newParams)
{
    if (m_params == newParams)
        return;
    m_params = newParams;
    emit paramsChanged();
}

ParamTableModelPtr Request::headers() const
{
    return m_headers;
}

void Request::setHeaders(ParamTableModelPtr newHeaders)
{
    if (m_headers == newHeaders)
        return;
    m_headers = newHeaders;
    emit headersChanged();
}

ResponsePtr Request::response() const
{
    return m_response;
}

void Request::setResponse(ResponsePtr newResponse)
{
    if (m_response == newResponse)
        return;
    m_response = newResponse;
    emit responseChanged();
}
