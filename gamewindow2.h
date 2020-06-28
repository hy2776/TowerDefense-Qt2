#ifndef GAMEWINDOW2_H
#define GAMEWINDOW2_H

#include "gamewindow.h"
#include "chooselevelwindow.h"
#include "mainwindow.h"
#include "mybutton.h"
#include "waypoint.h"
#include "enemy.h"
#include "bullet.h"
#include "plistreader.h"
#include "audioplayer.h"
#include <QPainter>
#include <QTimer>
#include <QPushButton>
#include <QPixmap>
#include <QMouseEvent>
#include <QMessageBox>
#include <QtGlobal>
#include <QMediaPlayer>
#include "gamewindow.h"
class GameWindow;

class GameWindow2 : public GameWindow
{
    Q_OBJECT
public:
    explicit GameWindow2(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *);
signals:
    void chooseBack();

};

#endif // GAMEWINDOW2_H
