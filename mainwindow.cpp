#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPaintEvent>
#include <QPainter>
#include <QPixmap>
#include <QPushButton>
#include <QDebug>
#include <QTimer>
#include "chooselevelwindow.h"
#include "mybutton.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    this->setFixedSize(1500,1200);
    this->setWindowIcon(QIcon(":/images/windowicon3.png"));
    ui->setupUi(this);
    MyButton * bin = new MyButton(":/images/Button.png");
    bin->setParent(this);
    bin->move(600,800);
    //connect(bin,&MyButton::clicked,this,&QMainWindow::close);
//    QPushButton * bin = new QPushButton(this);
//    bin->setFixedSize(100,50);
//    bin->move(40,40);
//    connect(bin,&QPushButton::clicked,this,&QMainWindow::close);

    ChooseLevelWindow * scene = new ChooseLevelWindow;
    connect(bin,&QPushButton::clicked,this,[=](){
        bin->zoomdown();
        bin->zoomup();
        QTimer::singleShot(500,this,[=](){
            this->hide();
            scene->show();
        });
    });

    connect(scene,&ChooseLevelWindow::chooseBack,this,[=](){
        scene->hide();
        this->show();
    });
    //mywindow back_bin clicked emit choose

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *){
    QPainter painter(this);
    QPixmap pixmap(":/images/Bg.png");
    QPixmap pixmap1(":/images/title1.png");
    //添加主界面背景
    painter.drawPixmap(0,0,this->width(),this->height(),pixmap);
    //添加游戏标题
    painter.drawPixmap(this->width()-pixmap1.width()+90,300,pixmap1.width()*0.8,pixmap1.height()*0.8,pixmap1);

}
