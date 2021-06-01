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
