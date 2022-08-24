#include "newgamesense0.h"
#include <QMenuBar>
#include <QPainter>
#include <QTimer>
#include "mypushbutton.h"

NewGameSense0::NewGameSense0(QWidget *parent) : QMainWindow(parent)
{
    this->setFixedSize(1440,810);
    this->setWindowIcon(QPixmap(":/res/Icon.png"));
    this->setWindowTitle("选择游戏模式");

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

    MyPushButton *pveBtn=new MyPushButton(":/res/PVEBtn.png");
    pveBtn->setParent(this);
    pveBtn->move(this->width()*0.5-pveBtn->width()*0.5,
                 this->height()*0.4);

    MyPushButton *pvpBtn=new MyPushButton(":/res/PVPBtn.png");
    pvpBtn->setParent(this);
    pvpBtn->move(this->width()*0.5-pveBtn->width()*0.5,
                 this->height()*0.4+pveBtn->height()*1.5);

    newGameSense1=new NewGameSense1;

    connect(newGameSense1,&NewGameSense1::backToNewGameSense0,[=](){
        newGameSense1->hide();
        this->show();
    });
    connect(pveBtn,&MyPushButton::clicked,[=](){
        pveBtn->zoomDn();
        pveBtn->zoomUp();

        QTimer::singleShot(500,this,[=](){
            this->hide();
            newGameSense1->show();
        });
    });


    connect(pvpBtn,&MyPushButton::clicked,[=](){
        pvpBtn->zoomDn();
        pvpBtn->zoomUp();
        int boardin[10][10]={0};
        nogoSense = new NogoSense(boardin,0,1,1,this);
        connect(nogoSense,&NogoSense::backToLastStep,[=](){
            nogoSense->hide();
            this->show();
        });
        QTimer::singleShot(500,this,[=](){
            //进入游戏界面
            this->hide();
            nogoSense->show();
        });
    });
}

void NewGameSense0::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/Background0.png");
    painter.drawPixmap(0,0,pix);
}
