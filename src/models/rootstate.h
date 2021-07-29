#ifndef ROOTSTATE_H
#define ROOTSTATE_H

#include "request.h"

#include <QObject>
#include <QSharedPointer>

class RootState : public QObject {
    Q_OBJECT
    Q_PROPERTY(RequestPtr activeRequest READ activeRequest WRITE setActiveRequest NOTIFY activeRequestChanged)
public:
    explicit RootState(QObject* parent = nullptr);

    RequestPtr activeRequest() const;
    void setActiveRequest(RequestPtr newActiveRequest);

    const QList<RequestPtr>& requestList() const;

    void addActiveRequest(RequestPtr req);
    void removeFromRequestList(RequestPtr req);
    void removeFromRequestList(int idx);
    void swapRequestListItemsAt(int i, int j);
signals:
    void activeRequestChanged();
    void requestListRemoved(int idx);
    void requestListAdded(int idx);

private:
    RequestPtr m_activeRequest;
    QList<RequestPtr> m_requestList;
};

typedef QSharedPointer<RootState> RootStatePtr;

#endif // ROOTSTATE_H
