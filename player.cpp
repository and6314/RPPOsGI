#include "player.h"

Player::Player()
{

}
Player::Player(int id, Fraction f,Person p, QColor col, QString flagsource,int bi)
{
    fraction = f;
    this->id = id;
    person = p;
    color = col;
    cash = 250;
    villages = 0;
    units = 0;
    flag = QPixmap(flagsource);
    baseIncome = bi;
}

int Player::getid()
{
    return this->id;
}

bool Player::operator==(const Player& arg)
{
    return arg.id==this->id;
}
