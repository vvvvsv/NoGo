#ifndef VALIDCOUNTER_H
#define VALIDCOUNTER_H
#include <vector>

class ValidCounter
{
    private:
    int vis[10][10];
    int tox[4]={0,0,1,-1};
    int toy[4]={1,-1,0,0};

    bool inBoard(int x,int y);

    int gas[100],cnt;
    void dfsPoints(int board[10][10],int x,int y);

    int tmpgas[100],tmpcnt;
    void excludeDuplicateGas();

    public:
    ValidCounter();
    std::vector<int> calcValidPoints(int board[10][10],int col);
};

#endif // VALIDCOUNTER_H
