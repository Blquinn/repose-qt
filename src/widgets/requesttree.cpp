#include "requesttree.h"
#include "ui_requesttree.h"

#include <QFileSystemModel>

RequestTree::RequestTree(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RequestTree)
{
    ui->setupUi(this);
    auto model = new QFileSystemModel();
    model->setRootPath(QDir::currentPath());
    ui->treeView->setModel(model);
}

RequestTree::~RequestTree()
{
    delete ui;
}
