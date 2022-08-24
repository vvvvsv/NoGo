#ifndef GAMEJUDGE_H
#define GAMEJUDGE_H

#include "aiplayer.h"
#include <ctime>

class GameJudge
{
private:
    int vis[10][10];
    int tox[4]={0,0,1,-1};
    int toy[4]={1,-1,0,0};
    bool inBoard(int x,int y);
    bool findair(int x,int y);


public:
    GameJudge(int type,bool flag,bool turn);
public:
    unsigned long startClock;
    bool playing;
    int board[10][10];//空白0,白子-1,黑子1
    bool playerFlag;//为1是黑子
    bool playerTurn;//为1是人类
    int gameType;//0是PVP,1是PVE_EASY,2是PVE_NORMAL,3是PVE_HARD
    AiPlayer *aiPlayer=nullptr;

    void startGame(int boardin[10][10]);
    void actionByPerson(int row, int col);
    int  HelpByAI();
    void actionByAI(int &clickRow, int &clickCol);
    void updateGameMap(int row, int col);
    bool judgeIfEnd();
};

#endif // GAMEJUDGE_H
