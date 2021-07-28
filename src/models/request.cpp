#include "request.h"

#include <QMimeDatabase>
#include <QUrl>
#include <QUrlQuery>
#include <QDebug>

#include "src/utils/defer.h"

Request::Request(QObject *parent) : QObject(parent)
  , m_name("")
  , m_url("")
  , m_method("GET")
  , m_body("")
  , m_requestMode("")
  , m_bodyForm(new ParamTableModel())
  , m_bodyUrlEncoded(new ParamTableModel())
  , m_bodyBinary("")
  , m_requestTimer()
  , m_params(new ParamTableModel())
  , m_headers(new ParamTableModel())
  , m_activeTab(MainTab::Request)
  , m_activeSection(RequestAttributeSection::Params)
  , m_activeBody(RequestBody::None)
  , m_activeResponseAttribute(ResponseAttributeType::Headers)
  , m_activeResponseBodyType(ResponseBodyType::Pretty)
  , m_loading(false)
  , m_networkReply(nullptr)
{
    m_params->addEmptyRow();
    m_headers->addEmptyRow();
    m_bodyForm->addEmptyRow();
    m_bodyUrlEncoded->addEmptyRow();

    QObject::connect(this, &Request::urlChanged, this, &Request::onUrlChanged);

    QObject::connect(m_params.get(), &QAbstractItemModel::dataChanged, this, [&](){
        auto query = m_params->urlEncode();

        QUrl url(m_url);
        url.setQuery(query);

        auto newUrl = url.toString();
        qDebug() << "Setting url to " << newUrl;

        QObject::disconnect(this, &Request::urlChanged, this, &Request::onUrlChanged);
        setUrl(newUrl);
        QObject::connect(this, &Request::urlChanged, this, &Request::onUrlChanged);
    });
}

const QString &Request::method() const
{
    return m_method;
}

const QString &Request::url() const
{
    return m_url;
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

const QElapsedTimer &Request::requestTimer() const
{
    return m_requestTimer;
}

void Request::setRequestTimer(const QElapsedTimer &newRequestTimer)
{
    if (m_requestTimer == newRequestTimer)
        return;
    m_requestTimer = newRequestTimer;
    emit requestTimerChanged();
}

Request::MainTab Request::activeTab() const
{
    return m_activeTab;
}

void Request::setActiveTab(MainTab newActiveTab)
{
    if (m_activeTab == newActiveTab)
        return;
    m_activeTab = newActiveTab;
    emit activeTabChanged();
}

Request::RequestAttributeSection Request::activeSection() const
{
    return m_activeSection;
}

void Request::setActiveSection(RequestAttributeSection newActiveSection)
{
    if (m_activeSection == newActiveSection)
        return;
    m_activeSection = newActiveSection;
    emit activeSectionChanged();
}

Request::RequestBody Request::activeBody() const
{
    return m_activeBody;
}

void Request::setActiveBody(RequestBody newActiveBody)
{
    if (m_activeBody == newActiveBody)
        return;
    m_activeBody = newActiveBody;

    emit activeBodyChanged();

    updateContentType();
}

void Request::updateContentType()
{
    switch (m_activeBody) {
    case Request::RequestBody::None:
        m_headers->removeRowByKey("Content-Type");
        break;
    case Request::RequestBody::Raw:
        // Set based on raw body mime type.
        // TODO: Handle more modes.

        if (m_requestMode == "Normal") {
            m_headers->upsertRowByKey(ParamTableRow("Content-Type", "text/plain", ""));
        } else if (m_requestMode == "JSON") {
            m_headers->upsertRowByKey(ParamTableRow("Content-Type", "application/json", ""));
        } else if (m_requestMode == "HTML") {
            m_headers->upsertRowByKey(ParamTableRow("Content-Type", "text/html", ""));
        } else if (m_requestMode == "JavaScript") {
            m_headers->upsertRowByKey(ParamTableRow("Content-Type", "application/javascript", ""));
        }

        break;
    case Request::RequestBody::Form:
            m_headers->upsertRowByKey(ParamTableRow("Content-Type", "multipart/form-data", ""));
        break;
    case Request::RequestBody::UrlEncoded:
            m_headers->upsertRowByKey(ParamTableRow("Content-Type", "application/x-www-form-urlencoded", ""));
        break;
    case Request::RequestBody::Binary:
        setContentTypeForBinaryBody();
        break;
    }
}

void Request::setContentTypeForBinaryBody()
{
    QMimeDatabase mimeDb;
    auto mimeType = mimeDb.mimeTypeForFile(m_bodyBinary);
    if (mimeType.isValid()) {
        m_headers->upsertRowByKey(ParamTableRow("Content-Type", mimeType.name(), ""));
    } else {
        m_headers->removeRowByKey("Content-Type");
    }
}

void Request::onUrlChanged()
{
    QUrl url(m_url, QUrl::ParsingMode::StrictMode);
    if (!url.isValid()) {
        qDebug() << "User entered invalid url";
        return;
    }

    QUrlQuery query(url.query());
    m_params->updateFromQuery(query.queryItems());
}

Request::ResponseAttributeType Request::activeResponseAttribute() const
{
    return m_activeResponseAttribute;
}

void Request::setActiveResponseAttribute(ResponseAttributeType newActiveResponseAttribute)
{
    if (m_activeResponseAttribute == newActiveResponseAttribute)
        return;
    m_activeResponseAttribute = newActiveResponseAttribute;
    emit activeResponseAttributeChanged();
}

Request::ResponseBodyType Request::activeResponseBodyType() const
{
    return m_activeResponseBodyType;
}

void Request::setActiveResponseBodyType(ResponseBodyType newActiveResponseBodyType)
{
    if (m_activeResponseBodyType == newActiveResponseBodyType)
        return;
    m_activeResponseBodyType = newActiveResponseBodyType;
    emit activeResponseBodyTypeChanged();
}

const QString &Request::requestMode() const
{
    return m_requestMode;
}

void Request::setRequestMode(const QString &newRequestMode)
{
    if (m_requestMode == newRequestMode)
        return;
    m_requestMode = newRequestMode;
    emit requestModeChanged();
    updateContentType();
}

ParamTableModelPtr Request::bodyForm() const
{
    return m_bodyForm;
}

void Request::setBodyForm(ParamTableModelPtr newBodyForm)
{
    if (m_bodyForm == newBodyForm)
        return;
    m_bodyForm = newBodyForm;
    emit bodyFormChanged();
}

ParamTableModelPtr Request::bodyUrlEncoded() const
{
    return m_bodyUrlEncoded;
}

void Request::setBodyUrlEncoded(ParamTableModelPtr newBodyUrlEncoded)
{
    if (m_bodyUrlEncoded == newBodyUrlEncoded)
        return;
    m_bodyUrlEncoded = newBodyUrlEncoded;
    emit bodyUrlEncodedChanged();
}

const QString &Request::bodyBinary() const
{
    return m_bodyBinary;
}

void Request::setBodyBinary(const QString &newBodyBinary)
{
    if (m_bodyBinary == newBodyBinary)
        return;
    m_bodyBinary = newBodyBinary;
    emit bodyBinaryChanged();
    setContentTypeForBinaryBody();
}

bool Request::loading() const
{
    return m_loading;
}

void Request::setLoading(bool newLoading)
{
    if (m_loading == newLoading)
        return;
    m_loading = newLoading;
    emit loadingChanged();
}

QNetworkReply *Request::networkReply() const
{
    return m_networkReply;
}

void Request::setNetworkReply(QNetworkReply *newNetworkReply)
{
    if (m_networkReply == newNetworkReply)
        return;
    m_networkReply = newNetworkReply;
    emit networkReplyChanged();
}
