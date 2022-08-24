#ifndef NEWGAMESENSE1_H
#define NEWGAMESENSE1_H

#include <QMainWindow>
#include "newgamesense2.h"

class NewGameSense1 : public QMainWindow
{
    Q_OBJECT
public:
    explicit NewGameSense1(QWidget *parent = nullptr);

    void paintEvent(QPaintEvent *event);

    NewGameSense2 * newGameSense2;

signals:
    void backToNewGameSense0();

public slots:
};

#endif // NEWGAMESENSE1_H
