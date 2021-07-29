#include "rootstate.h"

RootState::RootState(QObject* parent)
    : QObject(parent)
    , m_activeRequest(nullptr)
    , m_requestList()
{
}

RequestPtr RootState::activeRequest() const
{
    return m_activeRequest;
}

void RootState::setActiveRequest(RequestPtr newActiveRequest)
{
    if (m_activeRequest == newActiveRequest)
        return;
    m_activeRequest = newActiveRequest;
    emit activeRequestChanged();
}

const QList<RequestPtr>& RootState::requestList() const
{
    return m_requestList;
}

void RootState::addActiveRequest(RequestPtr req)
{
    if (m_requestList.contains(req))
        return;

    m_requestList.append(req);
    emit requestListAdded(m_requestList.length() - 1);
}

void RootState::removeFromRequestList(RequestPtr req)
{
    removeFromRequestList(m_requestList.indexOf(req));
}

void RootState::removeFromRequestList(int idx)
{
    if (idx < 0 || idx > m_requestList.length() - 1)
        return;

    m_requestList.removeAt(idx);
    emit requestListRemoved(idx);
}

void RootState::swapRequestListItemsAt(int i, int j)
{
    m_requestList.swapItemsAt(i, j);
}
