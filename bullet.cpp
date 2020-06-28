#include "bullet.h"
#include "enemy.h"
#include "mainwindow.h"
#include <QPainter>
#include <QPropertyAnimation>

const QSize Bullet::ms_fixedSize(26, 26);

Bullet::Bullet(QPoint startPos, QPoint targetPoint, int damage, Enemy *target,
               GameWindow *game, int kind, int fire, qreal slow, const QPixmap &sprite/* = QPixmap(":/image/noramlbullet.png")*/)
    : m_startPos(startPos)
    , m_targetPos(targetPoint)
    , m_sprite(sprite)
    , m_currentPos(startPos)
    , m_target(target)
    , m_game(game)
    , m_damage(damage)
    , bulletKind(kind)
    , fire_attack(fire)
    , slow_speed(slow)
{}


void Bullet::draw(QPainter *painter) const{
    painter->drawPixmap(m_currentPos, m_sprite);
}

void Bullet::move(){
    //300毫秒内击中敌人
    static const int duration = 300;
    //不同子弹移动速度可以不同
    QPropertyAnimation *animation = new QPropertyAnimation(this, "m_currentPos");
    animation->setDuration(duration);
    animation->setStartValue(m_startPos);
    animation->setEndValue(m_targetPos);
    connect(animation, SIGNAL(finished()), this, SLOT(hitTarget()));

    animation->start();
}

void Bullet::hitTarget(){
    // 这样处理的原因是:
    // 可能多个炮弹击中敌人,而其中一个将其消灭,导致敌人delete
    // 后续炮弹再攻击到的敌人就是无效内存区域
    // 因此先判断下敌人是否还有效
    if (m_game->enemyList().indexOf(m_target) != -1)
        m_target->getDamage(this);
    m_game->removedBullet(this);
}

void Bullet::setCurrentPos(QPoint pos){
    m_currentPos = pos;
}

QPoint Bullet::currentPos() const{
    return m_currentPos;
}
Tower1Bullet::Tower1Bullet(QPoint startPos, QPoint targetPoint, int damage, Enemy *target, GameWindow *game, const QPixmap &sprite)
    :Bullet(startPos, targetPoint, damage, target, game)
{

}

Tower2Bullet::Tower2Bullet(QPoint startPos, QPoint targetPoint, int damage, Enemy *target, GameWindow *game, int kind, int fireattack, const QPixmap &sprite)
    :Bullet(startPos, targetPoint, damage, target, game, kind, fireattack, 1, sprite)
{

}

Tower3Bullet::Tower3Bullet(QPoint startPos, QPoint targetPoint, int damage, Enemy *target, GameWindow *game, int kind, qreal slow, const QPixmap &sprite)
    :Bullet(startPos, targetPoint, damage, target, game, kind, 0, slow, sprite)
{

}

Tower4Bullet::Tower4Bullet(QPoint startPos, QPoint targetPoint, int damage, Enemy *target, GameWindow *game, int kind,const QPixmap &sprite)
    :Bullet(startPos, targetPoint, damage, target, game, kind, 0, 1, sprite)
{

}
