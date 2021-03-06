#include "map.h"

Map::Map(QQuickItem *parent) :
    QQuickPaintedItem(parent)
{
    sizeX =0;sizeY =0;m_cx=0;m_cy=0;
    rercActive = false;
    gameInProgress = false;
    activePlayer =NULL;
    attackTypes.append(AttackType(0,"Меч",":/images/attacks/sword.png",30,1,60));
    attackTypes.append(AttackType(1,"Лук",":/images/attacks/bow.png",30,3,40));
    attackTypes.append(AttackType(2,"Варп огонь",":/images/attacks/dark-missile.png",40,3,50));
    attackTypes.append(AttackType(3,"Варп огонь",":/images/attacks/fireball.png",40,3,50));
    attackTypes.append(AttackType(4,"Посох",":/images/attacks/staff-inc.png",20,1,70));
    attackTypes.append(AttackType(5,"Посох",":/images/attacks/staff-sorcerer.png",20,1,70));
    attackTypes.append(AttackType(6,"Клыки",":/images/attacks/fangs.png",35,1,60));
    attackTypes.append(AttackType(7,"Кинжал",":/images/attacks/dagger.png",15,1,50));
    attackTypes.append(AttackType(8,"Нож",":/images/attacks/dagger-thrown.png",15,2,30));
    passiveAbilities.append(PassiveAbility(0,"Воодушевление",Ally,10,3,Inspiration));
    passiveAbilities.append(PassiveAbility(1,"Слабое воодушевление",Ally,5,2,Inspiration));
    passiveAbilities.append(PassiveAbility(2,"Деморализация",Foe,10,3,Demoralization));
    passiveAbilities.append(PassiveAbility(3,"Слабая деморализация",Foe,5,2,Demoralization));
    passiveAbilities.append(PassiveAbility(4,"Лечение",Ally,10,3,Hill));
    passiveAbilities.append(PassiveAbility(5,"Отравление окружающих",Foe,10,3,Poison));
    this->unittypes.append(UnitType(0,Tzinch_cult,"Культист","мясо", ":/images/units/111.png",
                                    100,2,2,50,5,4,1,10));
    unittypes[0].attacks.append(attackTypes[0]);
    this->unittypes.append(UnitType(1,Tzinch_cult,"Колдун","командир", ":/images/units/112.png",
                                    500,4,3,50,25,44,3,99999));
    unittypes[1].specialfeatures.append("lord");
    unittypes[1].passiveAbilities.append(passiveAbilities[2]);
    unittypes[1].passiveAbilities.append(passiveAbilities[1]);
    unittypes[1].passiveAbilities.append(passiveAbilities[5]);
    unittypes[1].attacks.append(attackTypes[2]);unittypes[1].attacks.append(attackTypes[5]);
    this->unittypes.append(UnitType(2,O_Hereticus,"Инквизитор","командир", ":/images/units/113.png",
                                    500,4,3,50,25,44,3,99999));
    unittypes[2].specialfeatures.append("lord");
    unittypes[2].passiveAbilities.append(passiveAbilities[0]);
    unittypes[2].passiveAbilities.append(passiveAbilities[3]);
    unittypes[2].passiveAbilities.append(passiveAbilities[4]);
    unittypes[2].attacks.append(attackTypes[3]);unittypes[2].attacks.append(attackTypes[4]);
    this->unittypes.append(UnitType(3,O_Hereticus,"Ополченец","легкая пехота", ":/images/units/114.png",
                                    180,2,2,50,5,4,1,15));
    unittypes[3].attacks.append(attackTypes[0]);
    this->unittypes.append(UnitType(4,O_Hereticus,"Лучник","стрелок", ":/images/units/116.png",
                                    100,2,2,50,5,4,3,30));
    unittypes[4].passiveAbilities.append(passiveAbilities[1]);
    unittypes[4].attacks.append(attackTypes[1]);unittypes[4].attacks.append(attackTypes[7]);
    this->unittypes.append(UnitType(5,Tzinch_cult,"мутант","рубака", ":/images/units/115.png",
                                    250,2,3,50,8,6,1,30));
    unittypes[5].passiveAbilities.append(passiveAbilities[3]);
    unittypes[5].attacks.append(attackTypes[6]);unittypes[5].attacks.append(attackTypes[8]);
    /*UnitType(int type_id,Fraction f, QString name, QString descr, QString imS,
         double n_hp, int n_ap, double n_mp, double n_mor, double off,
         double def, double damage, int attackR,int cost)*/

    turnNum = 0;
    connect(this, SIGNAL(xChanged()), this, SLOT(update()));
    connect(this, SIGNAL(yChanged()), this, SLOT(update())); 
}

void Map::paint(QPainter *painter)
{

    if (gameInProgress)
    {

    QPen pen = QPen();
    int startcol = qFloor(m_cx / 64);
    int startrow = qFloor(m_cy / 64);
    int tilecountw = qFloor(width() / 64);
    int tilecounth = qFloor(height() / 64);
    double tx, ty = 0.0f;
    QPixmap tile;
    QString tileSource;
    for (int i =startcol; i < startcol+tilecountw;++i)
    {
        for (int j=startrow;j<startrow+tilecounth;++j)
        {
            tx=64*(i - startcol);
            ty=64*(j - startrow);

            tileSource = QString::number(mapArr[i][j]);
            if(tileCache.contains(tileSource)) {
                tile = tileCache.value(tileSource);
            }
            else {
                tile = QPixmap(":/images/terrains/"+tileSource+".png");
                tileCache.insert(tileSource, tile);
            }
            if (mapArr[i][j]==5)
                painter->drawPixmap(tx, ty, QPixmap(":/images/terrains/1.png"));
            painter->drawPixmap(tx, ty, tile);
            painter->setFont(QFont("Helvetica", 8));
            painter->setPen(QColor(255, 255, 255, 100));
            painter->drawText(QRectF(tx, ty, 64, 64),
                              Qt::AlignCenter,
                              QString::number(i)+":"+QString::number(j));
            painter->setPen(QColor(255, 255, 255, 60));
            painter->drawRect(tx,ty,64,64);
            if (!focus.isEmpty())
                if (occupancy[i][j] == false)
                    if (pow(64*(focus.infocus->getCellx()- startcol) - tx,2) +
                        pow(64*(focus.infocus->getCelly()- startrow) - ty,2) <=
                        pow(64*focus.infocus->getMp(),2))
                    {
                        painter->fillRect(tx,ty,64,64,QColor(0, 200, 0, 95));

                    }
        }
    }
    double sx, sy = 0.0f;
    QPixmap sprite;
    QString spriteSource;
    for (int i = 0; i<units.length();++i)
    {
        if (units[i].getCellx() < startcol && units[i].getCelly() < startrow)
            continue;
        sx = 64*(units[i].getCellx() - startcol);
        sy = 64*(units[i].getCelly() - startrow);
        spriteSource = units[i].type->getImSorce();
        if(tileCache.contains(spriteSource)) {
            sprite = tileCache.value(spriteSource);
        }
        else {
            sprite = QPixmap(spriteSource);
            tileCache.insert(spriteSource, sprite);
        }

        if (!focus.isEmpty())
        {
            if (focus.infocus==&units[i] )
            {
                painter->fillRect(sx,sy,64,64,QColor(255, 255, 0, 100));

            }
            if (focus.infocus->isAttackPossible(&units[i]))
            {
                painter->fillRect(sx,sy,64,64,QColor(255, 0, 0, 100));
                pen.setColor(QColor(255,0,0));
                pen.setWidth(3);
                painter->setPen(pen);
                painter->drawRect(sx+2,sy+2,60,60);
            }
        }
        painter->fillRect(sx+7,sy+55,50.0f*(units[i].type->getNorm_hp()/600)*(units[i].getHp()/(units[i].type->getNorm_hp())),4,QColor(0, 255, 0));
        pen.setColor(QColor(0,255,0));
        pen.setWidth(1);
        painter->setPen(pen);
        painter->drawRect(sx+7,sy+55,50.0f*(units[i].type->getNorm_hp()/600),4);
        painter->fillRect(sx+7,sy+60,units[i].getMorale()/2,4,QColor(0, 255, 255));
        pen.setColor(QColor(0,255,255));
        painter->setPen(pen);
        painter->drawRect(sx+7,sy+60,50,4);
        pen.setColor(units[i].player->color);
        pen.setWidth(2);
        painter->setPen(pen);
        painter->drawLine(sx+50,sy+40,sx+50,sy+55);
        painter->fillRect(sx+50,sy+40,10,5,units[i].player->color);
        painter->drawPixmap(sx, sy, sprite);
    }
    for (int k=0;k<villages.length();++k)
    {
        if (villages[k].player == NULL)
            continue;
        if (villages[k].cellx >= startcol && villages[k].cellx <startcol+tilecountw &&
            villages[k].celly >= startrow && villages[k].celly <startrow+tilecounth)
        {
            pen.setColor(villages[k].player->color);
            pen.setWidth(2);
            painter->setPen(pen);
            painter->drawLine((villages[k].cellx - startcol)*64+50,(villages[k].celly - startrow)*64+40,(villages[k].cellx - startcol)*64+50,(villages[k].celly - startrow)*64+55);
            painter->fillRect((villages[k].cellx - startcol)*64+50,(villages[k].celly - startrow)*64+40,10,5,villages[k].player->color);
        }
    }
    }
}

void Map::mouseClicked(int x, int y, Qt::MouseButtons btn)
{
    int startcol = qFloor(m_cx / 64);
    int startrow = qFloor(m_cy / 64);
    int nx = qFloor(x / 64);
    int ny = qFloor(y / 64);
    if (btn == Qt::LeftButton)
    {
        Unit *target = unitOnCell(nx+startcol,ny+startrow);
        if (target !=NULL)
        {
            if (target->player == activePlayer)
                focus.setInfocus(target);
        }
        else
            focus.clear();
    } else if (btn == Qt::RightButton && !focus.isEmpty())
    {
        if (!occupancy[nx+startcol][ny+startrow])
        {
            if (focus.infocus->isMovementPossible(mapArr, occupancy, nx+startcol, ny + startrow))
            {
                focus.infocus->move(mapArr, occupancy, nx+startcol, ny + startrow);
                for (int k=0;k<villages.length();++k)
                {
                    if (villages[k].cellx == focus.infocus->getCellx() &&
                        villages[k].celly == focus.infocus->getCelly())
                    {
                        villages[k].player = activePlayer;
                        activePlayer->villages+=1;
                        k = villages.length();
                    }
                }
            }
        } else {
            if (players.length()==1)
                emit victory();
        }
    }
    this->update();

}

void Map::newturn()
{
    ++turnNum;
    passiveAbilitiesAction();
    activePlayer->cash += activePlayer->baseIncome + activePlayer->villages * 5 - activePlayer->units;
    for (int i=0;i<units.length();++i)
    {
        if (units[i].player == activePlayer)
        {
            units[i].setAp(units[i].type->getNorm_ap());
            units[i].setMp(units[i].type->getNorm_mp());
            if (units[i].getHp() < units[i].type->getNorm_hp())
                units[i].setHp(units[i].getHp()+qCeil(units[i].type->getNorm_hp()/20));
            if (units[i].getHp() > units[i].type->getNorm_hp())
                units[i].setHp(units[i].type->getNorm_hp());
            if (units[i].getMorale()>50)
                units[i].setMorale(units[i].getMorale()-2);
            else
                if (units[i].getMorale()<50)
                units[i].setMorale(units[i].getMorale()+2);
        }

    }
    for (int i=0;i<players.length();++i)
    {
        if (players[i].getid() == activePlayer->getid())
        {
            activePlayer = i < (players.length()-1) ? &players[i+1] : &players[0];
            i = players.length()+1;
            focus.clear();
            activePlayer->villages=0;
            for (int k=0;k<villages.length();++k)
            {
                if (villages[k].player==activePlayer)
                    activePlayer->villages+=1;
            }
            activePlayer->units = 0;
            for (int k=0;k<units.length();++k)
            {
                if (units[k].player == activePlayer)
                {
                    units[k].player->units+=1;
                }

            }
        }
    }
    if (activePlayer->person == Comp)
    {
        emit aiturn();
        if (players.length()>1)
            newturn();
    }

    this->update();

}

void Map::distributePlayers()
{
    activePlayer = &players[0];
    bool pl = true;
    for (int i=0;i<sizeX;++i)
    {
        for (int j=0;j< sizeY;++j)
        {
            if (mapArr[i][j] == 3 && pl)
            {
                for (int k=0;k<unittypes.length();++k)
                {
                    if (unittypes[k].fraction == activePlayer->fraction && unittypes[k].specialfeatures.contains("lord"))
                    {
                        this->units.append(Unit(&unittypes[k],activePlayer,i,j));
                        occupancy[i][j] = true;
                        k = unittypes.length();
                        for (int p=0; p<players.length();++p)
                        {
                            if (&players[p] == activePlayer)
                            {

                                if (p == players.length()-1)
                                    pl = false;
                                else
                                    activePlayer = &players[p+1];
                                p = players.length();
                            }
                        }
                    }
                }
            }
        }
    }
    activePlayer = &players[0];
}

void Map::readMap(QString filename)
{
    QFile file1(filename);
    file1.open(QIODevice::ReadOnly);
    QByteArray a = file1.readAll();
    QString astr = a;
    QStringList s = astr.split(',');
    bool ok = true;
    sizeX = s.at(0).toInt(&ok,10);
    sizeY = s.at(1).toInt(&ok,10);
    int **arr = new int *[s.at(0).toInt(&ok,10)];
    occupancy = new bool *[s.at(1).toInt(&ok,10)];
    for (int i =0; i< s.at(0).toInt(&ok,10); ++i)
    {
        arr[i] = new int[s.at(1).toInt(&ok,10)];
        occupancy[i] = new bool[s.at(1).toInt(&ok,10)];
    }
    for (int i=0;i<sizeX;++i)
    {
        for (int j=0;j< sizeY;++j)
        {
            arr[i][j] = s.at(2 + j*sizeX + i).toInt(&ok,10);
            occupancy[i][j] = false;
            if (arr[i][j] == 5)
            {
                villages.append(Village(i,j));
            }
        }
    }
    mapArr = arr;
    file1.close();

}

void Map::clear()
{
    for (int i=0;i<sizeX;++i)
    {
        delete []mapArr[i];
        delete []occupancy[i];
    }
    units.clear();
    players.clear();
    sizeX =0;sizeY =0;m_cx=0;m_cy=0;turnNum = 0;
    activePlayer =NULL;
    focus.clear();
}

QList <QPoint> Map::path(QPoint cell1,QPoint cell2)
{
    QList <QPoint> path;
    QPoint p1 = QPoint(cell1.x()*64+32,cell1.y()*64+32);
    QPoint p2 = QPoint(cell2.x()*64+32,cell2.y()*64+32);
    int x1 = cell1.x() < cell2.x() ? cell1.x() : cell2.x();
    int x2 = cell1.x() > cell2.x() ? cell1.x() : cell2.x();
    int y1 = cell1.y() < cell2.y() ? cell1.y() : cell2.y();
    int y2 = cell1.y() > cell2.y() ? cell1.y() : cell2.y();
    for (int x=x1*64;x<x2*64;x+=8)
    {
        int y=(int)((x-p1.x())/((double)(p2.x()-p1.x()))*(p2.y()-p1.y())+p1.y());
        if (!path.contains(QPoint(x/64,y/64)))
            path.append(QPoint(x/64,y/64));
    }
    for (int y=y1*64;y<y2*64;y+=8)
    {
        int x=(int)((y-p1.y())/((double)(p2.y()-p1.y()))*(p2.x()-p1.x())+p1.x());
        if (!path.contains(QPoint(x/64,y/64)))
            path.append(QPoint(x/64,y/64));
    }
    return path;
}

void Map::aiVictory()
{

    emit defeat();
}

double Map::distance(int cellx1, int celly1, int cellx2, int celly2)
{
    return sqrt(pow(cellx1 - cellx2,2) + pow(celly1 - celly2,2));
}

int ** Map::getMapArr()
{
    return mapArr;
}

void Map::setMapArr(int **m)
{
    mapArr = m;
    emit mapArrChanged();
}

int Map::getSizeX()
{
    return sizeX;
}

void Map::setSizeX(const int &sx)
{
    sizeX = sx;
    emit sizeXChanged();
}

int Map::getSizeY()
{
    return sizeY;
}

void Map::setSizeY(const int &sy)
{
    sizeY = sy;
    emit sizeYChanged();
}

QList<Unit> Map::unitsList()
{
    return units;
}

QList<UnitType> Map::unittypesList()
{
    return unittypes;
}

void Map::start()
{

}

bool Map::isCellEmpty(int x, int y)
{
    return !occupancy[qFloor(m_cx / 64)+qFloor(x / 64)][qFloor(m_cy / 64)+qFloor(y / 64)];
}

double Map::cx() const
{
    return m_cx;
}

double Map::cy() const
{
    return m_cy;
}

void Map::setCx(double cx)
{
    if (m_cx == cx)
        return;

    m_cx = cx;
    emit cxChanged(cx);
}

void Map::setCy(double cy)
{
    if (m_cy == cy)
        return;

    m_cy = cy;
    emit cyChanged(cy);
}

QString Map::getFocus()
{
    return focus.infocus->type->getName();
}

bool Map::isFocusEmpty()
{
    return this->focus.isEmpty();
}

bool Map::isRercActive()
{
    return this->rercActive;
}

void Map::setRercActive(bool r)
{
    rercActive = r;
}

void Map::setLastxy(double ls,double ly)
{
    lastx = ls;
    lasty = ly;
}

bool Map::isRecrPoss(int x, int y)
{
    int startcol = qFloor(m_cx / 64);
    int startrow = qFloor(m_cy / 64);
    int nx = qFloor(x / 64);
    int ny = qFloor(y / 64);
    if (mapArr[nx+startcol][ny+startrow]==4 && !occupancy[nx+startcol][ny+startrow])
    {
        for (int i=0;i<units.length();++i)
        {
            if (units[i].player == activePlayer && units[i].type->specialfeatures.contains("lord"))
            {
                if (qCeil(sqrt(pow(units[i].getCellx() - nx-startcol,2) +
                               pow(units[i].getCelly() - ny-startrow,2)))<=2)
                return true;
            }
        }
    }
    return false;
}

bool Map::isAtckPoss(int x, int y)
{
    int startcol = qFloor(m_cx / 64);
    int startrow = qFloor(m_cy / 64);
    int nx = qFloor(x / 64);
    int ny = qFloor(y / 64);
    Unit *target = unitOnCell(nx+startcol,ny+startrow);
    if (!focus.isEmpty()&&target!=NULL)
        return focus.infocus->isAttackPossible(target);
    return false;
}

Unit * Map::unitOnCell(int cellx, int celly)
{
    for (int i=0; i < units.length();++i)
    {
        if (units[i].getCellx() == cellx && units[i].getCelly() == celly)
            return &units[i];
    }
    return NULL;
}

Village * Map::villageUnCell(QPoint cell)
{
    for (int i=0; i < villages.length();++i)
    {
        if (villages[i].cellx == cell.x() && villages[i].celly == cell.y())
            return &villages[i];
    }
    return NULL;
}

QList <QPoint> Map::sortByDistance(QList <QPoint> l, QPoint p)
{
    for (int i=0;i<l.length();++i)
        for(int j=i;j>0 && distance(l[j-1].x(),l[j-1].y(),p.x(),p.y())
            >distance(l[j].x(),l[j].y(),p.x(),p.y());--j)
            l.swap(j-1,j);
    return l;
}

void Map::passiveAbilitiesAction()
{
    for (int i=0;i<units.length();++i)
        if (units[i].player == activePlayer && units[i].type->passiveAbilities.length()>0)
        {
            for (int j=0;j<units[i].type->passiveAbilities.length();++j)
            {
                for(int k=0;k<units.length();++k)
                    if (distance(units[i].getCellx(),units[i].getCelly(),units[k].getCellx(),units[k].getCelly())
                            <=units[i].type->passiveAbilities[j].abilityRadius)
                        if (units[i].type->passiveAbilities[j].side==Foe && units[k].player!=units[i].player)
                        {
                            if (units[i].type->passiveAbilities[j].abilityType==Demoralization)
                            {
                                if(units[k].getMorale()>25)
                                    units[k].setMorale(units[k].getMorale()-units[i].type->passiveAbilities[j].value);
                            } else
                            if (units[i].type->passiveAbilities[j].abilityType==Poison)
                                if(units[k].getHp()*100/units[k].type->getNorm_hp()>25)
                                    units[k].setHp(units[k].getHp()-units[i].type->passiveAbilities[j].value);
                        } else
                            if (units[i].type->passiveAbilities[j].side==Ally && units[k].player==units[i].player)
                            {
                                if (units[i].type->passiveAbilities[j].abilityType==Inspiration)
                                {
                                    if(units[k].getMorale()<75)
                                        units[k].setMorale(units[k].getMorale()+units[i].type->passiveAbilities[j].value);
                                } else
                                if (units[i].type->passiveAbilities[j].abilityType==Hill)
                                    if(units[k].getHp()*100/units[k].type->getNorm_hp()<75)
                                        units[k].setHp(units[k].getHp()+units[i].type->passiveAbilities[j].value);
                            }

            }
        }
}


