#include "gamewindow.h"
#include "chooselevelwindow.h"
#include "mybutton.h"
#include "waypoint.h"
#include "enemy.h"
#include "bullet.h"
#include "plistreader.h"
#include <QPainter>
#include <QTimer>
#include <QPushButton>
#include <QPixmap>
#include <QMouseEvent>
#include <QMessageBox>
#include <QtGlobal>
static const int TowerCost = 200;


GameWindow::GameWindow(QWidget *parent) :
    QMainWindow(parent)
    , m_waves(0)
    , m_playerHp(1)
    , m_playrGold(10000)
    , m_gameEnded(false)
    , m_gameWin(false)
{
    preLoadWavesInfo();
    loadTowerPositions();
    addWayPoints();
    this->setWindowIcon(QIcon(":/images/windowicon3.png"));

    this->setFixedSize(1500,1200);


    MyButton * back_bin = new MyButton(":/images/back-button.png");
    back_bin->setParent(this);
    back_bin->setIconSize(QSize(350,175));
    back_bin->move(-100,900);
    connect(back_bin,&MyButton::clicked,this,[=](){
        emit chooseBack();
    });

    MyButton * play = new MyButton(":/images/Button.png");
    play->setParent(this);
    play->move(1100,1010);


    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateMap()));
    timer->start(10);
    // 设置300ms后游戏启动
    QTimer::singleShot(300, this, SLOT(gameStart()));


}
void GameWindow::paintEvent(QPaintEvent *){
    QPainter painter(this);
    QPixmap pixmap(":/images/01A.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pixmap);

    painter.setRenderHint(QPainter::Antialiasing, true);
    if (m_gameEnded || m_gameWin)
    {

        QString text = m_gameEnded ? "Defeat!!!" : "Victory!!!";
        QPainter painter(this);
        painter.setPen(QPen(Qt::red));
        QFont font1("宋体",64,QFont::Bold, true) ;
        painter.setFont(font1);
        painter.drawText(rect(), Qt::AlignCenter, text);
        return;
    }

    for(int i=0;i<=15;++i)
    {
        painter.drawPixmap(m_towerPositionsList[i].Pos11x(),m_towerPositionsList[i].Pos11y(),110,110,QPixmap(":/images/base2.png"));
    }

    foreach (const Tower *tower, m_towersList)
        tower->draw(&painter);

    //foreach (const WayPoint *wayPoint, m_wayPointsList)
    //    wayPoint->draw(&painter);

    foreach (const Enemy *enemy, m_enemyList)
        enemy->draw(&painter);

    foreach (const Bullet *bullet, m_bulletList)
        bullet->draw(&painter);

    //drawHP(&painter);
    drawPlayerGold(&painter);

}

void GameWindow::addWayPoints()
{
    WayPoint *wayPoint1 = new WayPoint(QPoint(1000, 285));
    m_wayPointsList.push_back(wayPoint1);

    WayPoint *wayPoint2 = new WayPoint(QPoint(35, 285));
    m_wayPointsList.push_back(wayPoint2);
    wayPoint2->setNextWayPoint(wayPoint1);

    WayPoint *wayPoint3 = new WayPoint(QPoint(900, 550));
    m_wayPointsList.push_back(wayPoint3);
    wayPoint3->setNextWayPoint(wayPoint2);

    WayPoint *wayPoint4 = new WayPoint(QPoint(900, 1000));
    m_wayPointsList.push_back(wayPoint4);
    wayPoint4->setNextWayPoint(wayPoint3);

    WayPoint *wayPoint5 = new WayPoint(QPoint(1400, 1000));
    m_wayPointsList.push_back(wayPoint5);
    wayPoint5->setNextWayPoint(wayPoint4);

    WayPoint *wayPoint6 = new WayPoint(QPoint(1400, 500));
    m_wayPointsList.push_back(wayPoint6);
    wayPoint6->setNextWayPoint(wayPoint5);
}

//void GameWindow::addMyobject(){
//    MyObject * object = new MyObject(QPoint(400,100),QPoint(1000,100),":/images/enemy1.png");

//    object_list.push_back(object);

//    object->move();
//    update();
//}

void GameWindow::updateScene()
{
   update();
}

void GameWindow::loadTowerPositions()
{
    QPoint pos[] =
    {
        QPoint(423, 445),
        QPoint(423, 560),
        QPoint(423, 675),
        QPoint(653, 560),
        QPoint(653, 675),
        QPoint(883, 550),
        QPoint(883, 435),
        QPoint(883, 320),
        QPoint(883, 70),
        QPoint(998, 70),
        QPoint(768, 790),
        QPoint(1223, 560),
        QPoint(1223, 675),
        QPoint(1223, 790),
        QPoint(1108, 790),
//        QPoint(538, 215),
//        QPoint(768, 895),
//        QPoint(883, 1050),
//        QPoint(1108, 330)
        QPoint(993, 790)
    };
    int len	= sizeof(pos) / sizeof(pos[0]);

    for (int i = 0; i < len; ++i)
        m_towerPositionsList.push_back(pos[i]);
}

bool GameWindow::canBuyTower() const
{
    if (m_playrGold >= TowerCost)
        return true;
    return false;
}

void GameWindow::drawWave(QPainter *painter)
{
    painter->setPen(QPen(Qt::blue));
    painter->drawText(QRect(400, 5, 100, 25), QString("WAVE : %1").arg(m_waves + 1));
}

void GameWindow::mousePressEvent(QMouseEvent *event)
{
    QPoint pressPos = event->pos();
    auto it = m_towerPositionsList.begin();
    while (it != m_towerPositionsList.end())
    {
        if (canBuyTower() && it->containPoint(pressPos) && !it->hasTower())
        {

            m_playrGold -= TowerCost;
            it->setHasTower();

            Tower *tower = new Tower(it->centerPos(), this);
            m_towersList.push_back(tower);
            update();
            break;
        }

        ++it;
    }
}

void GameWindow::drawPlayerGold(QPainter *painter)
{
    painter->setPen(QPen(Qt::yellow));
    QFont font1("宋体",28,QFont::Bold, true) ;
    painter->setFont(font1);
    painter->drawText(QRect(8, 3, 800, 800), QString(" %1").arg(m_playrGold));
    QPixmap pix(":/images/money2.png");
    painter->drawPixmap(0,0,55,80,pix);
}

void GameWindow::doGameOver()
{
    if (!m_gameEnded)
    {
        m_gameEnded = true;
        // 此处应该切换场景到结束场景
        // 暂时以打印替代,见paintEvent处理
    }
}

void GameWindow::awardGold(int gold)
{
    m_playrGold += gold;
    update();
}

AudioPlayer *GameWindow::audioPlayer() const
{
    return m_audioPlayer;
}

void GameWindow::getHpDamage(int damage/* = 1*/)
{

    m_playerHp -= damage;
    if (m_playerHp <= 0)
        doGameOver();
}

void GameWindow::removedEnemy(Enemy *enemy)
{
    Q_ASSERT(enemy);

    m_enemyList.removeOne(enemy);
    delete enemy;

    if (m_enemyList.empty())
    {
        ++m_waves;
        if (!loadWave())
        {
            m_gameWin = true;
            // 游戏胜利转到游戏胜利场景
            // 这里暂时以打印处理
        }
    }
}

void GameWindow::removedBullet(Bullet *bullet)
{
    Q_ASSERT(bullet);

    m_bulletList.removeOne(bullet);
    delete bullet;
}

void GameWindow::addBullet(Bullet *bullet)
{
    Q_ASSERT(bullet);
    m_bulletList.push_back(bullet);
}

void GameWindow::updateMap()
{
    foreach (Enemy *enemy, m_enemyList)
        enemy->move();
    foreach (Tower *tower, m_towersList)
        tower->checkEnemyInRange();
    update();
}

void GameWindow::preLoadWavesInfo()
{
    QFile file(":/config/Waves.plist");
    if (!file.open(QFile::ReadOnly | QFile::Text))
    {
        QMessageBox::warning(this, "TowerDefense", "Cannot Open TowersPosition.plist");
        return;
    }

    PListReader reader;
    reader.read(&file);
    // 获取波数信息
    m_wavesInfo = reader.data();

    file.close();
}

bool GameWindow::loadWave()
{
    if (m_waves >= m_wavesInfo.size())
        return false;

    WayPoint *startWayPoint = m_wayPointsList.back();
    QList<QVariant> curWavesInfo = m_wavesInfo[m_waves].toList();

    for (int i = 0; i < curWavesInfo.size(); ++i)
    {
        QMap<QString, QVariant> dict = curWavesInfo[i].toMap();
        int spawnTime = dict.value("spawnTime").toInt();
        Enemy *enemy = new Enemy(startWayPoint, this);
        m_enemyList.push_back(enemy);
        QTimer::singleShot(spawnTime, enemy, SLOT(doActivate()));
    }

    return true;
}


QList<Enemy *> GameWindow::enemyList() const
{
    return m_enemyList;
}

void GameWindow::gameStart()
{
    loadWave();
}



