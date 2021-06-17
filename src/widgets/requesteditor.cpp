#include "requesteditor.h"
#include "ui_requesteditor.h"

RequestEditor::RequestEditor(RootState *rootState, QWidget *parent) : QWidget(parent)
    , ui(new Ui::RequestEditor)
    , m_httpClient(new HttpClient)
    , m_rootState(rootState)
    , m_defaultMethods({
        "GET", "POST", "PUT", "PATCH", "DELETE",
        "CONNECT", "OPTIONS", "TRACE",
    })
{
    ui->setupUi(this);

    // TODO: Re-set this whenever a request is changed.
    // Store the extra ones on a per-request basis.
    ui->methodCombo->addItems(m_defaultMethods);

    requestContainer = new RequestContainer(m_rootState, this);
    responseContainer = new ResponseContainer(rootState, m_httpClient, this);
    ui->requestResponseStack->addWidget(requestContainer);
    ui->requestResponseStack->addWidget(responseContainer);

    QObject::connect(m_rootState, &RootState::activeRequestChanged, this, &RequestEditor::bindRequest);
    QObject::connect(ui->switchRequestButton, &QPushButton::clicked, this, &RequestEditor::onSwitchRequestButtonClicked);
    QObject::connect(ui->switchResponseButton, &QPushButton::clicked, this, &RequestEditor::onSwitchResponseButtonClicked);
    QObject::connect(ui->sendButton, &QPushButton::clicked, this, &RequestEditor::onSendButtonClicked);
    QObject::connect(ui->urlEdit, &QLineEdit::returnPressed, this, &RequestEditor::onUrlEditReturnPressed);
    QObject::connect(ui->urlEdit, &QLineEdit::textEdited, this, &RequestEditor::onUrlEditTextEdited);
    QObject::connect(ui->methodCombo, &QComboBox::currentTextChanged, this, &RequestEditor::onMethodComboCurrentTextChanged);
    QObject::connect(ui->requestNameEdit, &QLineEdit::textChanged, this, &RequestEditor::onRequestNameEditTextEdited);
}

RequestEditor::~RequestEditor()
{
    delete ui;
}

void RequestEditor::onSwitchRequestButtonClicked(bool checked)
{
    ui->requestResponseStack->setCurrentWidget(requestContainer);
    m_rootState->activeRequest()->setActiveTab(Request::MainTab::Request);
}

void RequestEditor::onSwitchResponseButtonClicked(bool checked)
{
    ui->requestResponseStack->setCurrentWidget(responseContainer);
    m_rootState->activeRequest()->setActiveTab(Request::MainTab::Response);
}

void RequestEditor::onSendButtonClicked()
{
    qDebug() << "Send button clicked";

    m_httpClient->initiateRequest(m_rootState->activeRequest());
    ui->switchResponseButton->click();
}

void RequestEditor::onUrlEditReturnPressed()
{
    ui->sendButton->click();
}

void RequestEditor::onRequestNameEditTextEdited(const QString &name)
{
    m_rootState->activeRequest()->setName(name);
}

void RequestEditor::onUrlEditTextEdited(const QString &url)
{
    m_rootState->activeRequest()->setUrl(url);
}

void RequestEditor::onMethodComboCurrentTextChanged(const QString &text)
{
    if (!m_rootState->activeRequest() || text.isEmpty()) return;
    m_rootState->activeRequest()->setMethod(text);
}

void RequestEditor::bindRequest()
{
    QSignalBlocker block(ui->methodCombo);

    ui->methodCombo->clear();
    ui->methodCombo->addItems(m_defaultMethods);

    auto request = m_rootState->activeRequest();

    if (!request) return;

    switch (request->activeTab()) {
    case Request::MainTab::Request:
        ui->switchRequestButton->click();
        break;
    case Request::MainTab::Response:
        ui->switchResponseButton->click();
        break;
    }

    ui->urlEdit->setText(request->url());
    ui->requestNameEdit->setText(request->name());
    ui->methodCombo->setCurrentText(request->method());
}

