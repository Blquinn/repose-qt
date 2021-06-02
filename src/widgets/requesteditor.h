#ifndef REQUESTEDITOR_H
#define REQUESTEDITOR_H

#include <QWidget>

#include <src/services/httpclient.h>

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

    void on_sendButton_clicked();

    void on_urlEdit_returnPressed();

private:
    Ui::RequestEditor *ui;
    RequestContainer *requestContainer;
    ResponseContainer *responseContainer;

    HttpClient *m_httpClient;
};

#endif // REQUESTEDITOR_H
