#include "sstream"

#include "responsecontainer.h"
#include "ui_responsecontainer.h"

#include "src/models/request.h"
#include "src/models/response.h"
#include "src/utils/humanize.h"
#include "src/utils/mimemapper.h"
#include "vendor/hexdump/Hexdump.hpp"

#include <QBuffer>
#include <QDomDocument>
#include <QJsonDocument>
#include <QTextStream>
#include <QWeakPointer>

ResponseContainer::ResponseContainer(RootState* rootState, HttpClient* httpClient, QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::ResponseContainer)
    , m_httpClient(httpClient)
{
    ui->setupUi(this);
    m_rootState = rootState;

    m_prettyResponseEditor = KTextEditor::Editor::instance();
    m_prettyResponseDocument = m_prettyResponseEditor->createDocument(0);
    m_prettyResponseView = m_prettyResponseDocument->createView(this);
    m_prettyResponseView->setContentsMargins(0, 0, 0, 0);

    m_prettyResponseDocument->setReadWrite(false);

    auto prettyResponseLayout = new QVBoxLayout(ui->responseBodyPrettyTab);
    prettyResponseLayout->setMargin(0);
    prettyResponseLayout->setSpacing(0);
    prettyResponseLayout->addWidget(m_prettyResponseView);

    connect(m_httpClient, &HttpClient::responseReceived, this, &ResponseContainer::onResponseReceived);

    connect(m_rootState, &RootState::activeRequestChanged, this, [=]() {
        bindRequest();
    });

    connect(ui->attributeTabs, &QTabWidget::currentChanged, this, [=](int idx) {
        auto req = m_rootState->activeRequest();
        if (!req)
            return;

        req->setActiveResponseAttribute((Request::ResponseAttributeType)idx);
    });

    connect(ui->bodyTabs, &QTabWidget::currentChanged, this, [=](int idx) {
        auto req = m_rootState->activeRequest();
        if (!req)
            return;

        req->setActiveResponseBodyType((Request::ResponseBodyType)idx);
    });
}

ResponseContainer::~ResponseContainer()
{
    delete ui;
}

bool isPreviewableResponse(QString contentType)
{
    if (contentType == "text/html")
        return true;
    if (contentType.startsWith("image"))
        return true;
    return false;
}

bool isBinaryFormat(QString contentType)
{
    if (contentType == "")
        return true;
    if (contentType == "application/octet-stream")
        return true;
    if (contentType.startsWith("image"))
        return true;
    return false;
}

void ResponseContainer::onResponseReceived(ResponsePtr response)
{
    bindResponse(response);
}

void ResponseContainer::bindRequest()
{
    // Unbind current bindings.
    auto req = m_rootState->activeRequest();
    if (!req)
        return;

    ui->attributeTabs->setCurrentIndex((int)req->activeResponseAttribute());
    ui->bodyTabs->setCurrentIndex((int)req->activeResponseBodyType());

    bindResponse(req->response());
}

void ResponseContainer::bindResponse(ResponsePtr response)
{
    // TODO: Clear out stuff.
    if (response.isNull())
        return;

    QString headerMarkup;
    for (const auto& p : response->headers())
        headerMarkup += QString("<b>%1:</b> %2<br>").arg(p.first, p.second);

    ui->requestHeadersText->setText(headerMarkup);

    QString body;
    QString prettyBody;

    if (isBinaryFormat(response->contentType())) {
        std::stringstream str;

        str << Hexdump((unsigned char*)response->body().constData(), response->body().size());

        body = str.str().c_str();
        prettyBody = str.str().c_str();
    } else if (response->contentType().startsWith("application/json")) {
        body = response->body();
        try {
            auto doc = QJsonDocument::fromJson(response->body());
            prettyBody = doc.toJson(QJsonDocument::JsonFormat::Indented);
        } catch (std::exception& e) {
            qWarning() << "Failed to parse json document " << e.what();
            prettyBody = response->body();
        }
    } else if (response->contentType().startsWith("text/xml") || response->contentType().startsWith("application/xml")) {
        body = response->body();
        try {
            QDomDocument input;
            input.setContent(response->body());
            QString formattedXMLResponse;
            QTextStream stream(&formattedXMLResponse);
            input.save(stream, 2);
            prettyBody = formattedXMLResponse.toUtf8();
        } catch (std::exception& e) {
            qWarning() << "Failed to parse xml document " << e.what();
            prettyBody = response->body();
        }
    } else {
        body = response->body();
        prettyBody = response->body();
    }

    m_prettyResponseDocument->setReadWrite(true);
    m_prettyResponseDocument->setText(prettyBody);
    m_prettyResponseView->scroll(0, 0);
    KTextEditor::Cursor cur;
    cur.setPosition(0, 0);
    m_prettyResponseView->setScrollPosition(cur);
    m_prettyResponseDocument->setReadWrite(false);
    auto mimeType = response->contentType().split(";").first().trimmed().toLower();
    auto mode = MimeMapper::mapMime(mimeType);
    m_prettyResponseDocument->setMode(mode);

    ui->responseTextRaw->document()->setPlainText(body);
    ui->responseTextRaw->scroll(0, 0);
    ui->responseTextRaw->centerOnScroll();

    ui->timeLabel->setText(Humanize::timeSpan(response->responseTime()));
    auto statusCodeText = response->statusCode() ? QString::number(response->statusCode()) : "-";
    ui->statusLabel->setText(QString("%1 %2").arg(statusCodeText, response->statusLine()));
    ui->sizeLabel->setText(Humanize::bytes(response->body().length()));

    if (isPreviewableResponse(mimeType)) {
        ui->previewWebEngine->setContent(response->body(), mimeType);
    } else {
        ui->previewWebEngine->setContent("", "text/plain; charset=UTF-8");
    }
}
