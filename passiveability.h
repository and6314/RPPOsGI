#ifndef PASSIVEABILITY_H
#define PASSIVEABILITY_H
#include <QString>

enum Side{Ally,Foe};
enum AbilityType{Inspiration,Demoralization,Hill,Poison};

class PassiveAbility
{
public:
    PassiveAbility();
    PassiveAbility(int id, QString n, Side s, int vl, int abr, AbilityType at);
    int id;
    QString name;
    Side side;
    int value;
    int abilityRadius;
    AbilityType abilityType;
    bool operator==(const PassiveAbility& arg);
};

#endif // PASSIVEABILITY_H
