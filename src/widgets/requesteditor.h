#ifndef REQUESTEDITOR_H
#define REQUESTEDITOR_H

#include <QWidget>

#include <src/services/httpclient.h>
#include <src/models/rootstate.h>
#include <src/models/request.h>

#include "requestcontainer.h"
#include "responsecontainer.h"

static const QStringList DEFAULT_METHODS = {
    "GET", "POST", "PUT", "PATCH", "DELETE",
    "CONNECT", "OPTIONS", "TRACE",
};

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
    void onSwitchRequestButtonClicked(bool checked);
    void onSwitchResponseButtonClicked(bool checked);
    void onSendButtonClicked();
    void onUrlEditReturnPressed();
    void onRequestNameEditTextEdited(const QString &arg1);
    void onMethodComboCurrentTextChanged(const QString &arg1);
    void onUrlEditEditingFinished();

    void bindRequest();
private:
    Ui::RequestEditor *ui;
    RequestContainer *m_requestContainer;
    ResponseContainer *m_responseContainer;

    HttpClient *m_httpClient;
    RootState *m_rootState;
    QStringList m_defaultMethods;
};

#endif // REQUESTEDITOR_H
