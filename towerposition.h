#ifndef TOWERPOSITION_H
#define TOWERPOSITION_H
#include <QPoint>
#include <QPixmap>
#include <QPainter>
#include "tower.h"

class TowerPosition
{
public:
    TowerPosition(QPoint pos, const QPixmap &sprite = QPixmap("://images/base.png"));

    void setHasTower(bool hasTower = true);

    void setHasnotTower(bool hasnotTower = false);
    bool hasTower() const;
    const QPoint centerPos() const;
    bool containPoint(const QPoint &pos) const;
    void draw(QPainter *painter) ;
    int Pos11x(){return m_pos.x();}
    int Pos11y(){return m_pos.y();}
    Tower*       m_tower;

private:
    QPoint		m_pos;
    bool		m_hasTower;
    bool		m_hasNotTower;
    QPixmap		m_sprite;

    static const QSize ms_fixedSize;
};

#endif // TOWERPOSITION_H
