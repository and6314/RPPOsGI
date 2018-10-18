#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <unittype.h>
#include <QColor>
#include <QPixmap>

enum Person{Man,Comp};

class Player
{
public:
    Player();
    Player(int id,Fraction f,Person p,QColor col, QString flagsource,int bi);
    Fraction fraction;
    int getid();
    QColor color;
    int cash;
    int villages;
    int units;
    QPixmap flag;
    bool operator==(const Player& arg);
    Person person;
    int baseIncome;

private:
    int id;
};

#endif // PLAYER_H
