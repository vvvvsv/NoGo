#include "newgamesense1.h"
#include <QMenuBar>
#include <QPainter>
#include <QTimer>
#include "mypushbutton.h"

NewGameSense1::NewGameSense1(QWidget *parent) : QMainWindow(parent)
{
    this->setFixedSize(1440,810);
    this->setWindowIcon(QPixmap(":/res/Icon.png"));
    this->setWindowTitle("选择游戏难度");

    QMenuBar *bar=menuBar();
    setMenuBar(bar);

    QMenu *startMenu=bar->addMenu("开始");
    QAction *quitAction =startMenu->addAction("退出");
    QAction *backToNewGameSense0Action =startMenu->addAction("返回上一步");

    connect(quitAction,&QAction::triggered,[=](){
        this->close();
    });

    connect(backToNewGameSense0Action,&QAction::triggered,[=](){
        QTimer::singleShot(300,this,[=](){
            emit this->backToNewGameSense0();
        });
    });

    MyPushButton * easyBtn=new MyPushButton(":/res/EasyModeBtn.png");
    easyBtn->setParent(this);
    easyBtn->move(this->width()*0.5-easyBtn->width()*0.5,
                  this->height()*0.3);

    MyPushButton * normalBtn=new MyPushButton(":/res/NormalModeBtn.png");
    normalBtn->setParent(this);
    normalBtn->move(this->width()*0.5-normalBtn->width()*0.5,
                  this->height()*0.3+easyBtn->height()*1.3);

    MyPushButton * hardBtn=new MyPushButton(":/res/HardModeBtn.png");
    hardBtn->setParent(this);
    hardBtn->move(this->width()*0.5-hardBtn->width()*0.5,
                  this->height()*0.3+easyBtn->height()*1.3+normalBtn->height()*1.3);


    connect(easyBtn,&MyPushButton::clicked,[=](){
        easyBtn->zoomDn();
        easyBtn->zoomUp();
        //选择先后手
        newGameSense2=new NewGameSense2(1,this);
        connect(newGameSense2,&NewGameSense2::backToNewGameSense1,[=](){
            newGameSense2->hide();
            this->show();
        });

        QTimer::singleShot(500,this,[=](){
            this->hide();
            newGameSense2->show();
        });
    });

    connect(normalBtn,&MyPushButton::clicked,[=](){
        normalBtn->zoomDn();
        normalBtn->zoomUp();
        //选择先后手
        newGameSense2=new NewGameSense2(2,this);
        connect(newGameSense2,&NewGameSense2::backToNewGameSense1,[=](){
            newGameSense2->hide();
            this->show();
        });

        QTimer::singleShot(500,this,[=](){
            this->hide();
            newGameSense2->show();
        });
    });

    connect(hardBtn,&MyPushButton::clicked,[=](){
        hardBtn->zoomDn();
        hardBtn->zoomUp();
        //选择先后手
        newGameSense2=new NewGameSense2(3,this);
        connect(newGameSense2,&NewGameSense2::backToNewGameSense1,[=](){
            newGameSense2->hide();
            this->show();
        });

        QTimer::singleShot(500,this,[=](){
            this->hide();
            newGameSense2->show();
        });
    });
}

void NewGameSense1::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/Background0.png");
    painter.drawPixmap(0,0,pix);
}
