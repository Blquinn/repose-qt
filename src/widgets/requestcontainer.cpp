#include "requestcontainer.h"
#include "ui_requestcontainer.h"

#include "QVBoxLayout"
#include "paramtable.h"

#include <QFileDialog>

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

RequestContainer::RequestContainer(RootState *rootState, QWidget *parent) :
    QWidget(parent)
    , ui(new Ui::RequestContainer)
    , m_rootState(rootState)
{
    ui->setupUi(this);

    m_requestEditor = KTextEditor::Editor::instance();
    m_requestEditorDocument = m_requestEditor->createDocument(0);
    m_requestEditorView = m_requestEditorDocument->createView(this);
    m_requestEditorView->setContentsMargins(0, 0, 0, 0);

    auto requestEditorLayout = new QVBoxLayout(this);
    requestEditorLayout->setMargin(0);
    requestEditorLayout->setSpacing(0);
    ui->bodyRaw->setLayout(requestEditorLayout);
    requestEditorLayout->addWidget(m_requestEditorView);

    auto paramTableLayout = new QVBoxLayout(this);
    paramTableLayout->setMargin(0);
    paramTableLayout->setSpacing(0);
    ui->paramsTab->setLayout(paramTableLayout);
    auto pt = new ParamTable(this);
    paramTableLayout->addWidget(pt);

    auto headerTableLayout = new QVBoxLayout(this);
    headerTableLayout->setMargin(0);
    headerTableLayout->setSpacing(0);
    ui->headersTab->setLayout(headerTableLayout);
    auto ht = new ParamTable(this);
    headerTableLayout->addWidget(ht);

    auto formDataTableLayout = new QVBoxLayout(this);
    formDataTableLayout->setMargin(0);
    formDataTableLayout->setSpacing(0);
    ui->bodyFormData->setLayout(formDataTableLayout);
    auto ft = new ParamTable(this);
    formDataTableLayout->addWidget(ft);

    auto urlEncodedTableLayout = new QVBoxLayout(this);
    urlEncodedTableLayout->setMargin(0);
    urlEncodedTableLayout->setSpacing(0);
    ui->bodyFormUrlEncoded->setLayout(urlEncodedTableLayout);
    auto ut = new ParamTable(this);
    urlEncodedTableLayout->addWidget(ut);

    // Bindings

    connect(m_rootState, &RootState::activeRequestChanged, this, [=]() {
        onActiveRequestChanged();
    });

    connect(ui->binaryBodyOpenDiagButton, &QPushButton::clicked, this, &RequestContainer::onBinaryBodyOpenDiagButtonClicked);
    connect(ui->paramsTabView, &QTabWidget::currentChanged, this, &RequestContainer::onParamTabViewCurrentIndexChanged);
    connect(ui->bodyTabWidget, &QTabWidget::currentChanged, this, &RequestContainer::onBodyTabWidgetCurrentIndexChanged);
}

RequestContainer::~RequestContainer()
{
    delete ui;
}

void RequestContainer::onBinaryBodyOpenDiagButtonClicked()
{
    QFileDialog diag;
    auto file = diag.getOpenFileName();
    ui->binaryBodyLabel->setText(QString("You opened %1").arg(file));
}

void RequestContainer::onActiveRequestChanged()
{
    auto req = m_rootState->activeRequest();
    if (!req) return;

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
