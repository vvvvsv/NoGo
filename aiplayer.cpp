#include "aiplayer.h"
#include <cmath>

AiPlayer::AiPlayer()
{
    randomMaker=new RandomMaker();
    validCounter=new ValidCounter();
}

void AiPlayer::TreeNode::calcValidChild()
{
    while(!validChild.empty()) validChild.pop();

    vector <int> vldcd=playerValidCounter->calcValidPoints(board,-color);
    playerRandomMaker->randomShuffle(vldcd.begin(),vldcd.end());
    maxChildCount=vldcd.size();
    for(vector<int>::iterator it=vldcd.begin();it!=vldcd.end();it++)
        validChild.push(*it);

    validForNod=maxChildCount;
    validForEnm=playerValidCounter->calcValidPoints(board,color).size();
}

bool AiPlayer::isEndBoard(int nod)
{
    return (node[nod].maxChildCount==0);
}

bool AiPlayer::isAllExpand(int nod)
{
    return node[nod].validChild.empty();
}

double AiPlayer::calcUcb(int nod,double cForUcb)
{
    TreeNode t=node[nod],fa=node[node[nod].father];
    return t.win/t.total+cForUcb*sqrt(log(fa.total)/t.total);
}

int AiPlayer::bestChild(int nod,double cForUcb)
{
    double mx=-1e9;
    int pos=0;
    for(vector<int>::iterator it=node[nod].children.begin();it!=node[nod].children.end();it++)
    {
        int tmp=(*it);
        double ucb=calcUcb(tmp,cForUcb);
        if(ucb>mx)
        {
            mx=ucb;
            pos=tmp;
        }
    }
    return pos;
}

int AiPlayer::newNode(int fa,int x,int y)
{
    int nod=++cnt;

    for(int i=1;i<=9;i++)
        for(int j=1;j<=9;j++)
        {
            node[nod].board[i][j]=node[fa].board[i][j];
        }
    node[nod].board[x][y]=node[nod].color=-node[fa].color;

    node[nod].father=fa;
    node[nod].children.clear();

    node[nod].playerRandomMaker=randomMaker;
    node[nod].playerValidCounter=validCounter;
    node[nod].calcValidChild();

    node[fa].children.push_back(nod);

    node[nod].win=0;
    node[nod].total=0;

    return nod;
}

int AiPlayer::expand(int nod)
{
    int xy=node[nod].validChild.front();
    node[nod].validChild.pop();

    int x=xy/10,y=xy%10;
    return newNode(nod,x,y);
}

double AiPlayer::simulate(int nod)
{
    int tmp1=node[nod].validForEnm,tmp2=node[nod].validForNod;
    //tmp1表示下子到这个点的人手数
    if(tmp1==0 && tmp2==0) return 0.0;
    return (double)(tmp1-tmp2)/(tmp1+tmp2);
}

void AiPlayer::UCT(int nod)
{
    while(isEndBoard(nod)==0)
    {
        if(isAllExpand(nod)==0)
        {
            nod=expand(nod);
            break;
        }
        else nod=bestChild(nod,1.414214);
    }
    double value=simulate(nod);
    while(nod>0)
    {
        node[nod].total++;
        node[nod].win+=value;
        value=-value;
        nod=node[nod].father;
    }
}

void AiPlayer::init(int board[10][10],int color)
{
    root=cnt=1;
    for(int i=1;i<=9;i++)
        for(int j=1;j<=9;j++)
        {
            node[1].board[i][j]=board[i][j];
        }
    node[1].color=color;

    node[1].father=0;
    node[1].children.clear();

    node[1].playerRandomMaker=randomMaker;
    node[1].playerValidCounter=validCounter;
    node[1].calcValidChild();

    node[1].win=0;
    node[1].total=0;
}

void AiPlayer::setTFORUCT(int x) {TFORUCT=x;}

int AiPlayer::calcAiOpt()
{
    if(isEndBoard(root))
    {
        //只能去世了
        for(int i=1;i<=9;i++)
            for(int j=1;j<=9;j++)
                if(!node[root].board[i][j])
                    return i*10+j;
    }

    for(int kase=1;kase<=TFORUCT;kase++) UCT(root);

    int bstcd=bestChild(root,0);
    for(int i=1;i<=9;i++)
        for(int j=1;j<=9;j++)
        {
            if(node[root].board[i][j]!=node[bstcd].board[i][j])
                return i*10+j;
        }
    return -1;
}
