#include "player.h"

Player::Player()
{

}
Player::Player(int id,Fraction f,QColor col)
{
    fraction = f;
    this->id = id;
    color = col;
    cash = 100;
    villages = 0;
    units = 0;
}

int Player::getid()
{
    return this->id;
}
