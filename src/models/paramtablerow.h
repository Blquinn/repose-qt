#ifndef PARAMTABLEROW_H
#define PARAMTABLEROW_H

#include <QString>

class ParamTableRow {
public:
    ParamTableRow();
    ParamTableRow(QString key, QString value, QString description);

    const QString& key() const;
    void setKey(const QString& newKey);

    const QString& value() const;
    void setValue(const QString& newValue);

    const QString& description() const;
    void setDescription(const QString& newDescription);

    bool isEmpty() const { return m_key.isEmpty() && m_value.isEmpty() && m_description.isEmpty(); }

private:
    QString m_key;
    QString m_value;
    QString m_description;
};

#endif // PARAMTABLEROW_H
