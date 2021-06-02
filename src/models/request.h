#ifndef REQUEST_H
#define REQUEST_H

#include <QObject>
#include <QDateTime>

class Request : public QObject
{
    Q_OBJECT
public:
    explicit Request(QObject *parent = nullptr);

    const QString &method() const;
    void setMethod(const QString &newMethod);

    const QString &url() const;
    void setUrl(const QString &newUrl);

    const QDateTime &startRequestTime() const;
    void setStartRequestTime(const QDateTime &newStartRequestTime);

signals:

private:
    QString m_url;
    QString m_method;
    QDateTime m_startRequestTime;
};

Q_DECLARE_METATYPE(Request*)

#endif // REQUEST_H
