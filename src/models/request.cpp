#include "request.h"

Request::Request(QObject *parent) : QObject(parent)
  , m_url("")
  , m_method("")
{

}

const QString &Request::method() const
{
    return m_method;
}

void Request::setMethod(const QString &newMethod)
{
    m_method = newMethod;
}

const QString &Request::url() const
{
    return m_url;
}

void Request::setUrl(const QString &newUrl)
{
    m_url = newUrl;
}

const QDateTime &Request::startRequestTime() const
{
    return m_startRequestTime;
}

void Request::setStartRequestTime(const QDateTime &newStartRequestTime)
{
    m_startRequestTime = newStartRequestTime;
}
