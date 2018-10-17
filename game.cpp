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
    ai = AI();
    m->readMap(":/maps/map3.txt");
    m->players.append(Player(0,Tzinch_cult,Man,QColor(255,0,0),":/images/flags/chaosflag.png"));
    m->players.append(Player(1,O_Hereticus,Comp,QColor(0,0,255),":/images/flags/incflag.png"));
    m->distributePlayers();
    m->gameInProgress = true;
    ai.setMap(m);
    //connect(m,SIGNAL(Map::aiturn()),ai,SLOT(AI::doTurn()));

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
