#include "gamewindow.h"
#include "chooselevelwindow.h"
#include "mainwindow.h"
#include "mybutton.h"
#include "waypoint.h"
#include "enemy.h"
#include "bullet.h"
#include "plistreader.h"
#include "audioplayer.h"
#include "towericon.h"

#include <QPainter>
#include <QTimer>
#include <QPushButton>
#include <QPixmap>
#include <QMouseEvent>
#include <QMessageBox>
#include <QtGlobal>
#include <QMediaPlayer>


static const int TowerCost1 = 100;
static const int TowerCost2 = 220;
static const int TowerCost3 = 160;
static const int TowerCost4 = 220;//设定每安置一个炮塔花费的金币
static const int UpdateTowerCost = 200;//设定升级炮塔花费200金币
static const int RemoveTowerGet = 100;//设定拆除炮塔得到100金币


GameWindow::GameWindow(QWidget *parent) :
    QMainWindow(parent)

    , m_waves(0)
    , m_playerHp(15)
    , m_playrGold(10000)
    , m_gameEnded(false)
    , m_gameWin(false)
{

    this->setWindowIcon(QIcon(":/images/windowicon3.png"));

    this->setFixedSize(1500,1200);


    MyButton * back_bin = new MyButton(":/images/back-button.png");
    back_bin->setParent(this);
    back_bin->setIconSize(QSize(350,175));
    back_bin->move(1200,30);
    connect(back_bin,&MyButton::clicked,this,[=](){
        back_bin->zoomdown();
        back_bin->zoomup();
        QTimer::singleShot(200,this,[=](){
         emit chooseBack();
        });
    });

    MyButton * tower1 = new MyButton(":/images/tower1icon.png");
    tower1->setParent(this);
    tower1->setIconSize(QSize(150,150));
    tower1->move(30,280);
    connect(tower1,&MyButton::clicked,this,[=](){
        tower1->zoomdown();
        tower1->zoomup();
        towertype=1;
        up=0;
        del=0;
    });

    MyButton * tower2 = new MyButton(":/images/tower2icon.png");
    tower2->setParent(this);
    tower2->setIconSize(QSize(150,150));
    tower2->move(30,450);
    connect(tower2,&MyButton::clicked,this,[=](){
        tower2->zoomdown();
        tower2->zoomup();
        towertype=2;
        up=0;
        del=0;
    });

    MyButton * tower3 = new MyButton(":/images/tower3icon.png");
    tower3->setParent(this);
    tower3->setIconSize(QSize(150,150));
    tower3->move(30,620);
    connect(tower3,&MyButton::clicked,this,[=](){
        tower3->zoomdown();
        tower3->zoomup();
        towertype=3;
        up=0;
        del=0;
    });

    MyButton * tower4 = new MyButton(":/images/tower4icon.png");
    tower4->setParent(this);
    tower4->setIconSize(QSize(150,150));
    tower4->move(30,790);
    connect(tower4,&MyButton::clicked,this,[=](){
        tower4->zoomdown();
        tower4->zoomup();
        towertype=4;
        up=0;
        del=0;
    });

    MyButton * play = new MyButton(":/images/Button.png");
    play->setParent(this);
    play->move(1100,1010);

    MyButton * upgrade_bin = new MyButton(":/images/upgrade.png");
    upgrade_bin->setParent(this);
    upgrade_bin->setIconSize(QSize(140,140));
    upgrade_bin->move(30,960);
    connect(upgrade_bin,&MyButton::clicked,this,[=](){
        upgrade_bin->zoomdown();
        upgrade_bin->zoomup();
        towertype=0;
        up=1;
        del=0;
    });

    MyButton * deletetower_bin = new MyButton(":/images/deletetower.png");
    deletetower_bin->setParent(this);
    deletetower_bin->setIconSize(QSize(150,150));
    deletetower_bin->move(200,960);
    connect(deletetower_bin,&MyButton::clicked,this,[=](){
        deletetower_bin->zoomdown();
        deletetower_bin->zoomup();
        towertype=0;
        up=0;
        del=1;
    });

    preLoadWavesInfo();
    loadTowerPositions();
    addWayPoints();



    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateMap()));
    timer->start(10);
    //this->uiSetup();
    // 设置500ms后游戏启动
    QTimer::singleShot(500, this, SLOT(gameStart()));


}

//void GameWindow::uiSetup()
//{
//    TowerIcon *card0 = new NormalTowerIcon(this);
//    card0->setGeometry(180, 10 , 100, 60);
//    Icons.append(card0);
//    card0->show();
//}
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

    QPixmap luobo1(":/images/luobo1.png");
    QPixmap luobo2(":/images/luobo2.png");
    QPixmap luobo3(":/images/luobo3.png");
    QPixmap luobo4(":/images/luobo4.png");
    QPixmap luobo5(":/images/luobo5.png");
    if(m_playerHp>=13){
        painter.drawPixmap(480,900,150,200,luobo1);
    }
    else if(m_playerHp<13&&m_playerHp>=9){
       painter.drawPixmap(480,900,150,200,luobo2);
    }
    else if(m_playerHp<9&&m_playerHp>=6){
       painter.drawPixmap(480,900,150,200,luobo3);
    }
    else if(m_playerHp<6&&m_playerHp>=3){
       painter.drawPixmap(480,900,150,200,luobo4);
    }
    else{
        painter.drawPixmap(480,900,150,200,luobo5);
    }


    for(int i=0;i<=19;++i)
    {
        painter.drawPixmap(m_towerPositionsList[i].Pos11x(),m_towerPositionsList[i].Pos11y(),110,110,QPixmap(":/images/base2.png"));
    }

    foreach (const Tower *tower, m_towersList)
        tower->draw(&painter);

    foreach (const Enemy *enemy, m_enemyList)
        enemy->draw(&painter);

    foreach (const Bullet *bullet, m_bulletList)
        bullet->draw(&painter);

    //drawHP(&painter);
    drawPlayerGold(&painter);
    drawWave(&painter);
    drawHP(&painter);

}

void GameWindow::addWayPoints()
{
    WayPoint *wayPoint1 = new WayPoint(QPoint(600-80, 900-80));
    m_wayPointsList.push_back(wayPoint1);

    WayPoint *wayPoint2 = new WayPoint(QPoint(600-80, 350-80));
    m_wayPointsList.push_back(wayPoint2);
    wayPoint2->setNextWayPoint(wayPoint1);

    WayPoint *wayPoint3 = new WayPoint(QPoint(700-80, 350-80));
    m_wayPointsList.push_back(wayPoint3);
    wayPoint3->setNextWayPoint(wayPoint2);

    WayPoint *wayPoint4 = new WayPoint(QPoint(700-80, 250-80));
    m_wayPointsList.push_back(wayPoint4);
    wayPoint4->setNextWayPoint(wayPoint3);

    WayPoint *wayPoint5 = new WayPoint(QPoint(1050-80, 250-80));
    m_wayPointsList.push_back(wayPoint5);
    wayPoint5->setNextWayPoint(wayPoint4);

    WayPoint *wayPoint6 = new WayPoint(QPoint(1050-80, 750-80));
    m_wayPointsList.push_back(wayPoint6);
    wayPoint6->setNextWayPoint(wayPoint5);

    WayPoint *wayPoint7 = new WayPoint(QPoint(950-80, 750-80));
    m_wayPointsList.push_back(wayPoint7);
    wayPoint7->setNextWayPoint(wayPoint6);

    WayPoint *wayPoint8 = new WayPoint(QPoint(950-80, 950-80));
    m_wayPointsList.push_back(wayPoint8);
    wayPoint8->setNextWayPoint(wayPoint7);

    WayPoint *wayPoint9 = new WayPoint(QPoint(1400-80, 950-80));
    m_wayPointsList.push_back(wayPoint9);
    wayPoint9->setNextWayPoint(wayPoint8);

    WayPoint *wayPoint10 = new WayPoint(QPoint(1400-80, 500-80));
    m_wayPointsList.push_back(wayPoint10);
    wayPoint10->setNextWayPoint(wayPoint9);
}



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
        QPoint(538, 215),
        QPoint(768, 895),
        QPoint(883, 1050),
        QPoint(1108, 330),//待调整位置
        QPoint(993, 790)
    };
    int len	= sizeof(pos) / sizeof(pos[0]);

    for (int i = 0; i < len; ++i)
        m_towerPositionsList.push_back(pos[i]);
}

bool GameWindow::canBuyTower() const
{
    if (m_playrGold >= TowerCost1)
        return true;
    return false;
}



void GameWindow::mousePressEvent(QMouseEvent *event)
{
    QPoint pressPos = event->pos();
    auto it = m_towerPositionsList.begin();
    while (it != m_towerPositionsList.end())
    {
        if (canBuyTower() && it->containPoint(pressPos) && !it->hasTower() && towertype==1 && up==0 && del==0)
        {
            m_audioPlayer->playSound(TowerPlaceSound);
            m_playrGold -= TowerCost1;
            it->setHasTower();

            it->m_tower = new Tower1(it->centerPos(), this);
            m_towersList.push_back(it->m_tower);
            update();
            break;
        }
        if (canBuyTower() && it->containPoint(pressPos) && !it->hasTower() && towertype==2 && up==0 && del==0)
        {
            m_audioPlayer->playSound(TowerPlaceSound);
            m_playrGold -= TowerCost2;
            it->setHasTower();

            it->m_tower = new Tower2(it->centerPos(), this);//构建的同时直接在mainwindow上作画
            m_towersList.push_back(it->m_tower);//把新构建的塔放入towerlist中储存，方便管理
            update();
            break;
        }
        if (canBuyTower() && it->containPoint(pressPos) && !it->hasTower() && towertype==3 && up==0 && del==0)
        {
            m_audioPlayer->playSound(TowerPlaceSound);
            m_playrGold -= TowerCost3;
            it->setHasTower();

            it->m_tower = new Tower3(it->centerPos(), this);//构建的同时直接在mainwindow上作画
            m_towersList.push_back(it->m_tower);//把新构建的塔放入towerlist中储存，方便管理
            update();
            break;
        }
        if (canBuyTower() && it->containPoint(pressPos) && !it->hasTower() && towertype==4 && up==0 && del==0)
        {
            m_audioPlayer->playSound(TowerPlaceSound);
            m_playrGold -= TowerCost4;
            it->setHasTower();

            it->m_tower = new Tower4(it->centerPos(), this);//构建的同时直接在mainwindow上作画
            m_towersList.push_back(it->m_tower);//把新构建的塔放入towerlist中储存，方便管理
            update();
            break;
        }
        //删除的鼠标事件，难点：如何删除塔
        if( it->containPoint(pressPos) && it->hasTower() && towertype==0 && up==0 && del==1)
        {
            m_towersList.removeOne(it->m_tower);
            it->setHasnotTower();
            m_playrGold+=RemoveTowerGet;
            m_audioPlayer->playSound(TowerPlaceSound);
            update();
            break;
        }
        //升级的鼠标事件
        if( it->containPoint(pressPos) && it->hasTower() && towertype==0 && up==1 && del==0)
        {
             if(it->m_tower->gettowertype()==1 && it->m_tower->getlevel()==1 && m_playrGold>=UpdateTowerCost)
             {
                 m_towersList.removeOne(it->m_tower);
                 it->m_tower = new Tower1_2(it->centerPos(), this);
                 m_towersList.push_back(it->m_tower);
                 m_playrGold -= UpdateTowerCost;

                 update();
             }
             if(it->m_tower->gettowertype()==2 && it->m_tower->getlevel()==1 && m_playrGold>=UpdateTowerCost)
             {
                 m_towersList.removeOne(it->m_tower);
                 it->m_tower = new Tower2_2(it->centerPos(), this);
                 m_towersList.push_back(it->m_tower);
                 m_playrGold -= UpdateTowerCost;
                 update();

             }
             if(it->m_tower->gettowertype()==3 && it->m_tower->getlevel()==1 && m_playrGold>=UpdateTowerCost)
             {
                 m_towersList.removeOne(it->m_tower);
                 it->m_tower = new Tower3_2(it->centerPos(), this);
                 m_towersList.push_back(it->m_tower);
                 m_playrGold -= UpdateTowerCost;
                 update();

             }
             if(it->m_tower->gettowertype()==4 && it->m_tower->getlevel()==1 && m_playrGold>=UpdateTowerCost)
             {
                 m_towersList.removeOne(it->m_tower);
                 it->m_tower = new Tower4_2(it->centerPos(), this);
                 m_towersList.push_back(it->m_tower);
                 m_playrGold -= UpdateTowerCost;
                 update();

             }
            m_audioPlayer->playSound(TowerPlaceSound);
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

void GameWindow::drawWave(QPainter *painter)
{
    painter->setPen(QPen(Qt::yellow));
    QFont font1("宋体",28,QFont::Bold, true) ;
    painter->setFont(font1);
    painter->drawText(QRect(8, 100, 300, 500), QString("WAVE:%1").arg(m_waves + 1));
}

void GameWindow::drawHP(QPainter *painter)
{
    painter->setPen(QPen(Qt::red));
    QFont font1("宋体",28,QFont::Bold, true) ;
    painter->setFont(font1);
    painter->drawText(QRect(8, 200, 500, 500), QString("HP:%1").arg(m_playerHp));
}

void GameWindow::doGameOver()
{
    if (!m_gameEnded)
    {
        m_gameEnded = true;
        // 此处应该切换场景到结束场景
        // 暂时以打印替代,见paintEvent处理

        //m_audioPlayer->stopBGM();
        m_audioPlayer->playLoseSound();
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
    m_audioPlayer->playSound(luoboCrySound);
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
//            m_audioPlayer->stopBGM();
            //m_audioPlayer->playWinSound();
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

        Enemy *enemy;
        int j=i%5;
        switch(j){
        case 0:
            enemy = new normalEnemy(startWayPoint, this);
            break;
        case 1:
            enemy=new iceEnemy(startWayPoint, this);
            break;
        case 2:
            enemy=new fireEnemy(startWayPoint, this);
            break;
        case 3:
            enemy=new fastEnemy(startWayPoint, this);
            break;
        case 4:
            enemy=new bossEnemy(startWayPoint, this);
            break;
        }
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

bool GameWindow::canUpgradeTower() const
{
    if(m_playrGold >= UpdateTowerCost)
        return true;
    return false;
}

