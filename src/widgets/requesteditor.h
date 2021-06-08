#ifndef REQUESTEDITOR_H
#define REQUESTEDITOR_H

#include <QWidget>

#include <src/services/httpclient.h>
#include <src/models/rootstate.h>
#include <src/models/request.h>

#include "requestcontainer.h"
#include "responsecontainer.h"

namespace Ui {
class RequestEditor;
}

class RequestEditor : public QWidget
{
    Q_OBJECT

public:
    explicit RequestEditor(RootState *rootState, QWidget *parent = nullptr);
    ~RequestEditor();

private slots:
    void on_switchRequestButton_clicked(bool checked);
    void on_switchResponseButton_clicked(bool checked);
    void on_sendButton_clicked();
    void on_urlEdit_returnPressed();
    void on_requestNameEdit_textEdited(const QString &arg1);
    void on_urlEdit_textEdited(const QString &arg1);

    void bindRequest();
    void on_methodCombo_currentTextChanged(const QString &arg1);

private:
    Ui::RequestEditor *ui;
    RequestContainer *requestContainer;
    ResponseContainer *responseContainer;

    HttpClient *m_httpClient;
    RootState *m_rootState;
    QStringList m_defaultMethods;
};

#endif // REQUESTEDITOR_H
