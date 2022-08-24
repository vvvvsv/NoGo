#include "loadgamesense.h"
#include "ui_loadgamesense.h"
#include <QMenuBar>
#include <QPainter>
#include <QTimer>

LoadGameSense::LoadGameSense(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LoadGameSense)
{
    ui->setupUi(this);
    this->setFixedSize(1440,810);
    this->setWindowIcon(QPixmap(":/res/Icon.png"));
    this->setWindowTitle("加载游戏存档");

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

LoadGameSense::~LoadGameSense()
{
    delete ui;
}

void LoadGameSense::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/Background0.png");
    painter.drawPixmap(0,0,pix);
}
