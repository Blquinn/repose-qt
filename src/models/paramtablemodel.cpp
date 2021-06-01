#include "paramtablemodel.h"

ParamTableModel::ParamTableModel(QObject *parent) : QAbstractTableModel(parent)
  , m_paramList()
{
}

void ParamTableModel::addEmptyRow() {
    beginInsertRows(QModelIndex(), m_paramList.length(), m_paramList.length()+1);
    m_paramList.append(ParamTableRow());
    endInsertRows();
}

int ParamTableModel::rowCount(const QModelIndex &parent) const
{
    return parent.isValid() ? 0 : m_paramList.length();
}

int ParamTableModel::columnCount(const QModelIndex &parent) const
{
    return parent.isValid() ? 0 : 3;
}

QVariant ParamTableModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || role != Qt::DisplayRole) return QVariant();

    if (index.row() >= m_paramList.size() || index.row() < 0) return QVariant();

    const auto &row = m_paramList[index.row()];
    switch (index.column()) {
    case 0:
        return row.key();
    case 1:
        return row.value();
    case 2:
        return row.description();
    default:
        return QVariant();
    }
}

bool ParamTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!index.isValid() || role != Qt::EditRole) return false;

    if (index.row() > m_paramList.size() || index.row() < 0) return false;

    if (value.type() != QVariant::Type::String) return false;

    auto param = m_paramList[index.row()];
    auto val = value.toString();

    switch (index.column()) {
    case 0:
        param.setKey(val);
        break;
    case 1:
        param.setValue(val);
        break;
    case 2:
        param.setDescription(val);
        break;
    }

    m_paramList[index.row()] = param;

    emit dataChanged(index, index, {Qt::DisplayRole, Qt::EditRole});

    // TODO: Fix this inserting multiple empty rows.
    if (index.row() != m_paramList.length() && param.isEmpty()) {
        beginRemoveRows(index, index.row(), index.row()+1);
        m_paramList.removeAt(index.row());
        endRemoveRows();
    }

    if (m_paramList.empty() || !m_paramList.last().isEmpty())
        addEmptyRow();

    return true;
}

QVariant ParamTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole) return QVariant();

    if (orientation != Qt::Orientation::Horizontal) return QVariant();

    switch (section) {
    case 0:
        return "Key";
    case 1:
        return "Value";
    case 2:
        return "Description";
    default:
        return QVariant();
    }
}

bool ParamTableModel::insertRows(int position, int rows, const QModelIndex &index)
{
    Q_UNUSED(index);
    beginInsertRows(QModelIndex(), position, position + rows - 1);

    for (int row = 0; row < rows; ++row)
        m_paramList.insert(position, ParamTableRow());

    endInsertRows();
    return true;
}

bool ParamTableModel::removeRows(int position, int rows, const QModelIndex &index)
{
    Q_UNUSED(index);
    beginRemoveRows(QModelIndex(), position, position + rows - 1);

    for (int row = 0; row < rows; ++row)
        m_paramList.removeAt(position);

    endRemoveRows();
    return true;
}

Qt::ItemFlags ParamTableModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::ItemIsEnabled;

    return QAbstractTableModel::flags(index) | Qt::ItemIsEditable;
}
