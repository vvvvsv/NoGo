#include "newgamesense2.h"
#include <QMenuBar>
#include <QPainter>
#include <QTimer>
#include "mypushbutton.h"

NewGameSense2::NewGameSense2(int type,QWidget *parent) : QMainWindow(parent)
{
    gameType=type;
    this->setFixedSize(1440,810);
    this->setWindowIcon(QPixmap(":/res/Icon.png"));
    this->setWindowTitle("选择游戏先后手");

    QMenuBar *bar=menuBar();
    setMenuBar(bar);

    QMenu *startMenu=bar->addMenu("开始");
    QAction *quitAction =startMenu->addAction("退出");
    QAction *backToNewGameSense1Action =startMenu->addAction("返回上一步");

    connect(quitAction,&QAction::triggered,[=](){
        this->close();
    });

    connect(backToNewGameSense1Action,&QAction::triggered,[=](){
        QTimer::singleShot(300,this,[=](){
            emit this->backToNewGameSense1();
        });
    });

    MyPushButton * blackBtn=new MyPushButton(":/res/BlackPlayerBtn.png");
    blackBtn->setParent(this);
    blackBtn->move(this->width()*0.5-blackBtn->width()*0.5,
                  this->height()*0.4);

    MyPushButton * whiteBtn=new MyPushButton(":/res/WhitePlayerBtn.png");
    whiteBtn->setParent(this);
    whiteBtn->move(this->width()*0.5-whiteBtn->width()*0.5,
                  this->height()*0.4+blackBtn->height()*1.5);

    connect(blackBtn,&MyPushButton::clicked,[=](){
        blackBtn->zoomDn();
        blackBtn->zoomUp();
        int boardin[10][10]={0};
        nogoSense=new NogoSense(boardin,gameType,1,1,this);
        connect(nogoSense,&NogoSense::backToLastStep,[=](){
            nogoSense->hide();
            this->show();
        });

        QTimer::singleShot(500,this,[=](){
            this->hide();
            nogoSense->show();
        });
    });

    connect(whiteBtn,&MyPushButton::clicked,[=](){
        whiteBtn->zoomDn();
        whiteBtn->zoomUp();
        int boardin[10][10]={0};
        nogoSense=new NogoSense(boardin,gameType,1,0,this);
        connect(nogoSense,&NogoSense::backToLastStep,[=](){
            nogoSense->hide();
            this->show();
        });

        QTimer::singleShot(500,this,[=](){
            this->hide();
            nogoSense->show();
        });
    });
}

void NewGameSense2::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/Background0.png");
    painter.drawPixmap(0,0,pix);
}
