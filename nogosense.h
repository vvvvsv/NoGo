#ifndef NOGOSENSE_H
#define NOGOSENSE_H

#include <QMainWindow>
#include "gamejudge.h"
#include <QMediaPlayer>

namespace Ui {
class NogoSense;
}

class NogoSense : public QMainWindow
{
    Q_OBJECT

public:
    explicit NogoSense(int boardin[10][10],int type,bool flag,bool turn,QWidget *parent = 0);
    ~NogoSense();
    GameJudge *judgement;

private:
    void paintEvent(QPaintEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

private:
    Ui::NogoSense *ui;
    int gameType;
    bool playerFlag;//为1是黑子
    bool playerTurn;//为1是人类
    int clickPosRow,clickPosCol;
    void chessOneByPerson(); // 人执行
    void chessOneByAI(); // AI下棋
    QMediaPlayer* mediaPlayer;
    bool playingMedia;

signals:
    void backToLastStep();
};

#endif // NOGOSENSE_H
