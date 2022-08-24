#include "gamejudge.h"
#include <cstring>

GameJudge::GameJudge(int type,bool flag,bool turn)
{
    gameType=type;
    playerFlag=flag;
    playerTurn=turn;
    memset(board,0,sizeof(board));
}

void GameJudge::startGame(int boardin[10][10])
{
    for(int i=1;i<=9;i++)
        for(int j=1;j<=9;j++) board[i][j]=boardin[i][j];
    startClock=clock();
    playing=1;

    if(gameType!=0)
    {
        aiPlayer=new AiPlayer();
        if(gameType==1) aiPlayer->setTFORUCT(10);
        else if(gameType==2) aiPlayer->setTFORUCT(1000);
        else aiPlayer->setTFORUCT(5000);
    }
    else
    {
        aiPlayer=new AiPlayer();
        aiPlayer->setTFORUCT(1000);
    }
}

void GameJudge::updateGameMap(int row, int col)
{
    if(playerFlag) board[row][col]=1;
    else board[row][col]=-1;

    playerFlag^=1;
    if(gameType!=0) playerTurn^=1;
}

void GameJudge::actionByPerson(int row, int col)
{
    updateGameMap(row,col);
}

int GameJudge::HelpByAI()
{
    if(playerFlag) aiPlayer->init(board,-1);
    else           aiPlayer->init(board, 1);

    return aiPlayer->calcAiOpt();
}

void GameJudge::actionByAI(int &clickRow, int &clickCol)
{
    if(playerFlag) aiPlayer->init(board,-1);
    else           aiPlayer->init(board, 1);

    int xy=aiPlayer->calcAiOpt();
    clickRow=xy/10;
    clickCol=xy%10;
    updateGameMap(clickRow,clickCol);
}

bool GameJudge::inBoard(int x, int y)
{
    return x>=1 && x<=9 && y>=1 && y<=9;
}

bool GameJudge::findair(int x, int y)
{
    vis[x][y]=1;
    int flag=0;
    for(int dir=0;dir<4;dir++)
    {
        int tx=x+tox[dir],ty=y+toy[dir];
        if(inBoard(tx,ty))
        {
            if(!board[tx][ty]) flag=1;
            if(board[tx][ty]==board[x][y] && !vis[tx][ty])
                if(findair(tx,ty)) flag=1;
        }
    }
    return flag;
}

bool GameJudge::judgeIfEnd()
{
    memset(vis,0,sizeof(vis));
    for(int i=1;i<=9;i++)
        for(int j=1;j<=9;j++)
        {
            if(!vis[i][j] && board[i][j])
                if(!findair(i,j)) return 1;
        }
    return 0;
}
