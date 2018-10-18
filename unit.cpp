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

bool Unit::operator==(const Unit& arg)
{
    if (this->cellx == arg.cellx && this->celly == arg.celly)
        return true;
    return false;
}

bool Unit::operator<(const Unit arg)
{
    if (this->cellx != arg.cellx && this->celly != arg.celly)
        return true;
    return false;
}

bool Unit::operator>(const Unit arg)
{
    if (this->cellx != arg.cellx && this->celly != arg.celly)
        return true;
    return false;
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

bool Unit::attack(Unit *target)
{
    this->setAp(this->getAp()-1);
    QList <AttackType> availableAttacks;
    for (int i=0;i<type->attacks.length();++i)
        if (isAttackPossible(target,type->attacks[i]))
            availableAttacks.append(type->attacks[i]);
    if (qrand()&101 >= availableAttacks[0].chance)
        target->setHp(target->getHp()-availableAttacks[0].damage);
    if (target->getHp()<=0)
        return true;
    return false;
}

bool Unit::attack(Unit *target, AttackType atc)
{
    this->setAp(this->getAp()-1);
    if (qrand()&101 >= atc.chance)
        target->setHp(target->getHp()-atc.damage);
    if (target->getHp()<=0)
        return true;
    return false;
}

bool Unit::isAttackPossible(Unit *target)
{
    if (target!=NULL)
    {
        if (target->player!=this->player && this->getAp()>0)
        {
            if (this->type->getAttackRadius()==1)
                if (target->getCellx() >= this->getCellx()-1
                        && target->getCellx() <= this->getCellx()+1
                        && target->getCelly() >= this->getCelly()-1
                        && target->getCelly() <= this->getCelly()+1)
                    return true;
            if ((qCeil(sqrt(pow((this->getCellx()- target->getCellx()) ,2) +
                            pow((this->getCelly()) - target->getCelly(),2)))
                 <=this->type->getAttackRadius()))
                return true;
        }
    }
    return false;
}

bool Unit::isAttackPossible(Unit *target,AttackType atc)
{
    if (target!=NULL)
    {
        if (target->player!=this->player && this->getAp()>0)
        {
            if (atc.attackRadius==1)
                if (target->getCellx() >= this->getCellx()-1
                        && target->getCellx() <= this->getCellx()+1
                        && target->getCelly() >= this->getCelly()-1
                        && target->getCelly() <= this->getCelly()+1)
                    return true;
            if ((qCeil(sqrt(pow((this->getCellx()- target->getCellx()) ,2) +
                            pow((this->getCelly()) - target->getCelly(),2)))
                 <=atc.attackRadius))
                return true;
        }
    }
    return false;
}

bool Unit::isMovementPossible(int **map, bool **occupancy, int cellx, int celly)
{
    if (!occupancy[cellx][celly])
    {
        if (pow(this->getCellx()- cellx,2) +
            pow(this->getCelly()- celly,2) <=
            pow(this->getMp(),2))
            return true;
    }
    return false;
}

void Unit::move(int **map, bool **occupancy, int cellx, int celly)
{
    occupancy[cellx][celly] = true;
    occupancy[this->cellx][this->celly] = false;
    setMp(this->mp - qCeil(sqrt(pow(this->cellx- cellx ,2) +
                                pow(this->celly- celly,2))));
    this->cellx = cellx;
    this->celly = celly;
}
