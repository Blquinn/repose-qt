#include "requestcontainer.h"
#include "ui_requestcontainer.h"

#include "QVBoxLayout"
#include "paramtable.h"

#include <QFileDialog>
#include <QUrlQuery>

void RequestContainer::onBodyTabWidgetCurrentIndexChanged()
{
    Request::RequestBody bod(Request::RequestBody::None);

    switch (ui->bodyTabWidget->currentIndex()) {
    case 0:
        bod = Request::RequestBody::None;
        break;
    case 1:
        bod = Request::RequestBody::Raw;
        break;
    case 2:
        bod = Request::RequestBody::Form;
        break;
    case 3:
        bod = Request::RequestBody::UrlEncoded;
        break;
    case 4:
        bod = Request::RequestBody::Binary;
        break;
    }

    m_rootState->activeRequest()->setActiveBody(bod);
}

RequestContainer::RequestContainer(RootState* rootState, QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::RequestContainer)
    , m_rootState(rootState)
    , m_requestEditor(nullptr)
    , m_requestEditorDocument(nullptr)
    , m_requestEditorView(nullptr)
    , m_paramsTable(nullptr)
    , m_headersTable(nullptr)
    , m_formDataTable(nullptr)
    , m_formUrlTable(nullptr)
{
    ui->setupUi(this);

    m_requestEditor = KTextEditor::Editor::instance();
    m_requestEditorDocument = m_requestEditor->createDocument(0);
    m_requestEditorView = m_requestEditorDocument->createView(this);
    m_requestEditorView->setContentsMargins(0, 0, 0, 0);

    auto requestEditorLayout = new QVBoxLayout(ui->bodyRaw);
    requestEditorLayout->setMargin(0);
    requestEditorLayout->setSpacing(0);
    requestEditorLayout->addWidget(m_requestEditorView);

    auto paramTableLayout = new QVBoxLayout(ui->paramsTab);
    paramTableLayout->setMargin(0);
    paramTableLayout->setSpacing(0);
    m_paramsTable = new ParamTable(this);
    paramTableLayout->addWidget(m_paramsTable);

    auto headerTableLayout = new QVBoxLayout(ui->headersTab);
    headerTableLayout->setMargin(0);
    headerTableLayout->setSpacing(0);
    m_headersTable = new ParamTable(this);
    headerTableLayout->addWidget(m_headersTable);

    auto formDataTableLayout = new QVBoxLayout(ui->bodyFormData);
    formDataTableLayout->setMargin(0);
    formDataTableLayout->setSpacing(0);
    m_formDataTable = new ParamTable(this);
    formDataTableLayout->addWidget(m_formDataTable);

    auto urlEncodedTableLayout = new QVBoxLayout(ui->bodyFormUrlEncoded);
    urlEncodedTableLayout->setMargin(0);
    urlEncodedTableLayout->setSpacing(0);
    m_formUrlTable = new ParamTable(this);
    urlEncodedTableLayout->addWidget(m_formUrlTable);

    // Bindings

    QObject::connect(m_rootState, &RootState::activeRequestChanged, this, [=]() {
        onActiveRequestChanged();
    });

    QObject::connect(ui->binaryBodyOpenDiagButton, &QPushButton::clicked, this, &RequestContainer::onBinaryBodyOpenDiagButtonClicked);
    QObject::connect(ui->paramsTabView, &QTabWidget::currentChanged, this, &RequestContainer::onParamTabViewCurrentIndexChanged);
    QObject::connect(ui->bodyTabWidget, &QTabWidget::currentChanged, this, &RequestContainer::onBodyTabWidgetCurrentIndexChanged);

    QObject::connect(m_requestEditorDocument, &KTextEditor::Document::modeChanged, this, [&](KTextEditor::Document* doc) {
        m_rootState->activeRequest()->setRequestMode(m_requestEditorDocument->mode());
    });
}

RequestContainer::~RequestContainer()
{
    delete ui;
}

void RequestContainer::onBinaryBodyChanged()
{
    auto file = m_rootState->activeRequest()->bodyBinary();
    if (file.isEmpty()) {
        ui->binaryBodyLabel->setText(QString("No file has been selected."));
    } else {
        ui->binaryBodyLabel->setText(QString("You opened %1").arg(file));
    }
}

void RequestContainer::onBinaryBodyOpenDiagButtonClicked()
{
    QFileDialog diag;
    auto file = diag.getOpenFileName();
    m_rootState->activeRequest()->setBodyBinary(file);
}

void RequestContainer::onActiveRequestChanged()
{
    auto req = m_rootState->activeRequest();
    if (!req)
        return;

    switch (req->activeSection()) {
    case Request::RequestAttributeSection::Params:
        ui->paramsTabView->setCurrentWidget(ui->paramsTab);
        break;
    case Request::RequestAttributeSection::Headers:
        ui->paramsTabView->setCurrentWidget(ui->headersTab);
        break;
    case Request::RequestAttributeSection::Body:
        ui->paramsTabView->setCurrentWidget(ui->bodyTab);
        break;
    }

    switch (req->activeBody()) {
    case Request::RequestBody::None:
        ui->bodyTabWidget->setCurrentWidget(ui->bodyNone);
        break;
    case Request::RequestBody::Raw:
        ui->bodyTabWidget->setCurrentWidget(ui->bodyRaw);
        break;
    case Request::RequestBody::Form:
        ui->bodyTabWidget->setCurrentWidget(ui->bodyFormData);
        break;
    case Request::RequestBody::UrlEncoded:
        ui->bodyTabWidget->setCurrentWidget(ui->bodyFormUrlEncoded);
        break;
    case Request::RequestBody::Binary:
        ui->bodyTabWidget->setCurrentWidget(ui->bodyBinary);
        break;
    }

    m_requestEditorDocument->setText(req->body());

    m_paramsTable->setModel(req->params().get());
    m_headersTable->setModel(req->headers().get());
    m_formDataTable->setModel(req->bodyForm().get());
    m_formUrlTable->setModel(req->bodyUrlEncoded().get());
    onBinaryBodyChanged();
    QObject::connect(req.get(), &Request::bodyBinaryChanged, this, &RequestContainer::onBinaryBodyChanged);
}

void RequestContainer::onParamTabViewCurrentIndexChanged()
{
    Request::RequestAttributeSection sec(Request::RequestAttributeSection::Params);

    switch (ui->paramsTabView->currentIndex()) {
    case 0:
        sec = Request::RequestAttributeSection::Params;
        break;
    case 1:
        sec = Request::RequestAttributeSection::Headers;
        break;
    case 2:
        sec = Request::RequestAttributeSection::Body;
        break;
    }

    m_rootState->activeRequest()->setActiveSection(sec);
}
