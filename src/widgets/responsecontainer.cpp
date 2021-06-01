#include "responsecontainer.h"
#include "ui_responsecontainer.h"

ResponseContainer::ResponseContainer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ResponseContainer)
{
    ui->setupUi(this);
}

ResponseContainer::~ResponseContainer()
{
    delete ui;
}
