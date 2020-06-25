#ifndef TCARD_H
#define TCARD_H

#include <QLabel>
#include <QMovie>
#include <QSound>
#include <QMouseEvent>

#include "gamewindow.h"

class GameWindow;

class TowerIcon: public QLabel
{
public:
    TowerIcon(QLabel* parent = 0);
    ~TowerIcon();
};

class NormalTowerIcon : public TowerIcon
{
public:
    NormalTowerIcon(QLabel* parent = 0);
    ~NormalTowerIcon();
private:
    QMovie* anim = new QMovie(":/images/tower1icon.png");
};


class FireTowerIcon : public TowerIcon
{
public:
    FireTowerIcon(QLabel* parent = 0);
    ~FireTowerIcon();
private:
    QMovie* anim = new QMovie(":/images/tower2icon.png");
};

class IceTowerIcon : public TowerIcon
{
public:
    IceTowerIcon(QLabel* parent = 0);
    ~IceTowerIcon();
private:
    QMovie* anim = new QMovie(":/images/tower3icon.png");
};

class LaserTowerIcon : public TowerIcon
{
public:
    LaserTowerIcon(QLabel* parent = 0);
    ~LaserTowerIcon();
private:
    QMovie* anim = new QMovie(":/images/tower4icon.png");
};
#endif // TCARD_H
