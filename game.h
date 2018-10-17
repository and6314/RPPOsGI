#ifndef GAME_H
#define GAME_H
#include <QObject>
#include <QDebug>
#include <ai.h>
#include <map.h>

class Game: public QObject
{
    Q_OBJECT
    Q_PROPERTY(Map *m READ map WRITE setMap NOTIFY mapChanged)

public:
    Game(QObject *parent = nullptr);
    Map *map();
    void setMap(Map *map);
    Q_INVOKABLE void newGame();
    Q_INVOKABLE void endGame();
    Q_INVOKABLE void ait();


signals:
    void mapChanged(Map *map);

private:
    Map *m;
    AI ai;

};

#endif // GAME_H
