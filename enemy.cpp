#include "enemy.h"
#include "waypoint.h"
#include "tower.h"
#include "utility.h"
#include "mainwindow.h"
#include "audioplayer.h"
#include <QPainter>
#include <QColor>
#include <QDebug>
#include <QMatrix>
#include <QVector2D>
#include <QtMath>


//血条长度
static const int Health_Bar_Width = 100;
const QSize Enemy::ms_fixedSize(10, 10);
Enemy::Enemy(WayPoint *startWayPoint, GameWindow *game, const QPixmap &sprite/* = QPixmap(":/images/monster1.png")*/)
    : QObject(0)
    , m_active(false)//决定painter是否显示enemy对象，不可通过m_active设置enemy暂停移动
    , fire(0)
    , ice(0)
    , m_maxHp(60)
    , m_currentHp(60)
    , enemyKind(1)
    , award(200)
    , fireattackLevel(1.0)
    , antiSlowspeed(1.0)
    , m_normalSpeed(2.0)
    , m_slowSpeed(1.0)
    , m_walkingSpeed(2.0)
    , m_rotationSprite(0.0)
    , m_pos(startWayPoint->pos())
    , m_destinationWayPoint(startWayPoint->nextWayPoint())
    , m_game(game)
    , m_sprite(sprite)
{}
Enemy::~Enemy(){
    m_attackedTowersList.clear();
    m_destinationWayPoint = NULL;
    m_game = NULL;
}
void Enemy::doActivate(){
    m_active = true;
}
void Enemy::move(){
    if (!m_active)
        return;
    if (collisionWithCircle(m_pos, 1, m_destinationWayPoint->pos(), 1)){
        // 敌人抵达了一个航点
        if (m_destinationWayPoint->nextWayPoint()){
            // 还有下一个航点
            m_pos = m_destinationWayPoint->pos();
            m_destinationWayPoint = m_destinationWayPoint->nextWayPoint();
        } else {
            // 表示进入基地
            m_game->getHpDamage(HPdamage);
            m_game->removedEnemy(this);
            return;
        }
    }
    // 还在前往航点的路上
    // 目标航点的坐标
    QPoint targetPoint = m_destinationWayPoint->pos();

    // 向量标准化
    qreal movementSpeed = m_walkingSpeed;
    QVector2D normalized(targetPoint - m_pos);
    normalized.normalize();
    m_pos = m_pos + 1.2*normalized.toPoint() * movementSpeed;

    //m_rotationSprite = qRadiansToDegrees(qAtan2(normalized.y(), normalized.x())) ;
}
void Enemy::draw(QPainter *painter) const{
    if (!m_active)
        return;

    painter->save();

    //m_pos仍然是中心位置
    QPoint healthBarPoint = m_pos + QPoint(0, -ms_fixedSize.height()/2 - 10);
    // 绘制血条
    //其实就是两个方框，红色方框代表总生命，固定大小不变
    //绿色方框代表当前生命，受m_currentHp / m_maxHp的变化影响
    painter->setPen(Qt::NoPen);
    painter->setBrush(Qt::red);
    QRect healthBarBackRect(healthBarPoint, QSize(Health_Bar_Width, 5));
    painter->drawRect(healthBarBackRect);

    painter->setBrush(Qt::green);
    QRect healthBarRect(healthBarPoint, QSize((double)m_currentHp / m_maxHp * Health_Bar_Width, 5));
    painter->drawRect(healthBarRect);

    // 绘制偏转坐标,由中心+偏移=左上
    static const QPoint offsetPoint(-ms_fixedSize.width() / 2, -ms_fixedSize.height() / 2);
    painter->translate(m_pos); //这里将坐标原点移到m_pos
    painter->rotate(m_rotationSprite);
    // 绘制敌人
    painter->drawPixmap(offsetPoint.x(),offsetPoint.y(),200,200, m_sprite);

    painter->restore();
}
void Enemy::getRemoved(){
    if (!m_attackedTowersList.empty())
        foreach (Tower *attacker, m_attackedTowersList)
            attacker->targetKilled();
    // 通知game,此敌人已经阵亡
    m_game->removedEnemy(this);
}
void Enemy::getDamage(Bullet *bullet){
    m_currentHp -= bullet->m_damage;

    switch(bullet->bulletKind)
    {
        case 0://NormalBullet
            m_game->audioPlayer()->playSound(NormalBulletSound);
            break;
        case 1://FireBullet
            m_game->audioPlayer()->playSound(FireBulletSound);
            fire = fireLevel;
            fireattack = bullet->fire_attack*fireattackLevel;
            break;
        case 2://IceBullet
            m_game->audioPlayer()->playSound(IceBulletSound);
            ice = iceLevel;
            m_slowSpeed = qMin(m_normalSpeed * bullet->slow_speed*antiSlowspeed, m_slowSpeed);
            m_walkingSpeed = m_slowSpeed;
            break;
        case 3://LaserBullet
            m_game->audioPlayer()->playSound(LaserBulletSound);
            break;
    }
    // 阵亡,需要移除
    canRemove();
}

void Enemy::canRemove()
{
    if (m_currentHp <= 0){
        switch(enemyKind){
        case(1):
            m_game->audioPlayer()->playSound(normalEnemyDestorySound);
            break;
        case(2):
            m_game->audioPlayer()->playSound(iceEnemyDestorySound);
            break;
        case(3):
            m_game->audioPlayer()->playSound(fireEnemyDestorySound);
            break;
        case(4):
            m_game->audioPlayer()->playSound(fastEnemyDestorySound);
            break;
        case(5):
            m_game->audioPlayer()->playSound(bossEnemyDestorySound);
            break;
        }

        m_game->awardGold(award);
        getRemoved();
    }
}
void Enemy::getFireDamage(int damage)
{
    m_currentHp -= damage;
    // 阵亡,需要移除
    canRemove();
}

void Enemy::getAttacked(Tower *attacker){
    m_attackedTowersList.push_back(attacker);
}
// 表明敌人已经逃离了攻击范围
void Enemy::gotLostSight(Tower *attacker){
    m_attackedTowersList.removeOne(attacker);
}
QPoint Enemy::pos() const{
    return m_pos;
}

normalEnemy::normalEnemy(WayPoint *startWayPoint, GameWindow *game, const QPixmap &sprite/* = QPixmap(":/images/enemy1.png")*/)
    :Enemy(startWayPoint, game,sprite/* = QPixmap(":/images/enemy1.png")*/)
{
    this->fireLevel=15;
    this->iceLevel=15;
    this->HPdamage=1;
    this->m_rotationSprite = 0.0;
    this->m_pos=startWayPoint->pos();
    this->m_destinationWayPoint=startWayPoint->nextWayPoint();
}

iceEnemy::iceEnemy(WayPoint *startWayPoint, GameWindow *game, const QPixmap &sprite/* = QPixmap(":/images/enemy2.png")*/)
    :Enemy(startWayPoint, game,sprite/* = QPixmap(":/images/enemy2.png")*/)
{
    this->enemyKind=2;
    this->award=250;
    this->m_maxHp = 75;
    this->m_currentHp = 75;
    this->antiSlowspeed=2.0;
    this->fireLevel=20;
    this->iceLevel=10;
    this->HPdamage=1;
    this->m_rotationSprite = 0.0;
    this->m_pos=startWayPoint->pos();
    this->m_destinationWayPoint=startWayPoint->nextWayPoint();
}

fireEnemy::fireEnemy(WayPoint *startWayPoint, GameWindow *game, const QPixmap &sprite/* = QPixmap(":/images/enemy3.png")*/)
    :Enemy(startWayPoint, game,sprite/* = QPixmap(":/images/enemy3.png")*/)
{
    this->enemyKind=3;
    this->award=200;
    this->m_maxHp = 85;
    this->m_currentHp = 85;
    this->antiSlowspeed=1.2;
    this->fireattackLevel=0.5;
    this->fireLevel=10;
    this->iceLevel=20;
    this->HPdamage=2;
    this->m_rotationSprite = 0.0;
    this->m_pos=startWayPoint->pos();
    this->m_destinationWayPoint=startWayPoint->nextWayPoint();
}

fastEnemy::fastEnemy(WayPoint *startWayPoint, GameWindow *game, const QPixmap &sprite/* = QPixmap(":/images/enemy4.png")*/)
    :Enemy(startWayPoint, game,sprite/* = QPixmap(":/images/enemy4.png")*/)
{
    this->enemyKind=4;
    this->award=250;
    this->m_maxHp = 90;
    this->m_currentHp = 90;
    this->m_normalSpeed=2.0;
    this->m_walkingSpeed=2.0;
    this->antiSlowspeed=4.0;
    this->fireLevel=15;
    this->iceLevel=15;
    this->HPdamage=2;
    this->m_rotationSprite = 0.0;
    this->m_pos=startWayPoint->pos();
    this->m_destinationWayPoint=startWayPoint->nextWayPoint();
}

bossEnemy::bossEnemy(WayPoint *startWayPoint, GameWindow *game, const QPixmap &sprite/* = QPixmap(":/images/monster1.png")*/)
    :Enemy(startWayPoint, game,sprite/* = QPixmap(":/images/monster1.png")*/)
{
    this->enemyKind=5;
    this->award=300;
    this->m_maxHp = 100;
    this->m_currentHp = 100;
    this->m_normalSpeed=3.0;
    this->m_walkingSpeed=4.0;
    this->antiSlowspeed=1.5;
    this->fireattack=1.0;
    this->fireLevel=10;
    this->iceLevel=10;
    this->HPdamage=3;
    this->m_rotationSprite = 0.0;
    this->m_pos=startWayPoint->pos();
    this->m_destinationWayPoint=startWayPoint->nextWayPoint();
}
