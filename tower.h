#ifndef TOWER_H
#define TOWER_H

#include <QPoint>
#include <QSize>
#include <QPixmap>
#include <QObject>


class QPainter;
class Enemy;
class GameWindow;
class QTimer;

class Tower : public QObject
{
    Q_OBJECT
public:
    Tower(QPoint pos, GameWindow *game, const QPixmap &sprite = QPixmap(":/images/tower1.png"));
    ~Tower();

    void draw(QPainter *painter) const;
    void checkEnemyInRange();
    void targetKilled();
    void attackEnemy();
    void chooseEnemyForAttack(Enemy *enemy);
    void removeBullet();
    void damageEnemy();
    void lostSightOfEnemy();
    virtual int gettowertype();
    virtual int getlevel();

private slots://槽函数，对不同类的塔有不同的武器子弹，所以先在此用虚函数
    virtual void shootWeapon();

    protected:
    int             m_towertype;
    bool			m_attacking;
    int				m_attackRange;	// 代表塔可以攻击到敌人的距离
    int				m_damage;		// 代表攻击敌人时造成的伤害
    int				m_fireRate;		// 代表再次攻击敌人的时间间隔
    qreal			m_rotationSprite;

    Enemy *			m_chooseEnemy;
    GameWindow *	m_game;
    QTimer *		m_fireRateTimer;

    const QPoint	m_pos;
    const QPixmap	m_sprite;

    static const QSize ms_fixedSize;
};
class Tower1 : public Tower
{
    Q_OBJECT
public:
    Tower1(QPoint pos, GameWindow *game, const QPixmap &sprite = QPixmap(":/images/tower1.png"));
    ~Tower1();
    virtual int gettowertype();
    virtual int getlevel();
protected slots:
    virtual void shootWeapon();

};
class Tower1_2 : public Tower1
{
    Q_OBJECT
public:
    Tower1_2(QPoint pos, GameWindow *game, const QPixmap &sprite = QPixmap(":/images/tower1-2.png"));
    ~Tower1_2();
    virtual int gettowertype();
    virtual int getlevel();
protected slots:
    virtual void shootWeapon();
};



class Tower2 : public Tower
{
    Q_OBJECT
public:
    Tower2(QPoint pos, GameWindow *game, const QPixmap &sprite = QPixmap(":/images/tower2.png"));
    ~Tower2();
    virtual int gettowertype();
    virtual int getlevel();
protected slots:
   virtual void shootWeapon();

};

class Tower2_2 : public Tower2
{
    Q_OBJECT
public:
    Tower2_2(QPoint pos, GameWindow *game, const QPixmap &sprite = QPixmap(":/images/tower2-2.png"));
    ~Tower2_2();
    virtual int gettowertype();
    virtual int getlevel();
protected slots:
   virtual void shootWeapon();

};

class Tower3 : public Tower
{
    Q_OBJECT
public:
    Tower3(QPoint pos, GameWindow *game, const QPixmap &sprite = QPixmap(":/images/tower3.png"));
    ~Tower3();
    virtual int gettowertype();
    virtual int getlevel();
protected slots:
   virtual void shootWeapon();

};

class Tower3_2 : public Tower3
{
    Q_OBJECT
public:
    Tower3_2(QPoint pos, GameWindow *game, const QPixmap &sprite = QPixmap(":/images/tower3-2.png"));
    ~Tower3_2();
    virtual int gettowertype();
    virtual int getlevel();
protected slots:
   virtual void shootWeapon();

};

class Tower4 : public Tower
{
    Q_OBJECT
public:
    Tower4(QPoint pos, GameWindow *game, const QPixmap &sprite = QPixmap(":/images/tower4-1.png"));
    ~Tower4();
    virtual int gettowertype();
    virtual int getlevel();
protected slots:
   virtual void shootWeapon();

};

class Tower4_2 : public Tower4
{
    Q_OBJECT
public:
    Tower4_2(QPoint pos, GameWindow *game, const QPixmap &sprite = QPixmap(":/images/tower4.png"));
    ~Tower4_2();
    virtual int gettowertype();
    virtual int getlevel();
protected slots:
   virtual void shootWeapon();

};
#endif // TOWER_H
