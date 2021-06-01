#ifndef REQUESTEDITOR_H
#define REQUESTEDITOR_H

#include <QWidget>

#include "requestcontainer.h"
#include "responsecontainer.h"

namespace Ui {
class RequestEditor;
}

class RequestEditor : public QWidget
{
    Q_OBJECT

public:
    explicit RequestEditor(QWidget *parent = nullptr);
    ~RequestEditor();

private slots:
    void on_switchRequestButton_clicked(bool checked);

    void on_switchResponseButton_clicked(bool checked);

private:
    Ui::RequestEditor *ui;
    RequestContainer *requestContainer;
    ResponseContainer *responseContainer;
};

#endif // REQUESTEDITOR_H
