#ifndef MYBUTTON_H
#define MYBUTTON_H

#include <QWidget>
#include <QPushButton>

class MyButton : public QPushButton
{
    Q_OBJECT
public:
    MyButton(QString pix);
    void zoomup();
    void zoomdown();

signals:

};

#endif // MYBUTTON_H
