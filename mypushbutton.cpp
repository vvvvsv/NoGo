#include "mypushbutton.h"
#include <QPropertyAnimation>
//MyPushButton::MyPushButton(QWidget *parent) : QPushButton(parent)
//{
//}

MyPushButton::MyPushButton(QString img)
{
    this->imgPath=img;

    QPixmap pix;
    pix.load(img);

    this->setFixedSize(pix.width(),pix.height());
    this->setStyleSheet("QPushButton{border:0px;}");
    this->setIcon(pix);
    this->setIconSize(QSize(pix.width(),pix.height()));
}


void MyPushButton::zoomDn(int delta)
{
    QPropertyAnimation *animation=new QPropertyAnimation(this,"geometry");
    animation->setDuration(200);

    animation->setStartValue(QRect(this->x(),this->y(),
                                   this->width(),this->height()));
    animation->setEndValue(QRect(this->x(),this->y()+delta,
                                 this->width(),this->height()));

    animation->setEasingCurve(QEasingCurve::OutBounce);
    animation->start();
}

void MyPushButton::zoomUp(int delta)
{
    QPropertyAnimation *animation=new QPropertyAnimation(this,"geometry");
    animation->setDuration(200);

    animation->setStartValue(QRect(this->x(),this->y()+delta,
                                   this->width(),this->height()));
    animation->setEndValue(QRect(this->x(),this->y(),
                                 this->width(),this->height()));

    animation->setEasingCurve(QEasingCurve::OutBounce);
    animation->start();
}
