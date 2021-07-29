#include "paramtablerow.h"

ParamTableRow::ParamTableRow()
{
    ParamTableRow("", "", "");
}

ParamTableRow::ParamTableRow(QString key, QString value, QString description)
{
    m_key = key;
    m_value = value;
    m_description = description;
}

const QString& ParamTableRow::key() const
{
    return m_key;
}

void ParamTableRow::setKey(const QString& newKey)
{
    m_key = newKey;
}

const QString& ParamTableRow::value() const
{
    return m_value;
}

void ParamTableRow::setValue(const QString& newValue)
{
    m_value = newValue;
}

const QString& ParamTableRow::description() const
{
    return m_description;
}

void ParamTableRow::setDescription(const QString& newDescription)
{
    m_description = newDescription;
}
