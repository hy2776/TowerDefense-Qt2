#ifndef BULLET_H
#define BULLET_H

#include <QPoint>
#include <QSize>
#include <QPixmap>
#include <QObject>
#include"gamewindow.h"

class QPainter;
class Enemy;
class Enemy1;
class Enemy2;
class MainWindow;
class GameWindow;


class Bullet : public QObject
{
    Q_OBJECT
    //Qt动画效果
    Q_PROPERTY(QPoint m_currentPos READ currentPos WRITE setCurrentPos)

public:
    Bullet(QPoint startPos, QPoint targetPoint, int damage, Enemy *target, GameWindow *game, int kind = 0, int fire = 0, qreal slow = 1, const QPixmap &sprite = QPixmap(":/images/tower4bullet.png"));

    void draw(QPainter *painter) const;
    void move();
    void setCurrentPos(QPoint pos);
    QPoint currentPos() const;
    friend class Enemy;

protected slots:
    void hitTarget();

protected:
    const QPoint	m_startPos;
    const QPoint	m_targetPos;
    const QPixmap	m_sprite;
    QPoint			m_currentPos;
    Enemy *			m_target;
    GameWindow *    m_game;
    int				m_damage;
    int             bulletKind;
    int             fire_attack;
    qreal           slow_speed;

    static const QSize ms_fixedSize;
};

class Tower1Bullet: public Bullet
{
    Q_OBJECT

public:
    Tower1Bullet(QPoint startPos, QPoint targetPoint, int damage, Enemy *target, GameWindow *game, const QPixmap &sprite = QPixmap(":/images/tower1bullet.png"));
};

class Tower2Bullet: public Bullet
{
    Q_OBJECT

public:
    Tower2Bullet(QPoint startPos, QPoint targetPoint, int damage, Enemy *target, GameWindow *game, int kind = 1, int fire = 1, const QPixmap &sprite = QPixmap(":/images/tower2bullet.png"));

};

class Tower3Bullet: public Bullet
{
    Q_OBJECT

public:
    Tower3Bullet(QPoint startPos, QPoint targetPoint, int damage, Enemy *target, GameWindow *game, int kind = 2, qreal slow = 0.5, const QPixmap &sprite = QPixmap(":/images/tower3bullet.png"));

};

class Tower4Bullet: public Bullet
{
    Q_OBJECT

public:
    Tower4Bullet(QPoint startPos, QPoint targetPoint, int damage, Enemy *target, GameWindow *game, int kind = 3,const QPixmap &sprite = QPixmap(":/images/tower4bullet.png"));

};

#endif // BULLET_H
