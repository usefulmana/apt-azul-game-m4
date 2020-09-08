#include "Game.h"
#include "utils.h"

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

void Game::save(const string &fileName, std::vector<std::string> vector) {
    writeMultipleStrToFile(fileName, vector);
}
