#include "helpsense.h"
#include <QMenuBar>
#include <QPainter>
#include <QTimer>

HelpSense::HelpSense(QWidget *parent) :
    QMainWindow(parent)
{
    this->setFixedSize(1440,810);
    this->setWindowIcon(QPixmap(":/res/Icon.png"));
    this->setWindowTitle("帮助");

    QMenuBar *bar=menuBar();
    setMenuBar(bar);

    QMenu *startMenu=bar->addMenu("开始");
    QAction *quitAction =startMenu->addAction("退出");
    QAction *backToMenuAction =startMenu->addAction("返回主菜单");

    connect(quitAction,&QAction::triggered,[=](){
        this->close();
    });

    connect(backToMenuAction,&QAction::triggered,[=](){
        QTimer::singleShot(300,this,[=](){
            emit this->backToMenu();
        });
    });
}

void HelpSense::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/BackgroundHelp.png");
    painter.drawPixmap(0,0,pix);
}
