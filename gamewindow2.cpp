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

GameWindow2::GameWindow2(QWidget *parent) : QMainWindow(parent)
{
    this->setWindowIcon(QIcon(":/images/windowicon3.png"));

    this->setFixedSize(1500,1200);
    MyButton * back_bin = new MyButton(":/images/back-button.png");
    back_bin->setParent(this);
    back_bin->setIconSize(QSize(350,175));
    back_bin->move(50,1000);
    connect(back_bin,&MyButton::clicked,this,[=](){
        emit chooseBack();
    });

}
void GameWindow2::paintEvent(QPaintEvent *){
    QPainter painter(this);
    QPixmap pixmap(":/images/02A.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pixmap);
}
