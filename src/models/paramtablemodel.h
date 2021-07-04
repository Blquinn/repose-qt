#ifndef PARAMTABLEMODEL_H
#define PARAMTABLEMODEL_H

#include <QAbstractTableModel>
#include <QSharedPointer>

#include "paramtablerow.h"

class ParamTableModel : public QAbstractTableModel
{
public:
    explicit ParamTableModel(QObject *parent = nullptr);

    void addEmptyRow();

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
//    bool insertRows(int position, int rows, const QModelIndex &index) override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;
//    bool removeRows(int position, int rows, const QModelIndex &index) override;
private:
    QList<ParamTableRow> m_paramList;
};

typedef QSharedPointer<ParamTableModel> ParamTableModelPtr;

Q_DECLARE_METATYPE(ParamTableModelPtr)

#endif // PARAMTABLEMODEL_H
