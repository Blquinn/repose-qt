#ifndef REQUESTCONTAINER_H
#define REQUESTCONTAINER_H

#include <QWidget>

#include <KTextEditor/Document>
#include <KTextEditor/View>
#include <KTextEditor/Editor>
//#include <KTextEditor/EditorChooser>

namespace Ui {
class RequestContainer;
}

class RequestContainer : public QWidget
{
    Q_OBJECT

public:
    explicit RequestContainer(QWidget *parent = nullptr);
    ~RequestContainer();

private slots:
    void on_binaryBodyOpenDiagButton_clicked();

private:
    Ui::RequestContainer *ui;

    KTextEditor::Editor *m_requestEditor;
    KTextEditor::Document *m_requestEditorDocument;
    KTextEditor::View *m_requestEditorView;
};

#endif // REQUESTCONTAINER_H
