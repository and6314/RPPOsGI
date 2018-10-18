#ifndef GAME_H
#define GAME_H
#include <QObject>
#include <QDebug>
#include "ai.h"
#include "map.h"
#include "menu.h"

class Game: public QObject
{
    Q_OBJECT
    Q_PROPERTY(Map *m READ map WRITE setMap NOTIFY mapChanged)
    Q_PROPERTY(Menu *mn READ menu WRITE setMenu NOTIFY menuChanged)

public:
    Game(QObject *parent = nullptr);
    Map *map();
    void setMap(Map *map);
    Menu *menu();
    void setMenu(Menu *menu);
    Q_INVOKABLE void newGame();
    Q_INVOKABLE void endGame();
    Q_INVOKABLE void ait();


signals:
    void mapChanged(Map *map);
    void menuChanged(Menu *menu);

private:
    Map *m;
    AI ai;
    Menu *mn;
};

#endif // GAME_H
