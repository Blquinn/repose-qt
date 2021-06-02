#ifndef RESPONSECONTAINER_H
#define RESPONSECONTAINER_H

#include <QWidget>

#include <KTextEditor/Editor>
#include <KTextEditor/Document>
#include <KTextEditor/View>

#include <src/services/httpclient.h>

namespace Ui {
class ResponseContainer;
}

class ResponseContainer : public QWidget
{
    Q_OBJECT

public:
    explicit ResponseContainer(HttpClient *httpClient, QWidget *parent = nullptr);
    ~ResponseContainer();

private slots:
    void onResponseReceived(Response* response);
private:
    Ui::ResponseContainer *ui;
    HttpClient *m_httpClient;

    KTextEditor::Editor *m_prettyResponseEditor;
    KTextEditor::Document *m_prettyResponseDocument;
    KTextEditor::View *m_prettyResponseView;
};

#endif // RESPONSECONTAINER_H
