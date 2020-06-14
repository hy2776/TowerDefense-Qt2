#ifndef GAMEWINDOW2_H
#define GAMEWINDOW2_H

#include <QMainWindow>
#include <QWidget>

class GameWindow2 : public QMainWindow
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
