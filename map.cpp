#include "map.h"

Map::Map(QQuickItem *parent) :
    QQuickPaintedItem(parent)
{
    sizeX =0;sizeY =0;m_cx=0;m_cy=0;
    rercActive = false;
    players.append(Player(0,Tzinch_cult,QColor(255,0,0)));
    players.append(Player(1,O_Hereticus,QColor(0,0,255)));
    activePlayer = &players[0];
    this->unittypes.append(UnitType(0,Tzinch_cult,"Культист","мясо", ":/111.png",
                                    50,2,2,50,5,4,20,1,40));
    this->unittypes.append(UnitType(1,Tzinch_cult,"Колдун","командир", ":/112.png",
                                    500,4,3,500,25,44,80,3,99999));
    unittypes[1].specialfeatures.append("lord");
    this->unittypes.append(UnitType(2,O_Hereticus,"Инквизитор","командир", ":/113.png",
                                    500,4,3,500,25,44,80,3,99999));
    unittypes[2].specialfeatures.append("lord");
    this->unittypes.append(UnitType(3,O_Hereticus,"Ополченец","легкая пехота", ":/114.png",
                                    120,2,2,50,5,4,20,1,60));
    this->unittypes.append(UnitType(4,O_Hereticus,"Лучник","стрелок", ":/116.png",
                                    50,2,2,50,5,4,20,4,80));
    this->unittypes.append(UnitType(5,Tzinch_cult,"мутант","рубака", ":/115.png",
                                    150,2,3,50,8,6,20,1,80));
    QFile file1("E:/QtProjects/untitled13/map3.txt");
    /*UnitType(int type_id,Fraction f, QString name, QString descr, QString imS,
         double n_hp, int n_ap, double n_mp, double n_mor, double off,
         double def, double damage, int attackR,int cost)*/

    file1.open(QIODevice::ReadOnly);
    QByteArray a = file1.readAll();
    QString astr = a;
    QStringList s = astr.split(',');
    bool ok,pl = true;
    sizeX = s.at(0).toInt(&ok,10);
    sizeY = s.at(1).toInt(&ok,10);
    int **arr = new int *[s.at(0).toInt(&ok,10)];
    occupancy = new bool *[s.at(0).toInt(&ok,10)];
    for (int i =0; i< s.at(0).toInt(&ok,10); ++i)
    {
        arr[i] = new int[s.at(1).toInt(&ok,10)];
        occupancy[i] = new bool[s.at(1).toInt(&ok,10)];
    }
    for (int i=0;i<sizeX;++i)
    {
        for (int j=0;j< sizeY;++j)
        {
            arr[i][j] = s.at(2 + i*sizeX + j).toInt(&ok,10);
            occupancy[i][j] = false;
            if (arr[i][j] == 5)
            {
                villages.append(Village(i,j));
            }
            else if (arr[i][j] == 3 && pl)
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
    mapArr = arr;
    file1.close();
    activePlayer = &players[0];
    connect(this, SIGNAL(xChanged()), this, SLOT(update()));
    connect(this, SIGNAL(yChanged()), this, SLOT(update())); 
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

void Map::mouseClicked(int x, int y, Qt::MouseButtons btn)
{
    int startcol = qFloor(m_cx / 64);
    int startrow = qFloor(m_cy / 64);
    int nx = qFloor(x / 64);
    int ny = qFloor(y / 64);
    bool f=false;
    if (btn == Qt::LeftButton /*&& focus.isEmpty()*/)
    {
        for (int i = 0; i < units.length();++i)
        {

            int tx=64*(units[i].getCellx() - startcol);
            int ty=64*(units[i].getCelly() - startrow);
            if ((x > tx && x < tx+64) &&
                    (y > ty && y < ty+64))
            {
                f = true;
                if (activePlayer == units[i].player)
                    focus.setInfocus(&units[i]);
                //qDebug()<<focus.infocus->type->getName()<<focus.infocus->getCellx()<<focus.infocus->getCelly();

            }
            if (!f)
                focus.clear();

        }
    } else if (btn == Qt::RightButton && !focus.isEmpty())
    {

        if (!occupancy[nx+startcol][ny+startrow])
        {
            if (pow((focus.infocus->getCellx()- startcol- nx) ,2) +
                pow((focus.infocus->getCelly()- startrow) - ny,2) <=
                pow(focus.infocus->getMp(),2))
            {
                occupancy[nx+startcol][ny+startrow] = true;
                occupancy[focus.infocus->getCellx()][focus.infocus->getCelly()]=false;
                focus.infocus->setMp(focus.infocus->getMp()
                                     - qCeil(sqrt(pow((focus.infocus->getCellx()- startcol- nx) ,2) +
                                                  pow((focus.infocus->getCelly()- startrow) - ny,2))));
                focus.infocus->setCellx(nx+startcol);
                focus.infocus->setCelly(ny+startrow);
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
            if (focus.infocus->getAp()>0)
            for (int i=0; i < units.length();++i)
            {
                if (units[i].getCellx() == nx+startcol && units[i].getCelly() == ny+startrow)
                {
                    if (units[i].player != focus.infocus->player)
                    {
                        if ((qCeil(sqrt(pow((focus.infocus->getCellx()- units[i].getCellx()) ,2) +
                                        pow((focus.infocus->getCelly()) - units[i].getCelly(),2)))
                             <=focus.infocus->type->getAttackRadius()))
                        {
                            qDebug()<<"bam"<<nx+startcol<<ny+startrow;
                            focus.infocus->setAp(focus.infocus->getAp()-1);
                            units[i].setHp(units[i].getHp()-focus.infocus->type->getDamage());
                            if (units[i].getHp()<=0)
                            {
                                occupancy[units[i].getCellx()][units[i].getCelly()] = false;
                                units.removeAt(i);
                            }
                        }
                    }
                    i = units.length()+100;
                }
            }
        }
    }
    this->update();

}

void Map::newturn()
{
    activePlayer->cash += activePlayer->villages * 5 - activePlayer->units;
    for (int i=0;i<units.length();++i)
    {
        if (units[i].player == activePlayer)
        {
            units[i].setAp(units[i].type->getNorm_ap());
            units[i].setMp(units[i].type->getNorm_mp());
            if (units[i].getHp() < units[i].type->getNorm_hp())
                units[i].setHp(units[i].getHp()+qFloor(units[i].type->getNorm_hp()/10));
            if (units[i].getHp() > units[i].type->getNorm_hp())
                units[i].setHp(units[i].type->getNorm_hp());
        }

    }
    for (int i=0;i<players.length();++i)
    {
        qDebug()<<i;
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

    this->update();
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

void Map::paint(QPainter *painter)
{
    QPen pen = QPen();
    int startcol = qFloor(m_cx / 64);
    int startrow = qFloor(m_cy / 64);
    int tilecountw = qFloor(width() / 64);
    int tilecounth = qFloor(height() / 64);
    double tx, ty = 0.0f;   //tile x y
    //qDebug()<<sizeX;
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
                tile = QPixmap("E:/QtProjects/untitled13/"+tileSource+".png");
                tileCache.insert(tileSource, tile);
            }
            if (mapArr[i][j]==5)
                painter->drawPixmap(tx, ty, QPixmap("E:/QtProjects/untitled13/1.png"));
            painter->drawPixmap(tx, ty, tile);
            painter->setFont(QFont("Helvetica", 8));
            painter->setPen(QColor(255, 255, 255, 100));
            painter->drawText(QRectF(tx, ty, 64, 64),
                              Qt::AlignCenter,
                              QString::number(i)+":"+QString::number(j));
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
            if ((focus.infocus->getAp()>0)&&(&units[i] != focus.infocus)&&(units[i].player != activePlayer)&&
                    (qCeil(sqrt(pow(focus.infocus->getCellx()- units[i].getCellx() ,2) +
                                pow(focus.infocus->getCelly() - units[i].getCelly(),2)))
                     <=focus.infocus->type->getAttackRadius()))
            {
                painter->fillRect(sx,sy,64,64,QColor(255, 0, 0, 100));

                pen.setColor(QColor(255,0,0));
                pen.setWidth(3);
                painter->setPen(pen);
                painter->drawRect(sx+2,sy+2,60,60);

            }
        }
        painter->fillRect(sx+7,sy+55,50.0f*(units[i].getHp()/units[i].type->getNorm_hp()),4,QColor(0, 255, 0));
        pen.setColor(QColor(0,255,0));
        pen.setWidth(1);
        painter->setPen(pen);
        painter->drawRect(sx+7,sy+55,50,4);

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

void Map::mousePressEvent(QMouseEvent * event)
{
    /*if (event->buttons().testFlag(Qt::LeftButton) && focus.isEmpty)
    {
        int startcol = qFloor(m_cx / 64);
        int startrow = qFloor(m_cy / 64);
        for (int i = 0; i < units.length();++i)
        {
            int tx=64*(units[i].getCellx() - startcol);
            int ty=64*(units[i].getCelly() - startrow);
            if ((event->x > tx || event->x < tx+64) &&
                    (event->y > ty || event->y < ty+64))
            {
                focus.setInfocus(&units[i]);
            }
            //qDebug()<<event->x;
            //int yo=event->x();
        }
    }*/
    //qDebug()<<event->x();
    qDebug()<<"event->x()";
}

bool Map::isRecrPoss(int x, int y)
{
    /*qCeil(sqrt(pow((focus.infocus->getCellx()- units[i].getCellx()) ,2) +
                                        pow((focus.infocus->getCelly()) - units[i].getCelly(),2)))
                             <=*/
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
