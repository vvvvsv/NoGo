#include "validcounter.h"
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;

ValidCounter::ValidCounter()
{

}

bool ValidCounter::inBoard(int x,int y)
{
    return x>=1 && x<=9 && y>=1 && y<=9;
}

void ValidCounter::dfsPoints(int board[10][10],int x,int y)
{
    vis[x][y]=1;

    for(int dir=0;dir<4;dir++)
    {
        int tx=x+tox[dir],ty=y+toy[dir];
        if(inBoard(tx,ty))
        {
            if(!board[tx][ty]) gas[++cnt]=tx*10+ty;
            else if(board[tx][ty]==board[x][y] && !vis[tx][ty])
                dfsPoints(board,tx,ty);
        }
    }
}

void ValidCounter::excludeDuplicateGas()
{
    sort(gas+1,gas+cnt+1);
    tmpcnt=0;
    for(int i=1;i<=cnt;i++)
        if(gas[i]!=gas[i-1]) tmpgas[++tmpcnt]=gas[i];

    cnt=tmpcnt;
    for(int i=1;i<=cnt;i++) gas[i]=tmpgas[i];
}

vector<int> ValidCounter::calcValidPoints(int board[10][10],int col)
{
    memset(vis,0,sizeof(vis));
    char gasValue[100]={0};
    //1  第0位表示是(1)否(0)为对方唯一气
    //2  第1位表示是(1)否(0)为对方传统眼
    //4  第2位表示是(1)否(0)为自己唯一气
    //8  第3位表示是(1)否(0)为自己非唯一气
    //16 第4位表示是(1)否(0)四周有气
    for(int i=1;i<=9;i++)
        for(int j=1;j<=9;j++)
            if(board[i][j]!=0 && vis[i][j]==0)
            {
                cnt=0;
                dfsPoints(board,i,j);
                excludeDuplicateGas();

                if(col==board[i][j])
                {
                    //这一块是自己的
                    if(cnt==1) gasValue[gas[1]]|=4;
                    else if(cnt>1)
                        for(int k=1;k<=cnt;k++) gasValue[gas[k]]|=8;
                }
                else
                {
                    //这一块是对方的
                    if(cnt==1) gasValue[gas[1]]|=1;
                }
            }

    for(int i=1;i<=9;i++)
        for(int j=1;j<=9;j++)
        {
            bool flag1=1,flag2=0;
            //flag1表示是否是对方传统眼,flag2表示是否四周有气
            for(int dir=0;dir<4;dir++)
            {
                int tx=i+tox[dir],ty=j+toy[dir];
                if(inBoard(tx,ty))
                {

                    if(board[tx][ty]!=-col) flag1=0;
                    if(board[tx][ty]==0)    flag2=1;
                }
            }

            if(flag1) gasValue[i*10+j]|=2;
            if(flag2) gasValue[i*10+j]|=16;
        }

    vector <int> ans;
    for(int i=1;i<=9;i++)
        for(int j=1;j<=9;j++)
            if(!board[i][j])
            {
                int tmp=gasValue[i*10+j];
                if((tmp&1) || (tmp&2) || ((tmp&4) && (!(tmp&8)) && (!(tmp&16)))) continue;
                else ans.push_back(i*10+j);
            }
    return ans;
}
