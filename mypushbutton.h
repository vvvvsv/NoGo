#ifndef MYPUSHBUTTON_H
#define MYPUSHBUTTON_H

#include <QPushButton>

class MyPushButton : public QPushButton
{
    Q_OBJECT
public:
//    explicit MyPushButton(QWidget *parent = nullptr);

    MyPushButton(QString img);
    QString imgPath;

    void zoomDn(int delta=10);
    void zoomUp(int delta=10);
signals:

public slots:
};

#endif // MYPUSHBUTTON_H
