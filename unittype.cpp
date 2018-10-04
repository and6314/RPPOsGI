#include "unittype.h"

UnitType::UnitType()
{

}

UnitType::UnitType(int type_id,Fraction f, QString name, QString descr, QString imS,
         double n_hp, int n_ap, double n_mp, double n_mor, double off,
         double def, double damage, int attackR,int cost)
{
    this->id = type_id;
    this->name = name;
    this->description = descr;
    this->imSource = imS;
    this->norm_hp = n_hp;
    this->norm_ap = n_ap;
    this->norm_mp = n_mp;
    this->norm_morale = n_mor;
    this->off = off;
    this->def = def;
    this->damage = damage;
    this->fraction =f;
    this->attackRadius = attackR;
    this->cost = cost;
}

void UnitType::setName(QString n)
{
    this->name = n;
}

QString UnitType::getName()
{
    return this->name;
}

void UnitType::setDescr(QString d)
{
    this->description = d;
}

QString UnitType::getDescription()
{
    return this->description;
}

void UnitType::setImSource(QString s)
{
    this->imSource = s;
}

QString UnitType::getImSorce()
{
    return this->imSource;
}

int UnitType::getid()
{
    return this->id;
}

void UnitType::setNorm_hp(double n)
{
    this->norm_hp = n;
}

double UnitType::getNorm_hp()
{
    return this->norm_hp;
}

void UnitType::setNorm_mp(double n)
{
    this->norm_mp  =  n;
}

double UnitType::getNorm_mp()
{
    return this->norm_mp;
}

void UnitType::setNorm_ap(int n)
{
    this->norm_ap = n;
}

int UnitType::getNorm_ap()
{
    return this->norm_ap;
}

double UnitType::getOff()
{
    return this->off;
}

void UnitType::setOff(double o)
{
    this->off = o;
}

double UnitType::getDef()
{
    return this->def;
}

void UnitType::setDef(int d)
{
    this->def = d;
}

double UnitType::getDamage()
{
    return this->damage;
}

void UnitType::setDamage(int d)
{
    this->damage = d;
}

void UnitType::setNorm_morale(double n)
{
    this->norm_morale = n;
}

double UnitType::getNorm_morale()
{
    return this->norm_morale;
}

int UnitType::getAttackRadius()
{
    return attackRadius;
}
