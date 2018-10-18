#include "ai.h"

AI::AI()
{
    map = NULL;
}

void AI::turn()
{
    mediumSpeed=0;
    m_units.clear();
    enemyunits.clear();
    fractionUnitTypes.clear();
    targetPlaces.clear();targetVillages.clear();targetEnemies.clear();
    for (int i=0;i<map->units.length();++i)
        if (map->units[i].player==map->activePlayer)
        {
            m_units.append(map->units[i]);
            mediumSpeed+=map->units[i].type->getNorm_mp();
        }
        else
            enemyunits.append(map->units[i]);
    for (int i=0;i<map->unittypes.length();++i)
        if (map->unittypes[i].fraction==map->activePlayer->fraction)
            fractionUnitTypes.append(map->unittypes[i]);
    mediumSpeed/=m_units.length();
    Unit *lord = getLord();
    if (map->getMapArr()[lord->getCellx()][lord->getCelly()]==3)
        if (isRecruitmentNeeded())
            recruitment();
    movements();m_units.clear();
    for (int i=0;i<map->units.length();++i)
        if (map->units[i].player==map->activePlayer)
            m_units.append(map->units[i]);
    attacks();
}

void AI::setMap(Map *m)
{
    map = m;
}

bool AI::isRecruitmentNeeded()
{
    if (m_units.length()<=4 || map->activePlayer->villages<=3)
        return true;
    if ((map->activePlayer->cash>150  && (map->activePlayer->baseIncome+map->activePlayer->villages*5 - map->activePlayer->units > 10))
            || enemiesNearby(getLord(),6) > 1)
        return true;
    return false;
}

void AI::recruitment()
{
    QList <UnitType> fast=fastUnitTypes();
    QList <UnitType> strong=strongUnitTypes();
    QList <UnitType> cheap=cheapUnitTypes();
    int plan=0;
    plan = map->activePlayer->cash/30 - m_units.length()/10 +enemiesNearby(getLord(),6);
    if (plan > recruitmentPlace().length())
        plan = recruitmentPlace().length();
    for (int i=0;i<fast.length();++i)
    {

        if (map->activePlayer->cash >= (plan/2)*fast[i].cost)
        {
            QList <QPoint> places = recruitmentPlace();
            for (int j=0;j < qCeil(plan/2);++j)
            {
                map->units.append(Unit(&map->unittypes[map->unittypes.indexOf(fast[i])],map->activePlayer,places[j].x(),places[j].y()));
                map->occupancy[places[j].x()][places[j].y()]=true;
                map->activePlayer->cash-=fast[i].cost;
                m_units.append(map->units.last());
            }
            plan/=2;
            i = fast.length();
        }
    }
    for (int i=0;i<strong.length();++i)
    {
        if (map->activePlayer->cash >= (plan/2)*strong[i].cost)
        {
            QList <QPoint> places = recruitmentPlace();
            for (int j=0;j < plan/2;++j)
            {
                map->units.append(Unit(&map->unittypes[map->unittypes.indexOf(strong[i])],map->activePlayer,places[j].x(),places[j].y()));
                map->occupancy[places[j].x()][places[j].y()]=true;
                map->activePlayer->cash-=strong[i].cost;
                m_units.append(map->units.last());
            }
            plan=0;
            i = strong.length();
        }
    }
    if (plan!=0)
    {
        while(map->activePlayer->cash>=cheap[0].cost && plan!=0)
        {
            QList <QPoint> places = recruitmentPlace();
            map->units.append(Unit(&map->unittypes[map->unittypes.indexOf(cheap[0])],map->activePlayer,places[0].x(),places[0].y()));
            map->occupancy[places[0].x()][places[0].y()]=true;
            map->activePlayer->cash-=cheap[0].cost;
            m_units.append(map->units.last());
            --plan;
        }
    }
}

void AI::movements()
{
    QList<QPoint> vils;
    QList<QPoint> enems;
    for (int i=0;i<map->villages.length();++i)
    {
        if (map->villages[i].player!=map->activePlayer)
            vils.append(QPoint(map->villages[i].cellx,map->villages[i].celly));
    }
    for (int i=0;i<enemyunits.length();++i)
    {
        if (friendsNearby(&map->units[map->units.indexOf(enemyunits[i])],2)<8)
            enems.append(QPoint(enemyunits[i].getCellx(),enemyunits[i].getCelly()));
    }
    for (int j=0;j< m_units.length();++j)
    {
        if (m_units[j].type->specialfeatures.contains("lord"))
            continue;
        vils = sortByDistance(vils,QPoint(m_units[j].getCellx(),m_units[j].getCelly()));
        if ((map->activePlayer->villages<=2
             || map->activePlayer->cash<20
             || map->activePlayer->baseIncome+map->activePlayer->villages*5 - map->activePlayer->units < 5
             || targetVillages.length() < m_units.length()/8+1)
             && vils.length()>0 && m_units[j].type->getNorm_mp()>=mediumSpeed)
        {
            for (int i=0;i<vils.length();++i)
                if (!targetPlaces.contains(QPoint(vils[i].x(),vils[i].y())))
                    if (!map->occupancy[vils[i].x()][vils[i].y()])
                    {
                        targetPlaces.append(QPoint(vils[i].x(),vils[i].y()));
                        targetVillages.append(QPoint(vils[i].x(),vils[i].y()));
                        moveInDirection(&map->units[map->units.indexOf(m_units[j])],QPoint(vils[i].x(),vils[i].y()));
                        i=vils.length();
                    }
        } else
        {
            enems=sortByDistance(enems,QPoint(m_units[j].getCellx(),m_units[j].getCelly()));
            for (int i=0;i<enems.length();++i)
            {
                Unit u=*map->unitOnCell(enems[i].x(),enems[i].y());
                QList <QPoint> t = freeCellsNearby(enems[i].x(),enems[i].y(),m_units[j].type->getAttackRadius());

                t = sortByDistance(t,QPoint(u.getCellx(),u.getCelly()));

                if (!targetEnemies.contains(map->units.indexOf(u)))
                {
                    if (t.length()>0)
                    {
                        targetPlaces.append(t[0]);
                        targetEnemies[map->units.indexOf(u)]=1;
                        moveInDirection(&map->units[map->units.indexOf(m_units[j])],t[0]);
                        i = enems.length();
                    }
                }
                else if (targetEnemies[map->units.indexOf(u)]<5)
                {
                    if (t.length()>0)
                    {
                        targetPlaces.append(t[0]);
                        targetEnemies[map->units.indexOf(u)]+=1;
                        moveInDirection(&map->units[map->units.indexOf(m_units[j])],t[0]);
                        i = enems.length();
                    }
                }
            }
        }
    }
}

void AI::attacks()
{
    for (int i=0;i<m_units.length();++i)
    {
        QList<QPoint> enems;
        for (int i=0;i<enemyunits.length();++i)
        {
            if (friendsNearby(&map->units[map->units.indexOf(enemyunits[i])],2)<8)
                enems.append(QPoint(enemyunits[i].getCellx(),enemyunits[i].getCelly()));
        }
        enems=sortByDistance(enems,QPoint(m_units[i].getCellx(),m_units[i].getCelly()));
        Unit *target = map->unitOnCell(enems[0].x(),enems[0].y());
        if (m_units[i].isAttackPossible(target))
        {
            if (map->units[map->units.indexOf(m_units[i])].attack(target))
            {
                map->occupancy[enems[0].x()][enems[0].y()]=false;
                if (target->type->specialfeatures.contains("lord"))
                {
                    Player p = *target->player;
                    map->units.removeOne(*target);
                    enemyunits.removeOne(*target);
                    map->players.removeOne(p);
                    if (map->players.length()==1)
                        map->aiVictory();
                    return;
                }
                else
                {
                    map->units.removeOne(*target);
                    enemyunits.removeOne(*target);
                }
            }
        }
    }
}

QList <UnitType> AI::strongUnitTypes()
{
    QList <UnitType> strongUnitTypes;
    for (int i=0;i<fractionUnitTypes.length();++i)
    {
        if (!fractionUnitTypes[i].specialfeatures.contains("lord"))
            strongUnitTypes.append(fractionUnitTypes[i]);
    }
    for (int i=0;i<strongUnitTypes.length();++i)
        for(int j=i;j>0 && strongUnitTypes[j-1].getDamage()*(strongUnitTypes[j-1].getAttackRadius()/3+1)
            <strongUnitTypes[j].getDamage()*(strongUnitTypes[j].getAttackRadius()+1);--j)
            strongUnitTypes.swap(j-1,j);
    return strongUnitTypes;
}

QList <UnitType> AI::fastUnitTypes()
{
    QList <UnitType> fastUnitTypes;
    for (int i=0;i<fractionUnitTypes.length();++i)
        if (!fractionUnitTypes[i].specialfeatures.contains("lord"))
            fastUnitTypes.append(fractionUnitTypes[i]);
    for (int i=0;i<fastUnitTypes.length();++i)
        for(int j=i;j>0 && fastUnitTypes[j-1].getNorm_mp()<fastUnitTypes[j].getNorm_mp();--j)
            fastUnitTypes.swap(j-1,j);
    return fastUnitTypes;
}

QList <UnitType> AI::cheapUnitTypes()
{
    QList <UnitType> cheapUnitTypes;
    for (int i=0;i<fractionUnitTypes.length();++i)
        if (!fractionUnitTypes[i].specialfeatures.contains("lord"))
            cheapUnitTypes.append(fractionUnitTypes[i]);
    for (int i=0;i<cheapUnitTypes.length();++i)
        for(int j=i;j>0 && cheapUnitTypes[j-1].cost>cheapUnitTypes[j].cost;--j)
            cheapUnitTypes.swap(j-1,j);
    return cheapUnitTypes;
}

Unit *AI::getLord()
{
    for (int i=0;i<m_units.length();++i)
    {
        if (m_units[i].type->specialfeatures.contains("lord"))
            return &map->units[map->units.indexOf(m_units[i])];
    }
}

QList <QPoint> AI::recruitmentPlace()
{
    Unit *lord = getLord();
    QList <QPoint> places;
    for (int i=lord->getCellx()-1;i<=lord->getCellx()+1;++i)
        for (int j=lord->getCelly()-1;j<=lord->getCelly()+1;++j)
            if (!map->occupancy[i][j])
                places.append(QPoint(i,j));
    return places;
}

QList <QPoint> AI::freeCellsNearby(int cellx,int celly,int r)
{
    QList <QPoint> places;
    for (int i=cellx-r >=0 ? cellx-r:0;i<=(cellx+r <=map->getSizeX()-1 ? cellx+r:map->getSizeX()-1);++i)
        for (int j=celly-r >=0 ? celly-r:0;j<=(celly+r <=map->getSizeY()-1 ? celly+r:map->getSizeY()-1);++j)
            if (!map->occupancy[i][j])
                places.append(QPoint(i,j));
    return places;
}

int AI::enemiesNearby(Unit *u,int r)
{
    int en=0;
    for (int i=0;i<enemyunits.length();++i)
        if (qCeil(map->distance(u->getCellx(),u->getCelly(),enemyunits[i].getCellx(),enemyunits[i].getCelly()))
                <=r)
            ++en;
    return en;
}

int AI::friendsNearby(Unit *u,int r)
{
    int fr=0;
    for (int i=0;i<m_units.length();++i)
        if (qCeil(map->distance(u->getCellx(),u->getCelly(),m_units[i].getCellx(),m_units[i].getCelly()))
                <=r)
            ++fr;
    return fr;
}



void AI::moveInDirection(Unit *u, QPoint p)
{

    QPoint tempTarget;
    if (map->distance(p.x(),p.y(),u->getCellx(),u->getCelly())<=u->getMp())
    {tempTarget=p;}
    else
    {
        //qDebug()<<p<<QPoint(u->getCellx(),u->getCelly());
        QList<QPoint> pth = map->path(p,QPoint(u->getCellx(),u->getCelly()));
        //qDebug()<<pth<<u->getCellx()<<u->getCelly();
        pth = sortByDistance(pth,QPoint(u->getCellx(),u->getCelly()));
        for (int i=pth.length()-1;i>=0;--i)
        {
            int r =qFloor(map->distance(pth[i].x(),pth[i].y(),u->getCellx(),u->getCelly()));
            if (r<=u->getMp())
            {
                if (!map->occupancy[pth[i].x()][pth[i].y()])
                {
                    tempTarget = pth[i];
                }
                else
                {
                    int k=1;
                    while (tempTarget.isNull())
                    {
                        QList<QPoint> places = freeCellsNearby(pth[i].x(),pth[i].y(),k);
                        places=sortByDistance(places,pth[i]);
                        if (!places.isEmpty())
                            tempTarget = places[0];
                        else
                            ++k;
                    }
                }
                i=-1;
            }
        }
    }
    for (int k=0;k<map->villages.length();++k)
    {
        if (map->villages[k].cellx == tempTarget.x() &&
                map->villages[k].celly == tempTarget.y())
        {
            map->villages[k].player = map->activePlayer;
            map->activePlayer->villages+=1;
            k = map->villages.length();
        }
    }
    u->move(map->getMapArr(),map->occupancy,tempTarget.x(),tempTarget.y());
    //qDebug()<<u1->getCellx()<<u1->getCelly()<<u->getCellx()<<u->getCelly();
}

QList <QPoint> AI::sortByDistance(QList <QPoint> l, QPoint p)
{
    for (int i=0;i<l.length();++i)
        for(int j=i;j>0 && map->distance(l[j-1].x(),l[j-1].y(),p.x(),p.y())
            >map->distance(l[j].x(),l[j].y(),p.x(),p.y());--j)
            l.swap(j-1,j);
    return l;
}
