#ifndef REQUESTTREE_H
#define REQUESTTREE_H

#include <QWidget>

namespace Ui {
class RequestTree;
}

class RequestTree : public QWidget
{
    Q_OBJECT

public:
    explicit RequestTree(QWidget *parent = nullptr);
    ~RequestTree();

private:
    Ui::RequestTree *ui;
};

#endif // REQUESTTREE_H
