#ifndef LOADGAMESENSE_H
#define LOADGAMESENSE_H

#include <QMainWindow>

namespace Ui {
class LoadGameSense;
}

class LoadGameSense : public QMainWindow
{
    Q_OBJECT

public:
    explicit LoadGameSense(QWidget *parent = 0);
    ~LoadGameSense();
    void paintEvent(QPaintEvent *event);

signals:
    void backToMenu();

private:
    Ui::LoadGameSense *ui;
};

#endif // LOADGAMESENSE_H
