#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QMainWindow>
#include <QList>
#include "myobject.h"
#include <QPushButton>
#include <QPainter>
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


    void getHpDamage(int damage = 1);
    void removedEnemy(Enemy *enemy);
    void removedBullet(Bullet *bullet);
    void addBullet(Bullet *bullet);
    void awardGold(int gold);
    AudioPlayer* audioPlayer() const;
    QList<Enemy *> enemyList() const;

    void updateScene();
protected:
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *);

private slots:
    void updateMap();
    void gameStart();

private:
    void loadTowerPositions();
    void addWayPoints();
    bool loadWave();
    bool canBuyTower() const;
    void drawWave(QPainter *painter);
    void drawHP(QPainter *painter);
    void drawPlayerGold(QPainter *painter);
    void doGameOver();
    void preLoadWavesInfo();


private:
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
