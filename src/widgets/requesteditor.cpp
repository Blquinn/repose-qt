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

    requestContainer = new RequestContainer(this);
    responseContainer = new ResponseContainer(rootState, m_httpClient, this);
    ui->requestResponseStack->addWidget(requestContainer);
    ui->requestResponseStack->addWidget(responseContainer);

    connect(m_rootState, &RootState::activeRequestChanged, this, &RequestEditor::bindRequest);
}

RequestEditor::~RequestEditor()
{
    delete ui;
}

void RequestEditor::on_switchRequestButton_clicked(bool checked)
{
    ui->requestResponseStack->setCurrentWidget(requestContainer);
}

void RequestEditor::on_switchResponseButton_clicked(bool checked)
{
    ui->requestResponseStack->setCurrentWidget(responseContainer);
}

void RequestEditor::on_sendButton_clicked()
{
    qDebug() << "Send button clicked";

    m_httpClient->initiateRequest(m_rootState->activeRequest());
    ui->switchResponseButton->click();
}

void RequestEditor::on_urlEdit_returnPressed()
{
    ui->sendButton->click();
}

void RequestEditor::on_requestNameEdit_textEdited(const QString &name)
{
    m_rootState->activeRequest()->setName(name);
}

void RequestEditor::on_urlEdit_textEdited(const QString &url)
{
    m_rootState->activeRequest()->setUrl(url);
}

void RequestEditor::on_methodCombo_currentTextChanged(const QString &text)
{
    if (!m_rootState->activeRequest()) return;
    m_rootState->activeRequest()->setMethod(text);
}

void RequestEditor::bindRequest()
{
    ui->methodCombo->clear();
    ui->methodCombo->addItems(m_defaultMethods);

    auto request = m_rootState->activeRequest();

    if (!request) return;

    ui->urlEdit->setText(request->url());
    ui->requestNameEdit->setText(request->name());
    ui->methodCombo->setCurrentText(request->method());
}

