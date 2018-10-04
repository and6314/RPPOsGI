#ifndef RECRUITMENT_H
#define RECRUITMENT_H

#include <QObject>
#include <QQuickItem>
#include <QQuickPaintedItem>
#include "map.h"

class Recruitment: public QQuickPaintedItem
{
    Q_OBJECT
    Q_PROPERTY(Map *m READ map WRITE setMap NOTIFY mapChanged)
public:
    Recruitment(QQuickItem *parent  = nullptr);
    void paint(QPainter *painter);
    Q_INVOKABLE void mouseClicked(int x, int y);
    Q_INVOKABLE void acceptr();

    Map *map();
    void setMap(Map *map);
signals:
    void mapChanged(Map *map);
private:
    QMap<QString, QPixmap> spriteCache;
    UnitType *focus;
    QMap<int, int>rel;
    Map *m;
};

#endif // RECRUITMENT_H
