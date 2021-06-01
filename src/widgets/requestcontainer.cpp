#include "requestcontainer.h"
#include "ui_requestcontainer.h"

#include "QVBoxLayout"
#include "paramtable.h"

RequestContainer::RequestContainer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RequestContainer)
{
    ui->setupUi(this);

    m_requestEditor = KTextEditor::Editor::instance();
    m_requestEditorDocument = m_requestEditor->createDocument(0);
    m_requestEditorView = m_requestEditorDocument->createView(this);
    m_requestEditorView->setContentsMargins(0, 0, 0, 0);

    auto requestEditorLayout = new QVBoxLayout(this);
    requestEditorLayout->setMargin(0);
    requestEditorLayout->setSpacing(0);
    ui->bodyRaw->setLayout(requestEditorLayout);
    requestEditorLayout->addWidget(m_requestEditorView);

    auto paramTableLayout = new QVBoxLayout(this);
    paramTableLayout->setMargin(0);
    paramTableLayout->setSpacing(0);
    ui->paramsTab->setLayout(paramTableLayout);
    auto pt = new ParamTable(this);
    paramTableLayout->addWidget(pt);

    auto headerTableLayout = new QVBoxLayout(this);
    headerTableLayout->setMargin(0);
    headerTableLayout->setSpacing(0);
    ui->headersTab->setLayout(headerTableLayout);
    auto ht = new ParamTable(this);
    headerTableLayout->addWidget(ht);

    auto formDataTableLayout = new QVBoxLayout(this);
    formDataTableLayout->setMargin(0);
    formDataTableLayout->setSpacing(0);
    ui->bodyFormData->setLayout(formDataTableLayout);
    auto ft = new ParamTable(this);
    formDataTableLayout->addWidget(ft);

    auto urlEncodedTableLayout = new QVBoxLayout(this);
    urlEncodedTableLayout->setMargin(0);
    urlEncodedTableLayout->setSpacing(0);
    ui->bodyFormUrlEncoded->setLayout(urlEncodedTableLayout);
    auto ut = new ParamTable(this);
    urlEncodedTableLayout->addWidget(ut);
}

RequestContainer::~RequestContainer()
{
    delete ui;
}
