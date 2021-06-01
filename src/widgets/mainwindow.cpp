#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include "./requesttree.h"
#include "./requesteditor.h"

#include <QTabBar>
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    requestTree = new RequestTree(ui->requestList);
    auto requestListLayout = new QVBoxLayout(this);
    requestListLayout->addWidget(requestTree);
    requestListLayout->setSpacing(0);
    requestListLayout->setMargin(0);
    ui->requestList->setLayout(requestListLayout);

    requestEditor = new RequestEditor(ui->requestResponseContainer);
    auto requestEditorLayout = new QVBoxLayout(this);
    requestEditorLayout->setSpacing(0);
    requestEditorLayout->setMargin(0);
    requestEditorLayout->addWidget(requestEditor);
    ui->requestResponseContainer->setLayout(requestEditorLayout);

    auto tabBarLayout = new QVBoxLayout(this);
    auto tabBar = new QTabBar(this);
    tabBar->setMovable(true);
    tabBar->setTabsClosable(true);
    tabBar->addTab("Tab 1");
    tabBar->setExpanding(false);
    tabBarLayout->addWidget(tabBar);
    tabBarLayout->setMargin(0);
    ui->tabBarContainer->setLayout(tabBarLayout);
}

MainWindow::~MainWindow()
{
    delete ui;
}
