#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QWidget>
#include <QMovie>
#include <QTimer>
#include <QLabel>
#include <QMouseEvent>
#include <QPushButton>
#include <QKeyEvent>
#include <waypoint.h>
#include <enemy.h>
#include <tower.h>
#include <QPaintEvent>
#include <QPainter>
#include <QList>
#include <QtGlobal>
#include <QMessageBox>
#include <QXmlStreamReader>
#include <QtDebug>
#include <QMainWindow>

#include "tower.h"
#include "towerposition.h"
#include "audioplayer.h"

class WayPoint;
class Enemy;
class Bullet;
class AudioPlayer;






class GameWindow : public QMainWindow
{
    Q_OBJECT
public:

    explicit GameWindow(QWidget *parent = nullptr);
    ~GameWindow();
    QPushButton* exit = new QPushButton(this);

    void getHpDamage(int damage = 1);
    void removedEnemy(Enemy *enemy);
    void removedBullet(Bullet *bullet);
    void addBullet(Bullet *bullet);
    void awardGold(int gold);
    AudioPlayer* audioPlayer() const;
    QList<Enemy *> enemyList() const;


    void updateScene();
    int                     towertype;//不同性质的的塔
    int                     del;//是否拆除塔
    int                     up;//是否升级塔


protected:
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *);

private slots:
    void updateMap();
    void gameStart();



public:
    bool canUpgradeTower() const;
    void loadTowerPositions();
    void addWayPoints();
    bool loadWave();
    bool canBuyTower() const;
    void drawWave(QPainter *painter);
    void drawHP(QPainter *painter);
    void drawPlayerGold(QPainter *painter);
    void doGameOver();
    void preLoadWavesInfo();





    int						m_waves;
    int						m_playerHp;
    int						m_playrGold;
    bool					m_gameEnded;
    bool					m_gameWin;
    AudioPlayer *			m_audioPlayer;
    QList<QVariant>			m_wavesInfo;
    QList<TowerPosition>	m_towerPositionsList;
    QList<Tower *>			m_towersList;
    QList<WayPoint *>		m_wayPointsList;
    QList<Enemy *>			m_enemyList;
    QList<Bullet *>			m_bulletList;


signals:
    void chooseBack();



};

#endif // GAMEWINDOW_H
