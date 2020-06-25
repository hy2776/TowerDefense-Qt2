#include "tower.h"
#include "enemy.h"
#include "bullet.h"
#include "mainwindow.h"
#include "utility.h"
#include <QPainter>
#include <QColor>
#include <QTimer>
#include <QVector2D>
#include <QtMath>

const QSize Tower::ms_fixedSize(107, 95);

Tower::Tower(QPoint pos, GameWindow *game, const QPixmap &sprite/* = QPixmap(":/image/tower1_1.png"*/)
    : m_attacking(false)
    , m_attackRange(200)
    , m_damage(10)
    , m_fireRate(1000)
    , m_rotationSprite(0.0)
    , m_chooseEnemy(NULL)
    , m_game(game)
    , m_pos(pos)
    , m_sprite(sprite)
{
    m_fireRateTimer = new QTimer(this);
    connect(m_fireRateTimer, SIGNAL(timeout()), this, SLOT(shootWeapon()));
}

Tower::~Tower()
{
    delete m_fireRateTimer;
    m_fireRateTimer = NULL;
}

void Tower::checkEnemyInRange()
{
    if (m_chooseEnemy)
    {
        // 这种情况下,需要旋转炮台对准敌人
        // 向量标准化
        QVector2D normalized(m_chooseEnemy->pos() - m_pos);
        normalized.normalize();
        m_rotationSprite = qRadiansToDegrees(qAtan2(normalized.y(), normalized.x())) - 90;

        // 如果敌人脱离攻击范围
        if (!collisionWithCircle(m_pos, m_attackRange, m_chooseEnemy->pos(), 1))
            lostSightOfEnemy();
    }
    else
    {
        // 遍历敌人,看是否有敌人在攻击范围内
        QList<Enemy *> enemyList = m_game->enemyList();
        foreach (Enemy *enemy, enemyList)
        {
            if (collisionWithCircle(m_pos, m_attackRange, enemy->pos(), 1))
            {
                chooseEnemyForAttack(enemy);
                break;
            }
        }
    }
}

void Tower::draw(QPainter *painter) const
{
    painter->save();
    painter->setPen(Qt::white);
    // 绘制攻击范围
    painter->drawEllipse(m_pos, m_attackRange, m_attackRange);

    // 绘制偏转坐标,由中心+偏移=左上
    static const QPoint offsetPoint(-ms_fixedSize.width() /2, -ms_fixedSize.height() / 2);
    // 绘制炮塔并选择炮塔
    painter->translate(m_pos);
    painter->rotate(m_rotationSprite);
    painter->drawPixmap(offsetPoint, m_sprite);
    painter->restore();
}
int Tower::gettowertype()
{
    return 1;
}
int Tower::getlevel()
{
    return 1;
}

void Tower::attackEnemy()
{
    m_fireRateTimer->start(m_fireRate);
}

void Tower::chooseEnemyForAttack(Enemy *enemy)
{
    m_chooseEnemy = enemy;
    attackEnemy();
    m_chooseEnemy->getAttacked(this);
}

void Tower::shootWeapon()
{
    Bullet *bullet = new Bullet(m_pos, m_chooseEnemy->pos(), m_damage, m_chooseEnemy, m_game);
    bullet->move();
    m_game->addBullet(bullet);
}

void Tower::targetKilled()
{
    if (m_chooseEnemy)
        m_chooseEnemy = NULL;

    m_fireRateTimer->stop();
    m_rotationSprite = 0.0;
}

void Tower::lostSightOfEnemy()
{
    m_chooseEnemy->gotLostSight(this);
    if (m_chooseEnemy)
        m_chooseEnemy = NULL;

    m_fireRateTimer->stop();
    m_rotationSprite = 0.0;
}
Tower1::Tower1(QPoint pos, GameWindow *game, const QPixmap &sprite)
    : Tower(pos, game, sprite)
{
    m_attackRange=150;
    m_damage=10;
}
Tower1::~Tower1()
{
}
void Tower1::shootWeapon()
{
    Bullet *bullet = new Bullet(m_pos, m_chooseEnemy->pos(), m_damage, m_chooseEnemy, m_game);
    bullet->move();
    m_game->addBullet(bullet);
}
int Tower1::gettowertype()
{
    return 1;
}
int Tower1::getlevel()
{
    return 1;
}

Tower1_2::Tower1_2(QPoint pos, GameWindow *game, const QPixmap &sprite)
    : Tower1(pos, game, sprite)
{
    m_attackRange=250;
    m_damage=15;
}
Tower1_2::~Tower1_2()
{
}
void Tower1_2::shootWeapon()
{
    Bullet *bullet = new Bullet(m_pos, m_chooseEnemy->pos(), m_damage, m_chooseEnemy, m_game);
    bullet->move();
    m_game->addBullet(bullet);
}
int Tower1_2::gettowertype()
{
    return 1;
}
int Tower1_2::getlevel()
{
    return 2;
}



Tower2::Tower2(QPoint pos, GameWindow *game, const QPixmap &sprite)
    : Tower(pos, game, sprite)
{
    m_attackRange=200;
    m_damage=15;
}
Tower2::~Tower2()
{

}
void Tower2::shootWeapon()
{
    Tower2Bullet *bullet2 = new Tower2Bullet(m_pos, m_chooseEnemy->pos(), m_damage, m_chooseEnemy, m_game);
    bullet2->move();
    m_game->addBullet(bullet2);
}
int Tower2::gettowertype()
{
    return 2;
}
int Tower2::getlevel()
{
    return 1;
}




Tower2_2::Tower2_2(QPoint pos, GameWindow *game, const QPixmap &sprite)
    : Tower2(pos, game, sprite)
{
    m_attackRange=300;
    m_damage=20;
}
Tower2_2::~Tower2_2()
{

}
void Tower2_2::shootWeapon()
{
    Tower2Bullet *bullet2 = new Tower2Bullet(m_pos, m_chooseEnemy->pos(), m_damage, m_chooseEnemy, m_game);
    bullet2->move();
    m_game->addBullet(bullet2);
}
int Tower2_2::gettowertype()
{
    return 2;
}
int Tower2_2::getlevel()
{
    return 2;
}


Tower3::Tower3(QPoint pos, GameWindow *game, const QPixmap &sprite)
    : Tower(pos, game, sprite)
{
    m_attackRange=200;
    m_damage=15;
}
Tower3::~Tower3()
{

}
void Tower3::shootWeapon()
{
    Tower3Bullet *bullet3 = new Tower3Bullet(m_pos, m_chooseEnemy->pos(), m_damage, m_chooseEnemy, m_game);
    bullet3->move();
    m_game->addBullet(bullet3);
}
int Tower3::gettowertype()
{
    return 3;
}
int Tower3::getlevel()
{
    return 1;
}




Tower3_2::Tower3_2(QPoint pos, GameWindow *game, const QPixmap &sprite)
    : Tower3(pos, game, sprite)
{
    m_attackRange=300;
    m_damage=20;
}
Tower3_2::~Tower3_2()
{

}
void Tower3_2::shootWeapon()
{
    Tower3Bullet *bullet3 = new Tower3Bullet(m_pos, m_chooseEnemy->pos(), m_damage, m_chooseEnemy, m_game);
    bullet3->move();
    m_game->addBullet(bullet3);
}
int Tower3_2::gettowertype()
{
    return 3;
}
int Tower3_2::getlevel()
{
    return 2;
}

Tower4::Tower4(QPoint pos, GameWindow *game, const QPixmap &sprite)
    : Tower(pos, game, sprite)
{
    m_attackRange=200;
    m_damage=15;
}
Tower4::~Tower4()
{

}
void Tower4::shootWeapon()
{
    Tower4Bullet *bullet4 = new Tower4Bullet(m_pos, m_chooseEnemy->pos(), m_damage, m_chooseEnemy, m_game);
    bullet4->move();
    m_game->addBullet(bullet4);
}
int Tower4::gettowertype()
{
    return 4;
}
int Tower4::getlevel()
{
    return 1;
}




Tower4_2::Tower4_2(QPoint pos, GameWindow *game, const QPixmap &sprite)
    : Tower4(pos, game, sprite)
{
    m_attackRange=300;
    m_damage=20;
}
Tower4_2::~Tower4_2()
{

}
void Tower4_2::shootWeapon()
{
    Tower4Bullet *bullet4 = new Tower4Bullet(m_pos, m_chooseEnemy->pos(), m_damage, m_chooseEnemy, m_game);
    bullet4->move();
    m_game->addBullet(bullet4);
}
int Tower4_2::gettowertype()
{
    return 4;
}
int Tower4_2::getlevel()
{
    return 2;
}


