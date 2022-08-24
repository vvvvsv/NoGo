#ifndef ACHIEVEMENTSENSE_H
#define ACHIEVEMENTSENSE_H

#include <QMainWindow>

namespace Ui {
class AchievementSense;
}

class AchievementSense : public QMainWindow
{
    Q_OBJECT

public:
    explicit AchievementSense(QWidget *parent = 0);
    ~AchievementSense();
    void paintEvent(QPaintEvent *event);

signals:
    void backToMenu();

private:
    Ui::AchievementSense *ui;
};

#endif // ACHIEVEMENTSENSE_H
