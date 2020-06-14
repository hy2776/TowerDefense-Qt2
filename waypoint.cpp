#include "waypoint.h"



WayPoint::WayPoint(QPoint pos)
    : m_pos(pos)
    , m_nextWayPoint(nullptr)
{
}

void WayPoint::setNextWayPoint(WayPoint *nextPoint)
{
    m_nextWayPoint = nextPoint;
}

WayPoint* WayPoint::nextWayPoint() const
{
    return m_nextWayPoint;
}

const QPoint WayPoint::pos() const
{
    return m_pos;
}

void WayPoint::draw(QPainter *painter) const
{
    painter->save();
    painter->setPen(QColor(57,170,198));
    painter->drawEllipse(m_pos, 6, 6);
    painter->drawEllipse(m_pos, 2, 2);

    if (m_nextWayPoint)
        painter->drawLine(m_pos, m_nextWayPoint->m_pos);
    painter->restore();
}
