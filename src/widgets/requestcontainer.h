#ifndef REQUESTCONTAINER_H
#define REQUESTCONTAINER_H

#include <QWidget>

#include <KTextEditor/Document>
#include <KTextEditor/View>
#include <KTextEditor/Editor>

#include <src/models/rootstate.h>
//#include <KTextEditor/EditorChooser>

namespace Ui {
class RequestContainer;
}

class RequestContainer : public QWidget
{
    Q_OBJECT

public:
    explicit RequestContainer(RootState *rootState, QWidget *parent = nullptr);
    ~RequestContainer();

private slots:
    void onBinaryBodyOpenDiagButtonClicked();
    void onParamTabViewCurrentIndexChanged();
    void onBodyTabWidgetCurrentIndexChanged();

private:
    void onActiveRequestChanged();
private:
    RootState *m_rootState;
    Ui::RequestContainer *ui;

    KTextEditor::Editor *m_requestEditor;
    KTextEditor::Document *m_requestEditorDocument;
    KTextEditor::View *m_requestEditorView;
};

#endif // REQUESTCONTAINER_H
