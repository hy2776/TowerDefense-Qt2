#ifndef ENEMY_H
#define ENEMY_H

#include <QObject>
#include <QPoint>
#include <QSize>
#include <QPixmap>
#include "gamewindow.h"
#include "bullet.h"

class WayPoint;
class QPainter;
class MainWindow;
class Tower;
class GameWindow;
class Bullet;

class Enemy : public QObject{
    Q_OBJECT
public:
    Enemy(WayPoint *startWayPoint, GameWindow *game, const QPixmap &sprite = QPixmap(":/images/enemy1.png"));
    virtual ~Enemy();
    void draw(QPainter *painter) const;
    void move();
    void getDamage(Bullet *bullet);
    void getRemoved();
    void canRemove();
    void getFireDamage(int damage);
    void getAttacked(Tower *attacker);
    void gotLostSight(Tower *attacker);
    QPoint pos() const;

    bool            m_active;
    int             fire; //当前是否受到火焰伤害
    int             fireLevel;//火焰效果持续时间
    int             ice; //
    int             iceLevel;//火焰效果持续时间
    int				m_maxHp;
    int				m_currentHp;
    int             HPdamage;//对“萝卜”的伤害
    int             enemyKind;
    int             award;
    qreal           fireattackLevel;
    qreal           antiSlowspeed;
    qreal           m_normalSpeed; //正常速度
    qreal           fireattack; //每0.5秒钟受到多少火焰伤害
    qreal           m_slowSpeed; //寒冰状态的速度
    qreal			m_walkingSpeed;//当前行走速度
    qreal			m_rotationSprite;
    QPoint			m_pos;
    WayPoint *		m_destinationWayPoint;
    GameWindow *    m_game;
    QList<Tower *>	m_attackedTowersList;
    const QPixmap	m_sprite;
    static const QSize ms_fixedSize;
public slots:
    void doActivate();
};

class normalEnemy:public Enemy{
    Q_OBJECT
public:
    normalEnemy(WayPoint *startWayPoint, GameWindow *game, const QPixmap &sprite = QPixmap(":/images/enemy1.png"));
};

class iceEnemy:public Enemy{
    Q_OBJECT
public:
    iceEnemy(WayPoint *startWayPoint, GameWindow *game, const QPixmap &sprite = QPixmap(":/images/enemy2.png"));
};

class fireEnemy:public Enemy{
    Q_OBJECT
public:
    fireEnemy(WayPoint *startWayPoint, GameWindow *game, const QPixmap &sprite = QPixmap(":/images/enemy3.png"));
};

class fastEnemy:public Enemy{
    Q_OBJECT
public:
    fastEnemy(WayPoint *startWayPoint, GameWindow *game, const QPixmap &sprite = QPixmap(":/images/monster4.png"));
};

class bossEnemy:public Enemy{
    Q_OBJECT
public:
    bossEnemy(WayPoint *startWayPoint, GameWindow *game, const QPixmap &sprite = QPixmap(":/images/monster1.png"));
};

#endif // ENEMY_H
