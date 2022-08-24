#include "achievementsense.h"
#include "ui_achievementsense.h"
#include <QMenuBar>
#include <QPainter>
#include <QTimer>
#include <QFile>
#include <QTextStream>
#include <QStandardItemModel>
#include <QTableWidget>
#include <QByteArray>
#include <QString>

AchievementSense::AchievementSense(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AchievementSense)
{
    ui->setupUi(this);

    this->setFixedSize(1440,810);
    this->setWindowIcon(QPixmap(":/res/Icon.png"));
    this->setWindowTitle("成就");

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

    //设置tablewidget
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget->setSelectionMode(QAbstractItemView::NoSelection);
    ui->tableWidget->verticalHeader()->setVisible(false); //隐藏列表头
    ui->tableWidget->horizontalHeader()->setVisible(false); //隐藏行表头

    ui->tableWidget->resizeColumnsToContents();
    ui->tableWidget->resizeRowsToContents();

    ui->tableWidget->setFixedSize(960,540);
    ui->tableWidget->move(this->width()*0.5-ui->tableWidget->width()*0.5+30,
                          this->height()*0.5-ui->tableWidget->height()*0.5+20);

    ui->tableWidget->
            setStyleSheet("background-color:rgba(0,0,0,0)");
    ui->tableWidget->setShowGrid(0);
    ui->tableWidget->setColumnWidth(0,447);
    ui->tableWidget->setColumnWidth(1,30);
    ui->tableWidget->setColumnWidth(2,30);
    ui->tableWidget->setColumnWidth(3,447);
    for(int i=0;i<11;i++)
        ui->tableWidget->setRowHeight(i,48);
}

AchievementSense::~AchievementSense()
{
    delete ui;
}

void AchievementSense::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/Background0.png");
    painter.drawPixmap(0,0,pix);

    //建立文件读写，把"Achievement.log"里面的东西输进来
    QFile file("NogoSaveData/Achievement.log");
    file.open(QIODevice::ReadOnly);

    for(int i=0;i<3;i++)
    {
        QByteArray allData = file.readLine();
        QTextStream out(&allData);
        unsigned long total,win,fastestWin;
        out>>total>>win>>fastestWin;

        if(total)
        {
            QTableWidgetItem *item=new QTableWidgetItem(QString::number(total));
            ui->tableWidget->setItem(i*3,3,item);

            item=new QTableWidgetItem(QString::number((double)win/total));
            ui->tableWidget->setItem(i*3+1,3,item);

            if(win)
            {
                int seconds=fastestWin/1000;
                int minutes=seconds/60;
                seconds=seconds%60;
                QString time=QString::number(minutes)+"m"+QString::number(seconds)+"s";
                item=new QTableWidgetItem(time);
                ui->tableWidget->setItem(i*3+2,3,item);
            }
            else
            {
                item=new QTableWidgetItem("还没有获胜过哦");
                ui->tableWidget->setItem(i*3+2,3,item);
            }
        }
        else
        {
            QTableWidgetItem *item=new QTableWidgetItem("还没有挑战过哦");
            ui->tableWidget->setItem(i*3,3,item);
            item=new QTableWidgetItem("还没有挑战过哦");
            ui->tableWidget->setItem(i*3+1,3,item);
            item=new QTableWidgetItem("还没有挑战过哦");
            ui->tableWidget->setItem(i*3+2,3,item);
        }
    }
}
