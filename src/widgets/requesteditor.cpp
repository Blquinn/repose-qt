#include "requesteditor.h"
#include "ui_requesteditor.h"

RequestEditor::RequestEditor(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RequestEditor)
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
    responseContainer = new ResponseContainer(this);
    ui->requestResponseStack->addWidget(requestContainer);
    ui->requestResponseStack->addWidget(responseContainer);
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
