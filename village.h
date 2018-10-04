#ifndef VILLAGE_H
#define VILLAGE_H
#include "player.h"

class Village
{
public:
    Village(int cellx,int celly);
    Player *player;
    int cellx;
    int celly;
};

#endif // VILLAGE_H
