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

void Game::newGame()
{
    m->readMap(":/maps/map3.txt");
    m->players.append(Player(0,Tzinch_cult,Man,QColor(255,0,0),":/images/flags/chaosflag.png"));
    m->players.append(Player(1,O_Hereticus,AI,QColor(0,0,255),":/images/flags/incflag.png"));
    m->distributePlayers();
    m->gameInProgress = true;
}

void Game::endGame()
{
    m->clear();
    m->gameInProgress = false;
}
