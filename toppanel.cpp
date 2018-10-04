#include "toppanel.h"

TopPanel::TopPanel(QQuickItem *parent):
    QQuickPaintedItem(parent)
{
    m=NULL;
}

void TopPanel::paint(QPainter *painter)
{
    //25,30,75,100
    painter->fillRect(0,0,width(),height(),QColor(25,30,75));
    if (this->m!=NULL)
    {
        painter->setFont(QFont("Helvetica", 10));
        painter->setPen(QColor(255, 255, 255));
        painter->drawText(QRectF(0, 3, 250, 25),
                          Qt::AlignCenter,"Деньги : "+
                          QString::number(m->activePlayer->cash));
        painter->drawText(QRectF(250, 3, 250, 25),
                          Qt::AlignCenter,"Поселения : "+
                          QString::number(m->activePlayer->villages));
        painter->drawText(QRectF(500, 3, 250, 25),
                          Qt::AlignCenter,"Юниты : "+
                          QString::number(m->activePlayer->units));
    }

}

Map *TopPanel::map()
{
    return this->m;
}

void TopPanel::setMap(Map *map)
{
    this->m = map;

    this->update();
}
