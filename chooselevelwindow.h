#ifndef MYWINDOW_H
#define MYWINDOW_H

#include <QMainWindow>
#include "tower.h"
#include <QList>

#include "gamewindow.h"

class ChooseLevelWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit ChooseLevelWindow(QWidget *parent = nullptr);

    void paintEvent(QPaintEvent *);
    GameWindow * game = NULL;
    AudioPlayer* audioPlayer() const;


    void updateScene();
private:
    QList<Tower*> tower_list;
    AudioPlayer *			m_audioPlayer;


signals:
    void chooseBack();

};

#endif // MYWINDOW_H
