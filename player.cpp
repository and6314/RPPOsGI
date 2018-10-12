#include "player.h"

Player::Player()
{

}
Player::Player(int id, Fraction f,Person p, QColor col, QString flagsource)
{
    fraction = f;
    this->id = id;
    person = p;
    color = col;
    cash = 100;
    villages = 0;
    units = 0;
    flag = QPixmap(flagsource);
}

int Player::getid()
{
    return this->id;
}

bool Player::operator==(const Player& arg)
{
    return arg.id==this->id;
}
