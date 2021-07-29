#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include "./requesteditor.h"
#include "./requesttree.h"

#include <QIcon>
#include <QMetaObject>
#include <QSizePolicy>
#include <QTabBar>
#include <QToolBar>
#include <QVBoxLayout>

int getSideBarWidth(int editorWidth)
{
    return editorWidth / 3;
}

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_requestListPreviousWidth(0)
    , actionNewRequest(nullptr)
    , actionShowSideBar(nullptr)
    , m_rootState(new RootState(this))
{
    ui->setupUi(this);
    addToolBar(buildToolBar());

    requestTree = new RequestTree(ui->requestList);
    auto requestListLayout = new QVBoxLayout(ui->requestList);
    requestListLayout->addWidget(requestTree);
    requestListLayout->setSpacing(0);
    requestListLayout->setMargin(0);

    requestEditor = new RequestEditor(m_rootState, ui->requestResponseContainer);
    auto requestEditorLayout = new QVBoxLayout(ui->requestResponseContainer);
    requestEditorLayout->setSpacing(0);
    requestEditorLayout->setMargin(0);
    requestEditorLayout->setContentsMargins(0, 0, 5, 5);
    requestEditorLayout->addWidget(requestEditor);

    auto tabBarLayout = new QVBoxLayout(ui->tabBarContainer);
    auto m_requestTabs = new QTabBar(this);
    // TODO: Allow moving of tabs
    // m_requestTabs->setMovable(true);
    m_requestTabs->setTabsClosable(true);
    m_requestTabs->setExpanding(false);
    m_requestTabs->setElideMode(Qt::ElideRight);
    tabBarLayout->addWidget(m_requestTabs);
    tabBarLayout->setMargin(0);

    connect(actionShowSideBar, &QAction::toggled, this, &MainWindow::onShowSidebarToggled);
    connect(actionNewRequest, &QAction::triggered, this, &MainWindow::onNewRequestTriggered);

    actionShowSideBar->toggle();

    auto sbw = getSideBarWidth(width());
    ui->splitter->setSizes({ sbw, width() - sbw });
    m_requestListPreviousWidth = ui->requestList->width();

    // Hide sidebar
    actionShowSideBar->toggle();

    // Bindings

    connect(m_rootState, &RootState::requestListAdded, this, [=](int idx) {
        auto req = m_rootState->requestList()[idx];

        m_requestTabs->insertTab(idx, req->displayName());
        connect(req.get(), &Request::nameChanged, this, [=]() {
            m_requestTabs->setTabText(idx, req->name());
        });
    });

    connect(m_rootState, &RootState::requestListRemoved, this, [=](int idx) {
        m_requestTabs->removeTab(idx);
    });

    connect(m_requestTabs, &QTabBar::tabCloseRequested, this, [=](int idx) {
        m_rootState->removeFromRequestList(idx);
        // If the active req was deleted, try activating the one to the left if available,
        // otherwise the one to the right.
        if (idx - 1 >= 0) {
            m_rootState->setActiveRequest(m_rootState->requestList()[idx - 1]);
        } else if (idx <= m_rootState->requestList().length() - 1) {
            m_rootState->setActiveRequest(m_rootState->requestList()[idx]);
        } else {
            m_rootState->setActiveRequest(nullptr);
        }
    });

    connect(m_requestTabs, &QTabBar::currentChanged, this, [=](int idx) {
        if (idx < 0 || m_rootState->requestList().isEmpty())
            return;

        m_rootState->setActiveRequest(m_rootState->requestList()[idx]);
    });

    connect(m_rootState, &RootState::activeRequestChanged, this, [=]() {
        if (m_rootState->activeRequest() == nullptr) {
            ui->emptyStack->setCurrentWidget(ui->emptyPage);
            return;
        }

        ui->emptyStack->setCurrentWidget(ui->requestResponseContainer);
        m_requestTabs->setCurrentIndex(m_rootState->requestList().indexOf(m_rootState->activeRequest()));
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onNewRequestTriggered()
{
    qDebug() << "New request button pressed.";

    RequestPtr req(new Request());
    m_rootState->addActiveRequest(req);
    m_rootState->setActiveRequest(req);
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

void MainWindow::onShowSidebarToggled(bool toggled)
{
    if (actionShowSideBar->isChecked() && m_requestListPreviousWidth == 0) {
        auto reWidth = ui->requestResponseContainer->width();
        auto newWidth = getSideBarWidth(reWidth);
        ui->splitter->setSizes({ newWidth, reWidth - newWidth });
        return;
    }

    int currentWidth = ui->requestList->width();
    int newWidth = toggled ? m_requestListPreviousWidth : 0;

    auto reWidth = ui->requestResponseContainer->width();
    ui->splitter->setSizes({ newWidth, reWidth - newWidth });

    m_requestListPreviousWidth = toggled ? 0 : currentWidth;
}

void MainWindow::onSplitterMoved(int pos, int index)
{
    if (index != 1)
        return;

    auto checked = actionShowSideBar->isChecked();
    auto check = pos != 0;
    if (checked != check) {
        QSignalBlocker block(actionShowSideBar);

        actionShowSideBar->setChecked(pos != 0);
    }
}
