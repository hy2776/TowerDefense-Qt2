#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPaintEvent>
#include <QPainter>
#include <QPixmap>
#include <QPushButton>
#include <QDebug>
#include <QTimer>
#include <QMediaPlayer>
#include "chooselevelwindow.h"
#include "mybutton.h"
#include "audioplayer.h"
#include "gamewindow.h"

class GameWindow;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    this->setFixedSize(1500,1200);
    this->setWindowIcon(QIcon(":/images/windowicon3.png"));
    ui->setupUi(this);

    QUrl backgroundMusicUrl = QUrl::fromLocalFile(s_curDir + "/mainmusic.mp3");
    m_audioPlayer = new AudioPlayer(backgroundMusicUrl,this);
    m_audioPlayer->startBGM();

    MyButton * bin = new MyButton(":/images/Button.png");
    bin->setParent(this);
    bin->move(600,800);



    connect(bin,&QPushButton::clicked,this,[=](){
        bin->zoomdown();
        bin->zoomup();
        ChooseLevelWindow * scene = new ChooseLevelWindow;
        QTimer::singleShot(500,this,[=](){
            m_audioPlayer->stopBGM();
            this->hide();
            scene->show();
            connect(scene,&ChooseLevelWindow::chooseBack,this,[=](){
                m_audioPlayer->startBGM();
                scene->hide();
                this->show();
            });
        });
    });



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

