#ifndef AIPLAYER_H
#define AIPLAYER_H

#include "randommaker.h"
#include "validcounter.h"
#include <vector>
#include <queue>
using namespace std;

const int MAXNFORUCT=1e4;

class AiPlayer
{
public:
    RandomMaker *randomMaker=nullptr;
    ValidCounter *validCounter=nullptr;

private:
    class TreeNode
    {
        public:
        int board[10][10];

        int color;
        //表示下子到当前局面的是人类(1)还是机器(-1)

        double win;
        int total;
        //表示下子到当前局面的角色输赢次数

        int father;
        vector <int> children;

        int maxChildCount;
        queue <int> validChild;

        int validForNod,validForEnm;

        void calcValidChild();

        RandomMaker *playerRandomMaker;
        ValidCounter *playerValidCounter;
    }node[MAXNFORUCT+5];
private:
    int root=0,cnt=0;

private:
    bool isEndBoard(int nod);
    bool isAllExpand(int nod);
    double calcUcb(int nod,double cForUcb);
    int bestChild(int nod,double cForUcb);
    int newNode(int fa,int x,int y);
    int expand(int nod);
    double simulate(int nod);
    void UCT(int nod);

public:
    AiPlayer();
    void init(int board[10][10],int color);

private:
    int TFORUCT;
public:
    void setTFORUCT(int x);
    int calcAiOpt();
};

#endif // AIPLAYER_H
