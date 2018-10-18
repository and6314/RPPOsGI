#ifndef ATTACKPANEL_H
#define ATTACKPANEL_H

#include <QObject>
#include <QQuickItem>
#include <QQuickPaintedItem>
#include "map.h"

class AttackPanel: public QQuickPaintedItem
{
    Q_OBJECT
    Q_PROPERTY(Map *m READ map WRITE setMap NOTIFY mapChanged)

public:
    AttackPanel(QQuickItem *parent  = nullptr);
    void paint(QPainter *painter);
    Q_INVOKABLE void mouseClicked(int x, int y);
    Q_INVOKABLE void acceptr();

    Map *map();
    void setMap(Map *map);

signals:
    void mapChanged(Map *map);

private:
    QMap<QString, QPixmap> spriteCache;
    AttackType *focus;
    QMap<int, int>rel;
    Map *m;

};

#endif // ATTACKPANEL_H
