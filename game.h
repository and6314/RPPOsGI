#ifndef GAME_H
#define GAME_H
#include <QObject>
#include <map.h>
#include <QDebug>

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

signals:
    void mapChanged(Map *map);

private:
    Map *m;
};

#endif // GAME_H
