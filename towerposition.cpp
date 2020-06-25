#include "towerposition.h"


const QSize TowerPosition::ms_fixedSize(110, 110);

TowerPosition::TowerPosition(QPoint pos, const QPixmap &sprite/* = QPixmap(":/images/base.png")*/)
    : m_pos(pos)
    , m_hasTower(false)
    , m_sprite(sprite)
{
}

const QPoint TowerPosition::centerPos() const
{
    QPoint offsetPoint(ms_fixedSize.width() / 2, ms_fixedSize.height() / 2);
    return m_pos + offsetPoint;
}

bool TowerPosition::containPoint(const QPoint &pos) const
{
    bool isXInHere = m_pos.x() < pos.x() && pos.x() < (m_pos.x() + ms_fixedSize.width());
    bool isYInHere = m_pos.y() < pos.y() && pos.y() < (m_pos.y() + ms_fixedSize.height());
    return isXInHere && isYInHere;
}

bool TowerPosition::hasTower() const
{
    return m_hasTower;
}

void TowerPosition::setHasTower(bool hasTower/* = true*/)
{
    m_hasTower = hasTower;
}

void TowerPosition::setHasnotTower(bool hasnotTower)
{
    m_hasTower = hasnotTower;
}

void TowerPosition::draw(QPainter *painter)
{
    painter->drawPixmap(m_pos.x(), m_pos.y(), m_sprite);
}

