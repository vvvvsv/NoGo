#include "mainsense.h"
#include "ui_mainsense.h"
#include <QPainter>
#include "mypushbutton.h"
#include <QTimer>
#include <QByteArray>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>

MainSense::MainSense(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainSense)
{
    ui->setupUi(this);

    setFixedSize(1440,810);
    setWindowIcon(QIcon(":/res/Icon.png"));
    setWindowTitle("vvsv带你下不围棋");

    connect(ui->actionquit,&QAction::triggered,[=]()
    {
        this->close();
    });

    //实现title跳动
    MyPushButton *titleBtn=new MyPushButton(":/res/Title.png");
    titleBtn->setParent(this);
    titleBtn->move(190,205);
    connect(titleBtn,&MyPushButton::clicked,[=](){
        titleBtn->zoomDn(20);
        titleBtn->zoomUp(20);
    });

    //定义了四个按钮
    MyPushButton *newGameBtn=new MyPushButton(":/res/NewGameBtn.png");
    newGameBtn->setParent(this);
    newGameBtn->move(910,250);

    MyPushButton *loadGameBtn=new MyPushButton(":/res/LoadGameBtn.png");
    loadGameBtn->setParent(this);
    loadGameBtn->move(910,250+newGameBtn->height());

    MyPushButton *achievementBtn=new MyPushButton(":/res/AchievementBtn.png");
    achievementBtn->setParent(this);
    achievementBtn->move(910+newGameBtn->width()-achievementBtn->width(),
                    250+newGameBtn->height()+loadGameBtn->height());

    MyPushButton *helpBtn=new MyPushButton(":/res/HelpBtn.png");
    helpBtn->setParent(this);
    helpBtn->move(910+newGameBtn->width()-helpBtn->width(),
                  250+newGameBtn->height()+loadGameBtn->height()
                  +achievementBtn->height());

    //定义了四个子界面
    helpSense=new HelpSense;
    newGameSense0=new NewGameSense0;
    achievementSense=new AchievementSense;

    //newgame
    connect(newGameSense0,&NewGameSense0::backToMenu,[=](){
       newGameSense0->hide();
       this->show();
    });
    connect(newGameBtn,&MyPushButton::clicked,[=](){
        newGameBtn->zoomDn();
        newGameBtn->zoomUp();

        QTimer::singleShot(500,this,[=](){
            this->hide();
            newGameSense0->show();
        });
    });

    //loadgame
    connect(loadGameBtn,&MyPushButton::clicked,[=](){
        loadGameBtn->zoomDn();
        loadGameBtn->zoomUp();

        QFile file("NogoSaveData/SaveBoard.log");
        if(!file.exists())
        {
            QMessageBox::information(this,"读档失败","没有找到存档文件");
        }
        else
        {
            file.open(QIODevice::ReadOnly);
            QByteArray allData = file.readLine();
            QTextStream out(&allData);
            unsigned long stClk,type,flag,turn;
            out>>stClk>>type>>flag>>turn;

            int boardin[10][10]={0};
            for(int i=1;i<=9;i++)
            {
                QByteArray allData = file.readLine();
                QTextStream out(&allData);
                int data;
                for(int j=1;j<=9;j++)
                {
                    out>>data;
                    boardin[i][j]=data-1;
                }
            }

            nogoSense=new NogoSense(boardin,type,bool(flag),bool(turn),this);
            nogoSense->judgement->startClock=stClk;

            connect(nogoSense,&NogoSense::backToLastStep,[=](){
                nogoSense->hide();
                this->show();
            });

            QTimer::singleShot(500,this,[=](){
                this->hide();
                nogoSense->show();
            });
        }
    });

    //achievement
    connect(achievementSense,&AchievementSense::backToMenu,[=](){
        achievementSense->hide();
        this->show();
    });
    connect(achievementBtn,&MyPushButton::clicked,[=](){
        achievementBtn->zoomDn();
        achievementBtn->zoomUp();
        QTimer::singleShot(500,this,[=](){
            this->hide();
            achievementSense->show();
        });
    });

    //help
    connect(helpSense,&HelpSense::backToMenu,[=](){
       helpSense->hide();
       this->show();
    });
    connect(helpBtn,&MyPushButton::clicked,[=](){
        helpBtn->zoomDn();
        helpBtn->zoomUp();

        QTimer::singleShot(500,this,[=](){
            this->hide();
            helpSense->show();
        });
    });
}

MainSense::~MainSense()
{
    delete ui;
}

void MainSense::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/Background0.png");
    painter.drawPixmap(0,0,pix);
}
