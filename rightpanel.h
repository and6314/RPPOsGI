#ifndef RIGHTPANEL_H
#define RIGHTPANEL_H
#include <QObject>
#include <QQuickItem>
#include <QQuickPaintedItem>
#include "map.h"

class RightPanel: public QQuickPaintedItem
{
    Q_OBJECT
    Q_PROPERTY(Map *m READ map WRITE setMap NOTIFY mapChanged)

public:
    RightPanel(QQuickItem *parent  = nullptr);
    void paint(QPainter *painter);

    Map *map();
    void setMap(Map *map);

signals:
    void mapChanged(Map *map);

private:
    Map *m;

};

#endif // RIGHTPANEL_H
