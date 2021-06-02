#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include "./requesttree.h"
#include "./requesteditor.h"

#include <QIcon>
#include <QSizePolicy>
#include <QTabBar>
#include <QToolBar>
#include <QVBoxLayout>

int getSideBarWidth(int editorWidth) {
    return editorWidth / 3;
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_requestListPreviousWidth(0)
    , actionNewRequest(nullptr)
    , actionShowSideBar(nullptr)
{
    ui->setupUi(this);
    addToolBar(buildToolBar());

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
    requestEditorLayout->setContentsMargins(0, 0, 5, 5);
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

    connect(actionShowSideBar, &QAction::toggled, this, &MainWindow::on_actionShow_Sidebar_toggled);
    connect(actionNewRequest, &QAction::triggered, this, &MainWindow::on_actionNew_Request_triggered);

    actionShowSideBar->toggle();

    auto sbw = getSideBarWidth(width());
    ui->splitter->setSizes({sbw, width()-sbw});
    m_requestListPreviousWidth = ui->requestList->width();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionNew_Request_triggered()
{
    qDebug() << "New request button pressed.";
}


QToolBar* MainWindow::buildToolBar()
{
    auto tb = new QToolBar(this);

    actionShowSideBar = new QAction(this);

    actionShowSideBar->setIcon(QIcon::fromTheme("view-dual-symbolic"));
    actionShowSideBar->setIconText(tr("Show side panel."));
    actionShowSideBar->setCheckable(true);

    tb->addAction(actionShowSideBar);

    auto spacer = new QWidget(this);
    spacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);

    tb->addWidget(spacer);

    actionNewRequest = new QAction(this);
    actionNewRequest->setIcon(QIcon::fromTheme("list-add-symbolic"));
    actionNewRequest->setIconText(tr("New Request."));

    tb->addAction(actionNewRequest);

    return tb;
}

void MainWindow::on_actionShow_Sidebar_toggled(bool toggled)
{
    if (actionShowSideBar->isChecked() && m_requestListPreviousWidth == 0) {
        auto reWidth = ui->requestResponseContainer->width();
        auto newWidth = getSideBarWidth(reWidth);
        ui->splitter->setSizes({newWidth, reWidth-newWidth});
        return;
    }

    int currentWidth = ui->requestList->width();
    int newWidth = toggled ? m_requestListPreviousWidth : 0;

    auto reWidth = ui->requestResponseContainer->width();
    ui->splitter->setSizes({newWidth, reWidth-newWidth});

    m_requestListPreviousWidth = toggled ? 0 : currentWidth;
}

void MainWindow::on_splitter_splitterMoved(int pos, int index)
{
    if (index != 1) return;

    auto checked = actionShowSideBar->isChecked();
    auto check = pos != 0;
    if (checked != check) {
        QSignalBlocker block(actionShowSideBar);

        actionShowSideBar->setChecked(pos != 0);
    }
}
