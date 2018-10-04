#include "recruitment.h"

Recruitment::Recruitment(QQuickItem *parent) :
    QQuickPaintedItem(parent)
{
    m=NULL;
    focus = NULL;
    connect(this, SIGNAL(xChanged()), this, SLOT(update()));
    connect(this, SIGNAL(yChanged()), this, SLOT(update()));
}

void Recruitment::paint(QPainter *painter)
{
    QPixmap sprite;
    int n=0;
    if (m!=NULL){
        for (int i=0;i<m->unittypes.length();++i)
        {

            if (m->unittypes[i].fraction == m->activePlayer->fraction &&
                    m->activePlayer->cash >= m->unittypes[i].cost)
            {
                if (focus==NULL)
                    focus=&m->unittypes[i];
                if(spriteCache.contains(m->unittypes[i].getImSorce())) {
                    sprite = spriteCache.value(m->unittypes[i].getImSorce());
                }
                else {
                    sprite = QPixmap(m->unittypes[i].getImSorce());
                    spriteCache.insert(m->unittypes[i].getImSorce(), sprite);
                }
                rel.insert(n,m->unittypes[i].getid());
                painter->fillRect(5,5+n*100,64,64,QColor(190, 190, 190, 95));
                painter->fillRect(5,5+n*100,250,95,QColor(25,30,75));
                painter->setFont(QFont("Helvetica", 8));
                painter->setPen(QColor(255, 255, 255));
                painter->drawText(QRectF(80, 10+n*100, 200, 15),
                                  Qt::AlignLeft,m->unittypes[i].getName());
                painter->drawText(QRectF(80, 25+n*100, 200, 15),
                                  Qt::AlignLeft,m->unittypes[i].getDescription());
                painter->drawText(QRectF(80, 40+n*100, 200, 15),
                                  Qt::AlignLeft,"Цена : " + QString::number(m->unittypes[i].cost));
                if (focus!=NULL)
                if (focus->getid() == m->unittypes[i].getid())
                {
                    painter->setPen(QColor(225, 255, 255));
                    painter->drawRect(5,5+n*100,250,95);

                }
                painter->drawPixmap(5, 5+n*100, sprite);
                ++n;
            }
        }
    }
}

Map *Recruitment::map()
{
    return this->m;
}

void Recruitment::setMap(Map *map)
{
    this->m = map;

    this->update();
}

void Recruitment::mouseClicked(int x, int y)
{
    int ny;
    ny = qFloor((y-5)/100);
    for (int i=0;i<m->unittypes.length();++i)
    {
        if (m->unittypes[i].getid() == rel.value(ny))
            focus = &m->unittypes[i];
    }
    this->update();
    //qDebug()<<rel.value(ny);

}

void Recruitment::acceptr()
{
    m->units.append(Unit(focus,m->activePlayer,qFloor(m->lastx/64)+qFloor(m->cx()/64),qFloor(m->lasty/64)+qFloor(m->cy()/64)));
    m->occupancy[qFloor(m->lastx/64)+qFloor(m->cx()/64)][qFloor(m->lasty/64)+qFloor(m->cy()/64)] = true;
    m->activePlayer->units+=1;
    m->activePlayer->cash-=focus->cost;
    m->update();
}

