#include "unit.h"

Unit::Unit()
{

}

Unit::Unit(UnitType *unittype)
{
    this->type = unittype;
    this->hp = type->getNorm_hp();
    this->mp = type->getNorm_mp();
    this->ap = type->getNorm_ap();
    this->modifierOff = 0;
    this->modifierDef = 0;
    this->modifierMp = 0;
    this->modifierDamage = 0;
    this->morale = unittype->getNorm_morale();
}

Unit::Unit(UnitType *unittype,Player *p, int cellx, int celly)
{
    this->type = unittype;
    this->hp = unittype->getNorm_hp();
    this->mp = unittype->getNorm_mp();
    this->ap = unittype->getNorm_ap();
    this->modifierOff = 0;
    this->modifierDef = 0;
    this->modifierMp = 0;
    this->modifierDamage = 0;
    this->morale = unittype->getNorm_morale();
    this->cellx = cellx;
    this->celly = celly;
    player = p;
    player->units+=1;
}

void Unit::setHp(double hp)
{
    this->hp = hp;
}

double Unit::getHp()
{
    return this->hp;
}

void Unit::setMp(double mp)
{
    this->mp = mp;
}

double Unit::getMp()
{
    return this->mp;
}

void Unit::setAp(int ap)
{
    this->ap = ap;
}

int Unit::getAp()
{
    return this->ap;
}

void Unit::setModOff(double mo)
{
    this->modifierOff = mo;
}

double Unit::getModOff()
{
    return this->modifierOff;
}

void Unit::setModDef(double md)
{
    this->modifierDef = md;
}

double Unit::getModDef()
{
    return this->modifierDef;
}

void Unit::setModDmg(double dmg)
{
    this->modifierDamage = dmg;
}

double Unit::getModDmg()
{
    return this->modifierDamage;
}

void Unit::setMorale(double mor)
{
    this->morale = mor;
}

double Unit::getMorale()
{
    return this->morale;
}

void Unit::setCellx(int c)
{
    this->cellx = c;
}

int Unit::getCellx()
{
    return this->cellx;
}

void Unit::setCelly(int c)
{
    this->celly = c;
}

int Unit::getCelly()
{
    return this->celly;
}
