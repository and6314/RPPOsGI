#include "game.h"

Game::Game(QObject *parent) :
    QObject(parent)
{
    m = NULL;

}

Map *Game::map()
{
    return this->m;
}

void Game::setMap(Map *map)
{
    this->m = map;
}

Menu *Game::menu()
{
    return this->mn;
}

void Game::setMenu(Menu *menu)
{
    this->mn= menu;
}

void Game::newGame()
{
    bool ok = true;
    ai = AI();
    QString s = "1";qDebug()<<mn->s_map;
    if (mn->s_map=="First map")
        s="1";
    if (mn->s_map=="Second map")
        s="2";
    if (mn->s_map=="Third map")
        s="3";
    m->readMap(":/maps/map"+s+".txt");
    if (mn->pf1!="None")
    {
        Fraction f = mn->pf1 == "Cult"?Tzinch_cult:O_Hereticus;
        QString flag = mn->pf1 == "Cult"?":/images/flags/chaosflag.png":":/images/flags/incflag.png";
        m->players.append(Player(0,f,Man,QColor(255,0,0),flag,mn->bi1.toInt(&ok,10)));
    }
    if (mn->pf2!="None")
    {
        Fraction f = mn->pf2 == "Cult"?Tzinch_cult:O_Hereticus;
        QString flag = mn->pf2 == "Cult"?":/images/flags/chaosflag.png":":/images/flags/incflag.png";
        m->players.append(Player(1,f,Comp,QColor(0,0,255),flag,mn->bi2.toInt(&ok,10)));
    }
    if (mn->pf3!="None")
    {
        Fraction f = mn->pf3 == "Cult"?Tzinch_cult:O_Hereticus;
        QString flag = mn->pf3 == "Cult"?":/images/flags/chaosflag.png":":/images/flags/incflag.png";
        m->players.append(Player(2,f,Comp,QColor(0,255,0),flag,mn->bi3.toInt(&ok,10)));
    }
    if (mn->pf4!="None")
    {
        Fraction f = mn->pf4 == "Cult"?Tzinch_cult:O_Hereticus;
        QString flag = mn->pf4 == "Cult"?":/images/flags/chaosflag.png":":/images/flags/incflag.png";
        m->players.append(Player(3,f,Comp,QColor(0,255,255),flag,mn->bi4.toInt(&ok,10)));
    }
    m->distributePlayers();
    m->gameInProgress = true;
    m->update();
    ai.setMap(m);

}

void Game::endGame()
{
    m->clear();
    m->gameInProgress = false;
}

void Game::ait()
{
    ai.turn();
}
