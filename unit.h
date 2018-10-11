#ifndef UNIT_H
#define UNIT_H

#include <QString>
#include <unittype.h>
#include <QObject>
#include "player.h"
#include <qmath.h>

class Unit
{
public:

    Unit();
    Unit(UnitType *unittype);
    Unit(UnitType *unittype,Player *p, int cellx, int celly);
    Player *player;
    UnitType *type;


    void setHp(double hp);
    double getHp();
    void setMp(double mp);
    double getMp();
    void setAp(int ap);
    int getAp();
    void setModOff(double mo);
    double getModOff();
    void setModDef(double md);
    double getModDef();
    void setModDmg(double dmg);
    double getModDmg();
    void setMorale(double mor);
    double getMorale();
    void setCellx(int c);
    int getCellx();
    void setCelly(int c);
    int getCelly();
    bool isFocusEmpty();
    bool attack(Unit *target); //возвращает убита ли цель
    bool isAttackPossible(Unit *target);
    bool operator==(const Unit& arg);
    bool isMovementPossible(int **map, bool **occupancy, int cellx, int celly);
    void move(int **map, bool **occupancy, int cellx, int celly);

private:
    double hp; //current
    double mp;
    int ap;
    double modifierOff;
    double modifierDef;
    double modifierMp;
    double modifierDamage;
    double morale;
    int cellx;
    int celly;
};

#endif // UNIT_H
