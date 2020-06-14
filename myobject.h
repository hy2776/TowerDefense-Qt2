#ifndef MYOBJECT_H
#define MYOBJECT_H

#include <QObject>
#include <QPoint>
#include <QPixmap>
#include <QPainter>
#include <QPropertyAnimation>


class MyObject : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QPoint currentPos READ getCurrentPos WRITE setCurrentPos)
public:
    MyObject(QPoint startPos,QPoint targetPos,QString fileName);
    void draw(QPainter * painter);
    void move();
    QPoint getCurrentPos();
    void setCurrentPos(QPoint pos);
private:
    QPoint startPos;
    QPoint targetPos;
    QPoint currentPos;
    QPixmap pixmap;
signals:

};

#endif // MYOBJECT_H
