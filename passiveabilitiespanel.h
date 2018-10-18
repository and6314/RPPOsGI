#ifndef PASSIVEABILITIESPANEL_H
#define PASSIVEABILITIESPANEL_H

#include <QQuickItem>
#include <QQuickPaintedItem>
#include "map.h"

class PassiveAbilitiesPanel: public QQuickPaintedItem
{
    Q_OBJECT
    Q_PROPERTY(Map *m READ map WRITE setMap NOTIFY mapChanged)

public:
    PassiveAbilitiesPanel(QQuickItem *parent  = nullptr);
    void paint(QPainter *painter);

    Map *map();
    void setMap(Map *map);

signals:
    void mapChanged(Map *map);

private:
    Map *m;

};

#endif // PASSIVEABILITIESPANEL_H
