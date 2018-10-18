#include "passiveabilitiespanel.h"

PassiveAbilitiesPanel::PassiveAbilitiesPanel(QQuickItem *parent) :
    QQuickPaintedItem(parent)
{
    m = NULL;
}

void PassiveAbilitiesPanel::paint(QPainter *painter)
{
    painter->fillRect(0,0,width(),height(),QColor(25,30,75));
    if (this->m!=NULL)
    {
        if (m->gameInProgress)
            if (!m->isFocusEmpty())
            {
                for (int i=0;i<m->focus.infocus->type->passiveAbilities.length();++i)
                {
                    painter->setFont(QFont("Helvetica", 10));
                    painter->setPen(QColor(255, 255, 255));
                    painter->drawText(5,20+40*i, m->focus.infocus->type->passiveAbilities[i].name);
                    painter->setFont(QFont("Helvetica", 8));
                    QString trg = m->focus.infocus->type->passiveAbilities[i].side==Ally ? "Свой" : "Враг";
                    painter->drawText(180,20+40*i, "Цель : "+trg);
                    painter->drawText(5,30+40*i, "Сила : "+QString::number(m->focus.infocus->type->passiveAbilities[i].value));
                    painter->drawText(180,30+40*i, "Дальность : "+QString::number(m->focus.infocus->type->passiveAbilities[i].abilityRadius));
                }
            }
    }
}

Map *PassiveAbilitiesPanel::map()
{
    return this->m;
}

void PassiveAbilitiesPanel::setMap(Map *map)
{
    this->m = map;

    this->update();
}
