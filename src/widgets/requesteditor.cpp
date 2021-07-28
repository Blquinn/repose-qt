#include "requesteditor.h"
#include "ui_requesteditor.h"

#include <QToolTip>
#include <QUrlQuery>

RequestEditor::RequestEditor(RootState *rootState, QWidget *parent) : QWidget(parent)
    , ui(new Ui::RequestEditor)
    , m_httpClient(new HttpClient)
    , m_rootState(rootState)
    , m_defaultMethods(DEFAULT_METHODS)
    , m_responseLoadingSpinner(nullptr)
{
    ui->setupUi(this);
    m_responseLoadingSpinner = new WaitingSpinnerWidget(ui->responseLoaderWrap, true, false);

    // TODO: Re-set this whenever a request is changed.
    // Store the extra ones on a per-request basis.
    ui->methodCombo->addItems(m_defaultMethods);

    m_requestContainer = new RequestContainer(m_rootState, this);
    m_responseContainer = new ResponseContainer(rootState, m_httpClient, this);

    auto requestContainerLayout = new QVBoxLayout(ui->requestContainerWrapper);
    requestContainerLayout->setMargin(0);
    requestContainerLayout->addWidget(m_requestContainer);

    auto responseContainerLayout = new QVBoxLayout(ui->responseContainerInnerWrap);
    responseContainerLayout->setMargin(0);
    responseContainerLayout->addWidget(m_responseContainer);

    m_responseLoadingSpinner->setRoundness(70.0);
    m_responseLoadingSpinner->setMinimumTrailOpacity(15.0);
    m_responseLoadingSpinner->setTrailFadePercentage(70.0);
    m_responseLoadingSpinner->setNumberOfLines(12);
    m_responseLoadingSpinner->setLineLength(10);
    m_responseLoadingSpinner->setLineWidth(5);
    m_responseLoadingSpinner->setInnerRadius(10);
    m_responseLoadingSpinner->setRevolutionsPerSecond(1);
    m_responseLoadingSpinner->start();
    ui->responseLoaderStack->setCurrentIndex(1);

    QObject::connect(ui->cancelRequestButton, &QPushButton::clicked, this, [this]() {
        auto req = m_rootState->activeRequest();
        if (!req) return;

        auto rep = req->networkReply();
        if (req && rep->isRunning()) rep->abort();
    });

    QObject::connect(m_rootState, &RootState::activeRequestChanged, this, &RequestEditor::bindRequest);
    QObject::connect(ui->switchRequestButton, &QPushButton::clicked, this, &RequestEditor::onSwitchRequestButtonClicked);
    QObject::connect(ui->switchResponseButton, &QPushButton::clicked, this, &RequestEditor::onSwitchResponseButtonClicked);
    QObject::connect(ui->sendButton, &QPushButton::clicked, this, &RequestEditor::onSendButtonClicked);
    QObject::connect(ui->urlEdit, &QLineEdit::editingFinished, this, &RequestEditor::onUrlEditEditingFinished);
    QObject::connect(ui->urlEdit, &QLineEdit::returnPressed, this, &RequestEditor::onUrlEditReturnPressed);
    QObject::connect(ui->methodCombo, &QComboBox::currentTextChanged, this, &RequestEditor::onMethodComboCurrentTextChanged);
    QObject::connect(ui->requestNameEdit, &QLineEdit::textChanged, this, &RequestEditor::onRequestNameEditTextEdited);
}

RequestEditor::~RequestEditor()
{
    delete ui;
}

void RequestEditor::onSwitchRequestButtonClicked(bool checked)
{
    ui->requestResponseStack->setCurrentIndex(0);
    m_rootState->activeRequest()->setActiveTab(Request::MainTab::Request);
}

void RequestEditor::onSwitchResponseButtonClicked(bool checked)
{
//    ui->requestResponseStack->setCurrentWidget(m_responseContainer);
    ui->requestResponseStack->setCurrentIndex(1);
    m_rootState->activeRequest()->setActiveTab(Request::MainTab::Response);
}

void RequestEditor::onSendButtonClicked()
{
    qDebug() << "Send button clicked";

    m_rootState->activeRequest()->setBody(m_requestContainer->body());
    m_httpClient->initiateRequest(m_rootState->activeRequest());
    ui->switchResponseButton->click();
}

void RequestEditor::onUrlEditReturnPressed()
{
    onUrlEditEditingFinished();

    ui->sendButton->click();
}

void RequestEditor::onRequestNameEditTextEdited(const QString &name)
{
    m_rootState->activeRequest()->setName(name);
}

void RequestEditor::onMethodComboCurrentTextChanged(const QString &text)
{
    if (!m_rootState->activeRequest() || text.isEmpty()) return;
    m_rootState->activeRequest()->setMethod(text);
}

void RequestEditor::onUrlEditEditingFinished()
{
    qDebug() << "Url edit finished";

    auto newUrl = ui->urlEdit->text();

    m_rootState->activeRequest()->setUrl(newUrl);
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
    ui->responseLoaderStack->setCurrentIndex(request->loading() ? 0 : 1);

    QObject::connect(request.get(), &Request::urlChanged, this, [this, request]() {
        ui->urlEdit->setText(request->url());
    });

    QObject::connect(request.get(), &Request::loadingChanged, this, [this, request]() {
        auto idx = request->loading() ? 0 : 1;
        ui->responseLoaderStack->setCurrentIndex(idx);
    });
}
