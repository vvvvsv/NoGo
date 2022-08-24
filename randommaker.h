#ifndef RANDOMMAKER_H
#define RANDOMMAKER_H

#include <vector>

class RandomMaker
{
    private:
    int randInt(int l,int r);

    public:
    RandomMaker();
    void randomShuffle(std::vector<int>::iterator itl,
                              std::vector<int>::iterator itr);
};

#endif // RANDOMMAKER_H
