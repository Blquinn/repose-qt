#ifndef REQUESTCONTAINER_H
#define REQUESTCONTAINER_H

#include "paramtable.h"

#include <QWidget>

#include <KTextEditor/Document>
#include <KTextEditor/Editor>
#include <KTextEditor/View>

#include <src/models/rootstate.h>
//#include <KTextEditor/EditorChooser>

namespace Ui {
class RequestContainer;
}

class RequestContainer : public QWidget {
    Q_OBJECT

public:
    explicit RequestContainer(RootState* rootState, QWidget* parent = nullptr);
    ~RequestContainer();

    QString body() { return m_requestEditorDocument->text(); }
private slots:
    void onBinaryBodyOpenDiagButtonClicked();
    void onParamTabViewCurrentIndexChanged();
    void onBodyTabWidgetCurrentIndexChanged();
    void onBinaryBodyChanged();

private:
    void onActiveRequestChanged();

private:
    RootState* m_rootState;
    Ui::RequestContainer* ui;

    KTextEditor::Editor* m_requestEditor;
    KTextEditor::Document* m_requestEditorDocument;
    KTextEditor::View* m_requestEditorView;
    ParamTable* m_paramsTable;
    ParamTable* m_headersTable;
    ParamTable* m_formDataTable;
    ParamTable* m_formUrlTable;
};

#endif // REQUESTCONTAINER_H
