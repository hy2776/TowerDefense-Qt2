#include "chooselevelwindow.h"
#include "mybutton.h"
#include "gamewindow.h"
#include "gamewindow2.h"
#include "audioplayer.h"
#include <QPainter>
#include <QTimer>
#include <QPushButton>
#include <QMediaPlayer>
ChooseLevelWindow::ChooseLevelWindow(QWidget *parent) : QMainWindow(parent)
{
    this->setFixedSize(1500,1200);
    this->setWindowIcon(QIcon(":/images/windowicon3.png"));

    QUrl backgroundMusicUrl = QUrl::fromLocalFile(s_curDir + "/levelmusic.mp3");
    m_audioPlayer = new AudioPlayer(backgroundMusicUrl,this);
    m_audioPlayer->startBGM();


    MyButton * back_bin = new MyButton(":/images/back-button.png");
    back_bin->setParent(this);
    back_bin->setIconSize(QSize(350,175));
    back_bin->move(50,1000);

    connect(back_bin,&MyButton::clicked,this,[=](){
        back_bin->zoomup();
        back_bin->zoomdown();
        m_audioPlayer->stopBGM();
        QTimer::singleShot(200,this,[=](){
         emit chooseBack();
        });

    });

    //设置关卡按钮
    MyButton * levelbtn1 = new MyButton(":/images/levelbtn1.png");
    levelbtn1->setParent(this);
    levelbtn1->setIconSize(QSize(200,200));
    levelbtn1->move(400,300);

    MyButton * levelbtn2 = new MyButton(":/images/levelbtn2.png");
    levelbtn2->setParent(this);
    levelbtn2->setIconSize(QSize(200,200));
    levelbtn2->move(700,300);

    MyButton * levelbtn3 = new MyButton(":/images/suobtn4.png");
    levelbtn3->setParent(this);
    levelbtn3->setIconSize(QSize(200,200));
    levelbtn3->move(1000,300);

    MyButton * levelbtn4 = new MyButton(":/images/suobtn4.png");
    levelbtn4->setParent(this);
    levelbtn4->setIconSize(QSize(200,200));
    levelbtn4->move(200,600);

    MyButton * levelbtn5 = new MyButton(":/images/suobtn4.png");
    levelbtn5->setParent(this);
    levelbtn5->setIconSize(QSize(200,200));
    levelbtn5->move(500,600);

    MyButton * levelbtn6 = new MyButton(":/images/suobtn4.png");
    levelbtn6->setParent(this);
    levelbtn6->setIconSize(QSize(200,200));
    levelbtn6->move(800,600);

    //点击关卡，显示对应主题游戏界面

    connect(levelbtn1,&MyButton::clicked,[=](){
        levelbtn1->zoomdown();
        levelbtn1->zoomup();
        GameWindow * scene1 = new GameWindow;
        QTimer::singleShot(300,this,[=](){
            m_audioPlayer->stopBGM();
            this->hide();
            scene1->show();

            //点击返回按钮，返回选择关卡界面
            connect(scene1,&GameWindow::chooseBack,this,[=](){
                scene1->hide();
                this->show();
                m_audioPlayer->startBGM();
            });
        });
    });


    connect(levelbtn2,&MyButton::clicked,[=](){
        levelbtn2->zoomdown();
        levelbtn2->zoomup();
        GameWindow2 * scene2= new GameWindow2;
        QTimer::singleShot(300,this,[=](){
            m_audioPlayer->stopBGM();
            this->hide();
            scene2->show();
            connect(scene2,&GameWindow2::chooseBack,this,[=](){
                scene2->hide();
                this->show();
                m_audioPlayer->startBGM();
            });

        });
    });







    QTimer * timer = new QTimer(this);
    connect(timer,&QTimer::timeout,this,&ChooseLevelWindow::updateScene);
    timer->start(10);

}

void ChooseLevelWindow::paintEvent(QPaintEvent *){
    QPainter painter(this);
    QPixmap pixmap(":/images/Bg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pixmap);




}

AudioPlayer *ChooseLevelWindow::audioPlayer() const
{
    return m_audioPlayer;
}


void ChooseLevelWindow::updateScene()
{
   update();
}
