#include "paramtable.h"
#include "ui_paramtable.h"

ParamTable::ParamTable(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ParamTable)
{
    ui->setupUi(this);
    m_model = new ParamTableModel(this);
    m_model->addEmptyRow();
    ui->tableView->setModel(m_model);
}

ParamTable::~ParamTable()
{
    delete ui;
}

void ParamTable::setModel(ParamTableModel *model)
{
    ui->tableView->setModel(model);
}
