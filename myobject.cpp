#include "myobject.h"

MyObject::MyObject(QPoint startPos,QPoint targetPos,QString fileName):QObject(0),pixmap(fileName)
{
    this->currentPos = startPos;
    this->startPos = startPos;
    this->targetPos = targetPos;
}

void MyObject::draw(QPainter * painter)
{



    painter->drawPixmap(currentPos,pixmap);


}

void MyObject::move()
{
    QPropertyAnimation * animation = new QPropertyAnimation(this,"currentPos");
    animation->setDuration(2000);
    animation->setStartValue(startPos);
    animation->setEndValue(targetPos);
    animation->start();
}

QPoint MyObject::getCurrentPos(){
    return this->currentPos;
}

void MyObject::setCurrentPos(QPoint pos){
    this->currentPos = pos;
}
