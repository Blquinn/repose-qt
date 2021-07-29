#include "paramtablemodel.h"

#include <QSet>
#include <QUrlQuery>

ParamTableModel::ParamTableModel(QObject* parent)
    : QAbstractTableModel(parent)
    , m_paramList()
{
}

void ParamTableModel::addEmptyRow()
{
    beginInsertRows(QModelIndex(), m_paramList.length(), m_paramList.length());
    m_paramList.append(ParamTableRow());
    endInsertRows();
}

void ParamTableModel::upsertRowByKey(ParamTableRow row)
{
    int idx = 0;
    for (auto&& r : m_paramList) {
        if (r.key().compare(row.key(), Qt::CaseInsensitive) == 0) {
            r.setValue(row.value());
            emit dataChanged(index(idx, Columns::Key), index(idx, Columns::Description));

            return;
        }

        idx++;
    }

    appendRow(row);
}

void ParamTableModel::appendRow(ParamTableRow row)
{
    Q_ASSERT(m_paramList.last().isEmpty());

    auto idx = m_paramList.length() - 1;
    m_paramList[idx] = row;
    emit dataChanged(index(idx, Columns::Key), index(idx, Columns::Description));

    addEmptyRow();
}

void ParamTableModel::removeRowByKey(QString key)
{
    int idx = 0;
    for (auto&& r : m_paramList) {
        if (r.key().compare(key, Qt::CaseInsensitive) == 0) {
            beginRemoveRows(QModelIndex(), idx, idx);
            m_paramList.removeAt(idx);
            endRemoveRows();

            return;
        }

        idx++;
    }
}

QString ParamTableModel::urlEncode()
{
    QUrlQuery query;
    for (auto&& p : m_paramList) {
        if (p.key().isEmpty() && p.value().isEmpty())
            continue;

        query.addQueryItem(p.key(), p.value());
    }
    return query.toString();
}

void ParamTableModel::updateFromQuery(const QList<QPair<QString, QString>>& queryItems)
{
    QList<ParamTableRow> newRows;

    for (auto&& item : queryItems) {
        ParamTableRow newRow(item.first, item.second, "");
        for (auto&& row : m_paramList) {
            if (item.first == row.key()) { // Keep description.
                newRow.setDescription(row.description());
                break;
            }
        }
        newRows.append(newRow);
    }

    newRows.append(ParamTableRow());

    beginResetModel();
    m_paramList = newRows;
    endResetModel();
}

int ParamTableModel::rowCount(const QModelIndex& parent) const
{
    return parent.isValid() ? 0 : m_paramList.length();
}

int ParamTableModel::columnCount(const QModelIndex& parent) const
{
    return parent.isValid() ? 0 : 3;
}

QVariant ParamTableModel::data(const QModelIndex& index, int role) const
{
    if (!index.isValid() || !(role == Qt::DisplayRole || role == Qt::EditRole))
        return QVariant();

    if (index.row() >= m_paramList.size() || index.row() < 0)
        return QVariant();

    const auto& row = m_paramList[index.row()];
    switch (index.column()) {
    case Columns::Key:
        return row.key();
    case Columns::Value:
        return row.value();
    case Columns::Description:
        return row.description();
    default:
        return QVariant();
    }
}

bool ParamTableModel::setData(const QModelIndex& index, const QVariant& value, int role)
{
    if (!index.isValid() || role != Qt::EditRole)
        return false;

    if (index.row() > m_paramList.size() || index.row() < 0)
        return false;

    if (value.type() != QVariant::Type::String)
        return false;

    auto param = m_paramList[index.row()];
    auto val = value.toString();

    switch (index.column()) {
    case Columns::Key:
        param.setKey(val);
        break;
    case Columns::Value:
        param.setValue(val);
        break;
    case Columns::Description:
        param.setDescription(val);
        break;
    }

    m_paramList[index.row()] = param;

    emit dataChanged(index, index, { Qt::DisplayRole, Qt::EditRole });

    if (index.row() != m_paramList.length() - 1 && param.isEmpty()) {
        beginRemoveRows(QModelIndex(), index.row(), index.row());
        m_paramList.removeAt(index.row());
        endRemoveRows();
        return true;
    }

    if (!m_paramList.last().isEmpty())
        addEmptyRow();

    return true;
}

QVariant ParamTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation != Qt::Orientation::Horizontal)
        return QVariant();

    switch (section) {
    case Columns::Key:
        return "Key";
    case Columns::Value:
        return "Value";
    case Columns::Description:
        return "Description";
    default:
        return QVariant();
    }
}

Qt::ItemFlags ParamTableModel::flags(const QModelIndex& index) const
{
    if (!index.isValid())
        return Qt::ItemIsEnabled;

    return QAbstractTableModel::flags(index) | Qt::ItemIsEditable;
}
