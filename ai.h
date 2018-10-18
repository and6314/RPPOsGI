#ifndef AI_H
#define AI_H

#include <map.h>
#include <QPoint>
#include <qmath.h>

class AI
{

public:
    AI();
    void setMap(Map *m);

public slots:
    void turn();

private:
    bool isRecruitmentNeeded();
    void recruitment();
    void movements();
    void attacks();
    QList <UnitType> strongUnitTypes();
    QList <UnitType> fastUnitTypes();
    QList <UnitType> cheapUnitTypes();
    Unit *getLord();
    QList <QPoint> recruitmentPlace();
    QList <QPoint> freeCellsNearby(int cellx,int celly,int r);
    int enemiesNearby(Unit *u,int r);
    int friendsNearby(Unit *u,int r);
    void moveInDirection(Unit *u, QPoint p);

    QList <Unit> m_units;
    QList <Unit> enemyunits;
    QList <UnitType> fractionUnitTypes;
    int mediumSpeed;
    QMap <int, int> targetEnemies;
    QList <QPoint> targetPlaces;
    QList <QPoint> targetVillages;
    Map *map;
};

#endif // AI_H
