#ifndef NEWGAMESENSE0_H
#define NEWGAMESENSE0_H

#include <QMainWindow>
#include "newgamesense1.h"
#include "nogosense.h"

class NewGameSense0 : public QMainWindow
{
    Q_OBJECT
public:
    explicit NewGameSense0(QWidget *parent = nullptr);

    void paintEvent(QPaintEvent *event);

    NewGameSense1 * newGameSense1;
    NogoSense* nogoSense;

signals:
    void backToMenu();

public slots:
};

#endif // NEWGAMESENSE0_H
