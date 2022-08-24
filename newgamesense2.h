#ifndef NEWGAMESENSE2_H
#define NEWGAMESENSE2_H

#include <QMainWindow>
#include "nogosense.h"

class NewGameSense2 : public QMainWindow
{
    Q_OBJECT
public:
    explicit NewGameSense2(int type,QWidget *parent = nullptr);

    void paintEvent(QPaintEvent *event);
    int gameType;
    NogoSense *nogoSense=nullptr;

signals:
    void backToNewGameSense1();

public slots:
};

#endif // NEWGAMESENSE2_H
