#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "requesttree.h"
#include "requesteditor.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionNew_Request_triggered();
    void on_actionShow_Sidebar_toggled(bool arg1);
    void on_splitter_splitterMoved(int pos, int index);
private:
    Ui::MainWindow *ui;
    RequestTree *requestTree;
    RequestEditor *requestEditor;

    int m_requestListPreviousWidth;

    QToolBar *buildToolBar();
    QAction *actionNewRequest;
    QAction *actionShowSideBar;
};
#endif // MAINWINDOW_H
