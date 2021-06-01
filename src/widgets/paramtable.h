#ifndef PARAMTABLE_H
#define PARAMTABLE_H

#include <QWidget>

#include <src/models/paramtablemodel.h>

namespace Ui {
class ParamTable;
}

class ParamTable : public QWidget
{
    Q_OBJECT

public:
    explicit ParamTable(QWidget *parent = nullptr);
    ~ParamTable();

private:
    Ui::ParamTable *ui;
    ParamTableModel *m_model;
};

#endif // PARAMTABLE_H
