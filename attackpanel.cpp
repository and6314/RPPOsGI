#include "attackpanel.h"

AttackPanel::AttackPanel(QQuickItem *parent) :
    QQuickPaintedItem(parent)
{
    m=NULL;
    focus = NULL;
    connect(this, SIGNAL(xChanged()), this, SLOT(update()));
    connect(this, SIGNAL(yChanged()), this, SLOT(update()));
}

void AttackPanel::paint(QPainter *painter)
{
    Unit *target = m->unitOnCell(qFloor(m->lastx/64)+qFloor(m->cx()/64),qFloor(m->lasty/64)+qFloor(m->cy()/64));
    QPixmap sprite;
    int n=0;
    if (m!=NULL){
        if (m->gameInProgress && !m->focus.isEmpty()) {
        if (m->activePlayer!=NULL && focus!=NULL)
            if (!m->focus.infocus->type->attacks.contains(*focus))
                focus=NULL;
        for (int i=0;i<m->focus.infocus->type->attacks.length();++i)
        {
            if (m->focus.infocus->isAttackPossible(target,m->focus.infocus->type->attacks[i]))
            {
                if (focus==NULL)
                    focus =&m->focus.infocus->type->attacks[i];
                if(spriteCache.contains(m->focus.infocus->type->attacks[i].imageSorce)) {
                    sprite = spriteCache.value(m->focus.infocus->type->attacks[i].imageSorce);
                }
                else {
                    sprite = QPixmap(m->focus.infocus->type->attacks[i].imageSorce);
                    spriteCache.insert(m->focus.infocus->type->attacks[i].imageSorce, sprite);
                }
                rel.insert(n,m->focus.infocus->type->attacks[i].id);
                painter->fillRect(5,5+n*100,64,64,QColor(190, 190, 190, 95));
                painter->fillRect(5,5+n*100,250,95,QColor(25,30,75));
                painter->setPen(QColor(255, 255, 255));
                painter->drawText(QRectF(80, 10+n*100, 200, 15),
                                  Qt::AlignLeft,m->focus.infocus->type->attacks[i].name);
                painter->drawText(QRectF(80, 25+n*100, 200, 15),
                                  Qt::AlignLeft,"Урон: "+QString::number(m->focus.infocus->type->attacks[i].damage));
                int chn = m->focus.infocus->type->attacks[i].chance + (m->focus.infocus->getMorale()-50)/100*m->focus.infocus->type->attacks[i].chance;
                chn = chn>=100 ? 99 : chn;
                chn = chn<=0 ? 1 : chn;
                painter->drawText(QRectF(80, 40+n*100, 200, 15),
                                  Qt::AlignLeft,"Шанс попадания: " + QString::number(chn));
                if (focus->id == m->focus.infocus->type->attacks[i].id)
                {
                    painter->setPen(QColor(225, 255, 255));
                    painter->drawRect(5,5+n*100,250,95);
                }
                painter->drawPixmap(5, 5+n*100, sprite);
                ++n;
            }
        }

    }}
}

Map *AttackPanel::map()
{
    return this->m;
}

void AttackPanel::setMap(Map *map)
{
    this->m = map;

    this->update();
}

void AttackPanel::mouseClicked(int x, int y)
{
    int ny;
    ny = qFloor((y-5)/100);
    for (int i=0;i<m->focus.infocus->type->attacks.length();++i)
    {
        if (m->focus.infocus->type->attacks[i].id == rel.value(ny))
            focus = &m->focus.infocus->type->attacks[i];
    }
    this->update();
}

void AttackPanel::acceptr()
{
    int x = qFloor(m->lastx/64)+qFloor(m->cx()/64);
    int y = qFloor(m->lasty/64)+qFloor(m->cy()/64);
    if (focus!=NULL)
    {
        Unit *target = m->unitOnCell(x,y);
        if (m->focus.infocus->attack(target,*focus))
        {
            m->occupancy[target->getCellx()][target->getCelly()] = false;
            if (target->type->specialfeatures.contains("lord"))
            {
                Player p = *target->player;
                m->units.removeOne(*target);
                m->players.removeOne(p);
                if (m->players.length()==1)
                    m->aiVictory();
            }
            else
                m->units.removeOne(*target);
        }

    }
    m->update();
}
