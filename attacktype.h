#ifndef ATTACKTYPE_H
#define ATTACKTYPE_H
#include <QString>

class AttackType
{
public:
    AttackType();
    AttackType(int id,QString n, QString imSrc, int dmg, int atr, int chn);
    int id;
    QString name;
    QString imageSorce;
    int damage;
    int attackRadius;
    int chance;
    bool operator==(const AttackType& arg);
};

#endif // ATTACKTYPE_H
