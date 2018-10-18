#include "menu.h"

Menu::Menu(QObject *parent) :
    QObject(parent)
{
    s_map = "3";
}

QString Menu::map()
{
    return this->s_map;
}

void Menu::setMap(QString map)
{
    this->s_map = map;
}

QString Menu::baseIncome1()
{
    return this->bi1;
}

QString Menu::baseIncome2()
{
    return this->bi2;
}

QString Menu::baseIncome3()
{
    return this->bi3;
}

QString Menu::baseIncome4()
{
    return this->bi4;
}

void Menu::setBI1(QString bi)
{
    this->bi1 = bi;
}

void Menu::setBI2(QString bi)
{
    this->bi2 = bi;
}

void Menu::setBI3(QString bi)
{
    this->bi3 = bi;
}

void Menu::setBI4(QString bi)
{
    this->bi4 = bi;
}

QString Menu::playerfr1()
{
    return this->pf1;
}

QString Menu::playerfr2()
{
    return this->pf2;
}

QString Menu::playerfr3()
{
    return this->pf3;
}

QString Menu::playerfr4()
{
    return this->pf4;
}

void Menu::setPf1(QString pf)
{
    this->pf1 = pf;
}

void Menu::setPf2(QString pf)
{
    this->pf2 = pf;
}

void Menu::setPf3(QString pf)
{
    this->pf3 = pf;
}

void Menu::setPf4(QString pf)
{
    this->pf4 = pf;
}
