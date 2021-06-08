#include "sstream"

#include "responsecontainer.h"
#include "ui_responsecontainer.h"

#include "src/utils/mimemapper.h"
#include "src/models/response.h"
#include "vendor/hexdump/Hexdump.hpp"

#include <QBuffer>

ResponseContainer::ResponseContainer(RootState *rootState, HttpClient *httpClient, QWidget *parent) : QWidget(parent)
  , ui(new Ui::ResponseContainer)
  , m_httpClient(httpClient)
{
    ui->setupUi(this);
    m_rootState = rootState;

    m_prettyResponseEditor = KTextEditor::Editor::instance();
    m_prettyResponseDocument = m_prettyResponseEditor->createDocument(0);
    m_prettyResponseView = m_prettyResponseDocument->createView(this);
    m_prettyResponseView->setContentsMargins(0, 0, 0, 0);

    QFile f("/tmp/hm.txt");
    f.open(QIODevice::OpenModeFlag::ReadWrite);
    foreach (const auto &m, m_prettyResponseDocument->highlightingModes()) {
        f.write((m + "\n").toUtf8());
    }
    f.close();

    m_prettyResponseDocument->setReadWrite(false);

    auto prettyResponseLayout = new QVBoxLayout(this);
    prettyResponseLayout->setMargin(0);
    prettyResponseLayout->setSpacing(0);
    ui->responseBodyPrettyTab->setLayout(prettyResponseLayout);
    prettyResponseLayout->addWidget(m_prettyResponseView);

    connect(m_httpClient, &HttpClient::responseReceived, this, &ResponseContainer::onResponseReceived);
}

ResponseContainer::~ResponseContainer()
{
    delete ui;
}

bool isPreviewableResponse(QString contentType)
{
    if (contentType == "text/html") return true;
    if (contentType.startsWith("image")) return true;
    return false;
}

bool isBinaryFormat(QString contentType) {
    if (contentType == "") return true;
    if (contentType == "application/octet-stream") return true;
    if (contentType.startsWith("image")) return true;
    return false;
}

void ResponseContainer::onResponseReceived(ResponsePtr response)
{
    QString headerMarkup;
    for (const auto &p : response->headers())
        headerMarkup += QString("<b>%1:</b> %2<br>").arg(p.first, p.second);

    ui->requestHeadersText->setText(headerMarkup);

    // TODO: Do we actually want this?
    QByteArray body;
    if (isBinaryFormat(response->contentType())) {
        std::stringstream str;

        str << Hexdump((unsigned char*) response->body().constData(), response->body().size());

        body = str.str().c_str();
    } else {
        body = response->body();
    }

    m_prettyResponseDocument->setReadWrite(true);
    m_prettyResponseDocument->setText(body);
    m_prettyResponseView->scroll(0, 0);
    KTextEditor::Cursor cur;
    cur.setPosition(0, 0);
    m_prettyResponseView->setScrollPosition(cur);
    m_prettyResponseDocument->setReadWrite(false);
    auto mimeType = response->contentType().split(";")[0].trimmed().toLower();
    auto mode = MimeMapper::mapMime(mimeType);
    m_prettyResponseDocument->setHighlightingMode(mode);

    ui->responseTextRaw->document()->setPlainText(body);
    ui->responseTextRaw->scroll(0, 0);
    ui->responseTextRaw->centerOnScroll();

    if (isPreviewableResponse(mimeType)) {
        ui->previewWebEngine->setContent(response->body(), mimeType);
    } else {
        ui->previewWebEngine->setContent("", "text/plain; charset=UTF-8");
    }
}

void ResponseContainer::bindRequest()
{
    // Unbind current bindings.
    auto req = m_rootState->activeRequest();
    if (req.isNull()) return;

    auto res = req->response();
    if (res.isNull()) return;

    onResponseReceived(res);
}
