#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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

#include "bullet.h"
#include "audioplayer.h"
#include "towerposition.h"
#include "plistreader.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    AudioPlayer *		    m_audioPlayer;

protected:
    void paintEvent(QPaintEvent *);
    //void mousePressEvent(QMouseEvent *);//鼠标点击触发事件

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
