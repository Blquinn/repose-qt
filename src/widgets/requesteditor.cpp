#include "requesteditor.h"
#include "ui_requesteditor.h"

RequestEditor::RequestEditor(QWidget *parent) : QWidget(parent)
    , ui(new Ui::RequestEditor)
    , m_httpClient(new HttpClient)
{
    ui->setupUi(this);
    // TODO: Re-set this whenever a request is changed.
    // Store the extra ones on a per-request basis.
    ui->methodCombo->addItems({
                                  "GET",
                                  "POST",
                                  "PUT",
                                  "PATCH",
                                  "DELETE",
                                  "CONNECT",
                                  "OPTIONS",
                                  "TRACE",
                              });

    requestContainer = new RequestContainer(this);
    responseContainer = new ResponseContainer(m_httpClient, this);
    ui->requestResponseStack->addWidget(requestContainer);
    ui->requestResponseStack->addWidget(responseContainer);

    connect(m_httpClient, &HttpClient::responseReceived, this, [=](Response* res) {
        Q_UNUSED(res)

        ui->switchResponseButton->click();
    });
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

    auto request = new Request();
    request->setUrl(ui->urlEdit->text());
    request->setMethod(ui->methodCombo->currentText());
    m_httpClient->initiateRequest(request);
}

void RequestEditor::on_urlEdit_returnPressed()
{
    ui->sendButton->click();
}

