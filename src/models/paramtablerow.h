#ifndef PARAMTABLEROW_H
#define PARAMTABLEROW_H

#include <QString>

class ParamTableRow
{
public:
    ParamTableRow();
    ParamTableRow(QString key, QString value, QString description);

    QString key() const { return m_key; }
    QString value() const { return m_value; }
    QString description() const { return m_description; }

    void setKey(QString key) { m_key = key; }
    void setValue(QString value) { m_value = value; }
    void setDescription(QString description) { m_description = description; }

    bool isEmpty() const { return m_key.isEmpty() && m_value.isEmpty() && m_description.isEmpty(); }
private:
    QString m_key;
    QString m_value;
    QString m_description;
};

#endif // PARAMTABLEROW_H
