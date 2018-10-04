#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <unittype.h>
#include <QColor>
class Player
{
public:
    Player();
    Player(int id,Fraction f,QColor col);
    Fraction fraction;
    int getid();
    QColor color;
    int cash;
    int villages;
    int units;

private:
    int id;
};

#endif // PLAYER_H
