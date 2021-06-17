#ifndef RESPONSECONTAINER_H
#define RESPONSECONTAINER_H

#include <QWidget>

#include <KTextEditor/Editor>
#include <KTextEditor/Document>
#include <KTextEditor/View>

#include <src/services/httpclient.h>
#include <src/models/rootstate.h>

namespace Ui {
class ResponseContainer;
}


// TODO: Store response bodies in /tmp

class ResponseContainer : public QWidget
{
    Q_OBJECT

public:
    explicit ResponseContainer(RootState *rootState, HttpClient *httpClient, QWidget *parent = nullptr);
    ~ResponseContainer();

private slots:
    void onResponseReceived(ResponsePtr response);
private:
    void bindRequest();
    void bindResponse(ResponsePtr);
private:
    Ui::ResponseContainer *ui;
    RootState *m_rootState;
    HttpClient *m_httpClient;

    KTextEditor::Editor *m_prettyResponseEditor;
    KTextEditor::Document *m_prettyResponseDocument;
    KTextEditor::View *m_prettyResponseView;
};

#endif // RESPONSECONTAINER_H
