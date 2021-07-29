#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <src/models/rootstate.h>

#include "requesteditor.h"
#include "requesttree.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private slots:
    void onNewRequestTriggered();
    void onShowSidebarToggled(bool arg1);
    void onSplitterMoved(int pos, int index);

private:
    Ui::MainWindow* ui;
    RequestTree* requestTree;
    RequestEditor* requestEditor;

    int m_requestListPreviousWidth;

    QToolBar* buildToolBar();
    QToolBar m_requestTabs();
    QAction* actionNewRequest;
    QAction* actionShowSideBar;
    RootState* m_rootState;
};
#endif // MAINWINDOW_H
