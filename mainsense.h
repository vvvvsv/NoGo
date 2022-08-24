#ifndef MAINSENSE_H
#define MAINSENSE_H

#include <QMainWindow>
#include "helpsense.h"
#include "newgamesense0.h"
#include "achievementsense.h"
#include "loadgamesense.h"
#include "nogosense.h"

namespace Ui {
class MainSense;
}

class MainSense : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainSense(QWidget *parent = 0);
    ~MainSense();

    void paintEvent(QPaintEvent *event);

    HelpSense *helpSense=NULL;
    NewGameSense0 *newGameSense0=NULL;
    AchievementSense *achievementSense=NULL;
    LoadGameSense *loadGameSense=NULL;
    NogoSense *nogoSense=NULL;

private:
    Ui::MainSense *ui;
};

#endif // MAINSENSE_H
