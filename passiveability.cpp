#include "passiveability.h"

PassiveAbility::PassiveAbility()
{

}

PassiveAbility::PassiveAbility(int id, QString n, Side s, int vl, int abr , AbilityType at)
{
    this->id = id;
    name = n;
    side  = s;
    value = vl;
    abilityRadius = abr;
    abilityType = at;
}

bool PassiveAbility::operator==(const PassiveAbility& arg)
{
    if (this->id == arg.id)
        return true;
    return false;
}
