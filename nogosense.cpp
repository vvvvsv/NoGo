#include "nogosense.h"
#include "ui_nogosense.h"
#include <QPainter>
#include <QBrush>
#include <QPixmap>
#include <QTimer>
#include <QDebug>
#include "mypushbutton.h"
#include <QMouseEvent>
#include <cmath>
#include <QPoint>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QSound>
#include <QUrl>

const int lucWidth=720;
const int lucHeight=250;
const int radius=15;
const int markSize=6;
const int blockSize=50;
const int posDelta=20;

NogoSense::NogoSense(int boardin[10][10],int type,bool flag,bool turn,QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::NogoSense)
{
    ui->setupUi(this);

    mediaPlayer=new QMediaPlayer;
    mediaPlayer->setMedia(QUrl("qrc:/res/bgm.wav"));
    mediaPlayer->setVolume(100);
    playingMedia=0;

    gameType=type;
    playerFlag=flag;
    playerTurn=turn;

    this->setFixedSize(1440,810);
    this->setWindowIcon(QPixmap(":/res/Icon.png"));
    this->setWindowTitle("vvsv带你下不围棋");

    QMenuBar *bar=menuBar();
    setMenuBar(bar);

    QMenu *startMenu=bar->addMenu("开始");
    QAction *quitAction =startMenu->addAction("退出");
    QAction *backToLastAction =startMenu->addAction("返回上一步");

    connect(quitAction,&QAction::triggered,[=](){
        this->close();
    });

    connect(backToLastAction,&QAction::triggered,[=](){
        QTimer::singleShot(300,this,[=](){
            mediaPlayer->stop();
            emit this->backToLastStep();
        });
    });

    //title按钮
    MyPushButton *titleBtn=new MyPushButton(":/res/TitleSmall.png");
    titleBtn->setParent(this);
    titleBtn->move(180,295);
    connect(titleBtn,&MyPushButton::clicked,[=](){
        titleBtn->zoomDn();
        titleBtn->zoomUp();

        if(playingMedia) mediaPlayer->stop();
        else mediaPlayer->play();
        playingMedia^=1;
    });

    //pause/save/help按钮
    MyPushButton *pauseBtn=new MyPushButton(":/res/PauseBtn.png");
    pauseBtn->setParent(this);
    pauseBtn->move(705,90);

    connect(pauseBtn,&MyPushButton::clicked,[=](){
        pauseBtn->zoomDn();
        pauseBtn->zoomUp();
        judgement->playing^=1;

        playingMedia=judgement->playing;
        if(!judgement->playing) mediaPlayer->stop();
        else mediaPlayer->play();
    });

    MyPushButton *saveBtn=new MyPushButton(":/res/SaveBtn.png");
    saveBtn->setParent(this);
    saveBtn->move(705+pauseBtn->width()*1.2,90);

    connect(saveBtn,&MyPushButton::clicked,[=](){
        saveBtn->zoomDn();
        saveBtn->zoomUp();

        QFile file("NogoSaveData/SaveBoard.log");
        file.open(QIODevice::WriteOnly | QIODevice::Text);
        QTextStream output(&file);

        output<<judgement->startClock<<" "<<judgement->gameType<<" "
              <<(int)playerFlag<<" "<<(int)playerTurn<<endl;
        for(int i=1;i<=9;i++)
        {
            for(int j=1;j<=9;j++)
            {
                output<<judgement->board[i][j]+1<<" ";
            }
            output<<endl;
        }
        file.close();
        QMessageBox::information(this,"存档成功","耶~耶~peace~peace~");
    });

    MyPushButton *helpBtn=new MyPushButton(":/res/HelpPlayBtn.png");
    helpBtn->setParent(this);
    helpBtn->move(705+pauseBtn->width()*1.2+saveBtn->width()*1.2,90);

    connect(helpBtn,&MyPushButton::clicked,[=](){
        helpBtn->zoomDn();
        helpBtn->zoomUp();
        if(judgement->playerTurn==1)
        {
            int xy=judgement->HelpByAI();
            int row=xy/10,col=xy%10;

            QSound::play(":/res/Chess.wav");
            judgement->board[row][col]=2;
            update();
            QTimer::singleShot(700,this,[=](){
                judgement->board[row][col]=0;
            });
            update();
        }
    });

    this->centralWidget()->setMouseTracking(true);
    this->setMouseTracking(true);
    //开始游戏
    judgement=new GameJudge(gameType,playerFlag,playerTurn);
    judgement->startGame(boardin);
    if(gameType!=0)//PVE
        if(playerTurn==0) chessOneByAI();

    update();
}

NogoSense::~NogoSense()
{
    delete ui;
}

void NogoSense::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/Background0.png");
    painter.drawPixmap(0,0,pix);

    //抗锯齿
    painter.setRenderHint(QPainter::Antialiasing, true);

    //画棋盘
    for(int i=0;i<9;i++)
    {
        painter.drawLine(QPointF(lucWidth,lucHeight+blockSize*i),
                         QPointF(lucWidth+blockSize*8,lucHeight+blockSize*i));
        painter.drawLine(QPointF(lucWidth+blockSize*i,lucHeight),
                         QPointF(lucWidth+blockSize*i,lucHeight+blockSize*8));
    }

    //画mark
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    if(clickPosCol>=1 && clickPosCol<=9 && clickPosRow>=1 && clickPosRow<=9
            && judgement->board[clickPosRow][clickPosCol]==0)
    {
        if(judgement->playerFlag) brush.setColor("black");
        else brush.setColor("white");

        painter.setBrush(brush);
        painter.drawRect(QRect(lucWidth+blockSize*(clickPosCol-1)-markSize*0.5,
                         lucHeight+blockSize*(clickPosRow-1)-markSize*0.5,markSize,markSize));
    }

    //画棋子
    for(int i=0;i<9;i++)
        for(int j=0;j<9;j++)
        {
            if(judgement->board[i+1][j+1]==1)
            {
                brush.setColor("black");
                painter.setBrush(brush);
                painter.drawEllipse(QPoint(lucWidth+blockSize*j,lucHeight+blockSize*i),
                                    radius,radius);
            }
            if(judgement->board[i+1][j+1]==-1)
            {
                brush.setColor("white");
                painter.setBrush(brush);
                painter.drawEllipse(QPoint(lucWidth+blockSize*j,lucHeight+blockSize*i),
                                    radius,radius);
            }
            if(judgement->board[i+1][j+1]==2)
            {
                brush.setColor("blue");
                painter.setBrush(brush);
                painter.drawEllipse(QPoint(lucWidth+blockSize*j,lucHeight+blockSize*i),
                                    radius,radius);
            }
        }
}

void NogoSense::mouseMoveEvent(QMouseEvent *event)
{
    int x = event->x();
    x-=lucWidth;
    int y = event->y();
    y-=lucHeight;

    if(x>=-20 && x<=blockSize*8+20 && y>=-20 && y<=blockSize*8+20)
    {
        int col=x/blockSize,row=y/blockSize,len;
        clickPosCol=clickPosRow=0;

        len=sqrt((x-col*blockSize)*(x-col*blockSize)+
                 (y-row*blockSize)*(y-row*blockSize));
        if(len<posDelta) {clickPosCol=col+1,clickPosRow=row+1;}

        len=sqrt((x-(col+1)*blockSize)*(x-(col+1)*blockSize)+
                 (y-row*blockSize)*(y-row*blockSize));
        if(len<posDelta) {clickPosCol=col+2,clickPosRow=row+1;}

        len=sqrt((x-col*blockSize)*(x-col*blockSize)+
                 (y-(row+1)*blockSize)*(y-(row+1)*blockSize));
        if(len<posDelta) {clickPosCol=col+1,clickPosRow=row+2;}

        len=sqrt((x-(col+1)*blockSize)*(x-(col+1)*blockSize)+
                 (y-(row+1)*blockSize)*(y-(row+1)*blockSize));
        if(len<posDelta) {clickPosCol=col+2,clickPosRow=row+2;}
    }
    update();
}

void NogoSense::mouseReleaseEvent(QMouseEvent *event)
{
    if(judgement->playing)
        if(!(judgement->gameType!=0 && judgement->playerTurn==0))
        {
            chessOneByPerson();
            if(judgement->gameType!=0 && judgement->playerTurn==0)
            {
                QTimer::singleShot(200,this,[=](){
                    chessOneByAI();
                });
            }
        }
}

void NogoSense::chessOneByPerson()
{
    if(clickPosCol>=1 && clickPosCol<=9 && clickPosRow>=1 && clickPosRow<=9 &&
            judgement->board[clickPosRow][clickPosCol]==0)
    {
        QSound::play(":/res/Chess.wav");
        judgement->actionByPerson(clickPosRow,clickPosCol);
        int sx=clickPosRow,sy=clickPosCol;
        update();

        if(judgement->judgeIfEnd())
        {
            QMessageBox::StandardButton ret=
                    QMessageBox::question(this, "这么下就结束了哦", "要悔棋吗？",
                                          QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);

           if(ret==QMessageBox::Yes)
           {
               judgement->actionByPerson(sx,sy);
               judgement->board[sx][sy]=0;
           }
           else
           {
                //人类输了
                if(gameType==0)
                {
                    QString str;
                    if(judgement->playerFlag) str="黑方选手";
                    else str="白方选手";
                    QMessageBox::StandardButton btnValue =
                            QMessageBox::information(this,"游戏结束",str+"获胜！");
                    if (btnValue == QMessageBox::Ok)
                    {
                        judgement->gameType=gameType;
                        judgement->playerFlag=playerFlag;
                        judgement->playerTurn=playerTurn;
                        int boardin[10][10]={0};
                        judgement->startGame(boardin);
                    }
                }
                else
                {
                    //失败记录到成就里面
                    QFile file("NogoSaveData/Achievement.log");
                    file.open(QIODevice::ReadOnly);

                    unsigned long data[4][3]={0};
                    for(int i=1;i<=3;i++)
                    {
                        QByteArray allData = file.readLine();
                        QTextStream out(&allData);
                        out>>data[i][0]>>data[i][1]>>data[i][2];
                    }
                    data[gameType][0]++;
                    file.close();
                    file.open(QIODevice::WriteOnly | QIODevice::Text);
                    QTextStream achOutput(&file);
                    for(int i=1;i<=3;i++)
                    {
                        for(int j=0;j<=2;j++)
                            achOutput<<data[i][j]<<" ";
                        achOutput<<endl;
                    }
                    file.close();

                    QMessageBox::StandardButton btnValue =
                            QMessageBox::information(this,"游戏结束","落败！");
                    if (btnValue == QMessageBox::Ok)
                    {
                        judgement->gameType=gameType;
                        judgement->playerFlag=playerFlag;
                        judgement->playerTurn=playerTurn;
                        int boardin[10][10]={0};
                        judgement->startGame(boardin);
                    }
                }
            }
        }
    }
}

void NogoSense::chessOneByAI()
{
    QSound::play(":/res/Chess.wav");
    judgement->actionByAI(clickPosRow,clickPosCol);
    update();

    if(judgement->judgeIfEnd())
    {
        //bot输了
        //记录到成就
        QFile file("NogoSaveData/Achievement.log");
        file.open(QIODevice::ReadOnly);

        unsigned long data[4][3]={0};
        for(int i=1;i<=3;i++)
        {
            QByteArray allData = file.readLine();
            QTextStream out(&allData);
            out>>data[i][0]>>data[i][1]>>data[i][2];
        }
        data[gameType][0]++;
        data[gameType][1]++;
        if(data[gameType][1]==1) data[gameType][2]=clock()-judgement->startClock;
        else data[gameType][2]=min(data[gameType][2],clock()-judgement->startClock);
        file.close();

        file.open(QIODevice::WriteOnly | QIODevice::Text);
        QTextStream achOutput(&file);
        for(int i=1;i<=3;i++)
        {
            for(int j=0;j<=2;j++)
                achOutput<<data[i][j]<<" ";
            achOutput<<endl;
        }
        file.close();
        QMessageBox::StandardButton btnValue =
                QMessageBox::information(this,"游戏结束","获胜！");
        if (btnValue == QMessageBox::Ok)
        {
            judgement->gameType=gameType;
            judgement->playerFlag=playerFlag;
            judgement->playerTurn=playerTurn;
            int boardin[10][10]={0};
            judgement->startGame(boardin);
        }
    }
}
