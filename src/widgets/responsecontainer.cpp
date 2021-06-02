#include "responsecontainer.h"
#include "ui_responsecontainer.h"

#include <src/utils/mimemapper.h>

ResponseContainer::ResponseContainer(HttpClient *httpClient, QWidget *parent) : QWidget(parent)
  , ui(new Ui::ResponseContainer)
  , m_httpClient(httpClient)
{
    ui->setupUi(this);

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

    QObject::connect(m_httpClient, SIGNAL(responseReceived(Response*)), this, SLOT(onResponseReceived(Response*)));
}

ResponseContainer::~ResponseContainer()
{
    delete ui;
}

void ResponseContainer::onResponseReceived(Response *response)
{
    QString headerMarkup;
    foreach (const auto &p, response->headers())
        headerMarkup += QString("<b>%1:</b> %2<br>").arg(p.first, p.first);

    ui->requestHeadersText->setText(headerMarkup);

    m_prettyResponseDocument->setReadWrite(true);
    m_prettyResponseDocument->setText(response->body());
    m_prettyResponseView->scroll(0, 0);
    KTextEditor::Cursor cur;
    cur.setPosition(0, 0);
    m_prettyResponseView->setScrollPosition(cur);
    m_prettyResponseDocument->setReadWrite(false);
    auto mode = MimeMapper::mapMime(response->contentType().split(";")[0].trimmed().toLower());
    m_prettyResponseDocument->setHighlightingMode(mode);

    ui->responseTextRaw->document()->setPlainText(response->body());
    ui->responseTextRaw->scroll(0, 0);

    ui->previewWebEngine->setContent(response->body(), response->contentType());
}
