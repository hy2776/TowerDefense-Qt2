#include "gamewindow2.h"
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
//第二关暂时没有完全调试好
GameWindow2::GameWindow2(QWidget *parent) : GameWindow(parent)
{
    this->setWindowIcon(QIcon(":/images/windowicon3.png"));

    MyButton * back_bin = new MyButton(":/images/back-button.png");
    back_bin->setParent(this);
    back_bin->setIconSize(QSize(350,175));
    back_bin->move(1200,30);
    connect(back_bin,&MyButton::clicked,this,[=](){
        back_bin->zoomdown();
        back_bin->zoomup();
        m_audioPlayer->stopBGM();
        QTimer::singleShot(200,this,[=](){
         emit chooseBack();
        });
    });

    this->setFixedSize(1500,1200);
    preLoadWavesInfo();
    loadTowerPositions();
    addWayPoints();



    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateMap()));
    timer->start(10);

    // 设置10000ms后游戏启动
    QTimer::singleShot(10000, this, SLOT(gameStart()));
}
void GameWindow2::paintEvent(QPaintEvent *){
    QPainter painter(this);
    QPixmap pixmap(":/images/02A.png");
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


    drawPlayerGold(&painter);
    drawWave(&painter);
    drawHP(&painter);
}


