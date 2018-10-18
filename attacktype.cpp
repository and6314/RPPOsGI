#include "attacktype.h"

AttackType::AttackType()
{

}

AttackType::AttackType(int id,QString n, QString imSrc, int dmg, int atr, int chn)
{
    this->id = id;
    name = n;
    imageSorce = imSrc;
    damage = dmg;
    attackRadius = atr;
    chance = chn;
}

bool AttackType::operator==(const AttackType& arg)
{
    if (this->id == arg.id)
        return true;
    return false;
}
