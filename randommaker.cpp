#include "randommaker.h"
#include <cstdlib>
#include <ctime>
#include <algorithm>

RandomMaker::RandomMaker()
{
    srand(time(0));
}

int RandomMaker::randInt(int l,int r)
{
    return rand()%(r-l+1)+l;
}

void RandomMaker::randomShuffle(std::vector<int>::iterator itl,
                                       std::vector<int>::iterator itr)
{
    int sz=itr-itl;
    for(int i=sz-1;i>=1;i--)
    {
        int j=randInt(0,i-1);
        std::swap(*(itl+i),*(itl+j));
    }
}
