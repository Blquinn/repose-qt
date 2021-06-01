#ifndef RESPONSECONTAINER_H
#define RESPONSECONTAINER_H

#include <QWidget>

namespace Ui {
class ResponseContainer;
}

class ResponseContainer : public QWidget
{
    Q_OBJECT

public:
    explicit ResponseContainer(QWidget *parent = nullptr);
    ~ResponseContainer();

private:
    Ui::ResponseContainer *ui;
};

#endif // RESPONSECONTAINER_H
