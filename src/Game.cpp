#include "Game.h"

Game::Game() {}

Game::~Game() {
    for(auto & player: players){
        delete player;
    }
}

void Game::addPlayers(std::vector<Player *> p) {
    for(auto & player: p){
        players.push_back(player);
    }
}

std::vector<Player *> Game::getPlayers() {
    return players;
}
