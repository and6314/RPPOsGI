#include "rightpanel.h"

RightPanel::RightPanel(QQuickItem *parent) :
    QQuickPaintedItem(parent)
{
    m = NULL;
}

void RightPanel::paint(QPainter *painter)
{
    painter->fillRect(0,0,width(),height(),QColor(25,30,75));

    if (this->m!=NULL)
    {
        painter->fillRect(30,30,width()-60,width()-60,m->activePlayer->color);
        painter->drawPixmap(30,30,m->activePlayer->flag);
        if (!m->isFocusEmpty())
        {
            painter->setFont(QFont("Helvetica", 10));
            painter->setPen(QColor(255, 255, 255));

            painter->drawText(QRectF(30, width(), 250, 25),
                              Qt::AlignLeft,"Название : "+ m->focus.infocus->type->getName());
            painter->drawText(QRectF(30, width()+30, 250, 25),
                              Qt::AlignLeft,"Описание : "+m->focus.infocus->type->getDescription());
            painter->drawText(QRectF(30, width()+60, 250, 25),
                              Qt::AlignLeft,"Передвижение : "+QString::number(m->focus.infocus->getMp())+"/"+QString::number(m->focus.infocus->type->getNorm_mp()));
            painter->drawText(QRectF(30, width()+90, 250, 25),
                              Qt::AlignLeft,"Атаки : "+QString::number(m->focus.infocus->getAp())+"/"+QString::number(m->focus.infocus->type->getNorm_ap()));
            painter->drawText(QRectF(30, width()+120, 250, 25),
                              Qt::AlignLeft,"Радиус атаки : "+QString::number(m->focus.infocus->type->getAttackRadius()));
            painter->drawText(QRectF(30, width()+150, 250, 25),
                              Qt::AlignLeft,"Урон : "+QString::number(m->focus.infocus->type->getDamage()));
            painter->drawText(QRectF(30, width()+180, 250, 25),
                              Qt::AlignLeft,"Здоровье : "+QString::number(m->focus.infocus->getHp())+"/"+QString::number(m->focus.infocus->type->getNorm_hp()));

        }
    }
}

Map *RightPanel::map()
{
    return this->m;
}

void RightPanel::setMap(Map *map)
{
    this->m = map;

    this->update();
}
