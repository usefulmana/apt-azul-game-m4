//
// Created by usefulmana on 16/10/20.
//

#include "AdvGame.h"

AdvGame::AdvGame() {
    // Declare factories
    factories = new Tile *[NUM_OF_FACTORIES];
    for (int i = 0; i < NUM_OF_FACTORIES; ++i) {
        factories[i] = new Tile[FACTORY_SIZE];
    }

    // Initialize factories
    for (int i = 0; i < NUM_OF_FACTORIES; ++i) {
        for (int j = 0; j < FACTORY_SIZE; ++j) {
            factories[i][j] = *new Tile(WHITESPACE);
        }
    }

    // Initialize the tile bag
    tileBag = new LinkedList<Tile *>();

    // Initialize the box lid
    boxLid = new LinkedList<Tile *>();

    // Default seed
    seed = 1;
}

AdvGame::~AdvGame() {
    // Delete players
    for (auto &player: players) {
        delete player;
    }

    // Delete factories
    for (int i = 0; i < NUM_OF_FACTORIES; ++i) {
        delete factories[i];
    }
    delete[] factories;

    // Delete tile bag;
    tileBag->clear();
    delete tileBag;

    // Delete Box Lid
    boxLid->clear();
    delete boxLid;
}

void AdvGame::addPlayers(std::vector<AdvPlayer *> p) {
    // Add Player to back of Vector
    for (auto &player: p) {

        players.push_back(player);
    }
}

std::vector<AdvPlayer *> AdvGame::getPlayers() {
    return players;
}

void AdvGame::play(){
    std::vector<std::string> savedInputs;

    savedInputs.push_back(ADVANCED_MODE_HEADER);

    std::string bag;

    for (int i = 0; i < NUM_OF_TILES_IN_TILE_BAG; ++i) {
        bag += tileBag->get(i)->getName();
    }
    // Save tile bag to input vector;
    savedInputs.push_back(bag);

    savedInputs.push_back(std::to_string(seed));

    // Save players name
    for (auto &player: players) {
        savedInputs.push_back(player->getName());
    }

    //Add "First" Tile to Centre Factory
    addFirstTileToCenter();

    //Fill Remaining Factories
    fillFactories();

    //Round Number Counter
    int round = 1;

    bool gameOver = false;
    while(!gameOver){
        std::cout << "=== Round " << round << " Starts ===" << std::endl;
        bool end = endRound();
        if (players[0]->isFirst()) {

        }
        else {
            
        }
    }
}

void AdvGame::testLoadGame(char *fileName) {

}

void AdvGame::load(const std::string &fileName) {

}

void AdvGame::execute(const std::string &command, AdvPlayer *player) {

}

void AdvGame::setTileBagAutomatically() {
    std::default_random_engine engine(seed);
    std::string tiles = ADV_ALL_TILES;

    shuffleString(tiles, engine);

    for (size_t i = 0; i < tiles.length(); ++i) {
        tileBag->addBack(new Tile(tiles[i]));
    }
}

void AdvGame::setTileBagFromString(const std::string &line) {
    //Initialise Tile Bag
    tileBag = new LinkedList<Tile *>();

    //Fill Tile Bag
    for (size_t i = 0; i < line.length(); ++i) {
        tileBag->addBack(new Tile(line[i]));
    }
}

void AdvGame::fillFactories() {
    // Fill factories with tiles from the tile bag
    for (int i = 0; i < NUM_OF_FACTORIES && tileBag->getLength() > 0; ++i) {
        for (int j = 0; j < FACTORY_SIZE && tileBag->getLength() > 0; ++j) {
            factories[i][j].setName(tileBag->get(0)->getName());

            //Remove tile from tile bag
            tileBag->popFront();
        }
    }
}


void AdvGame::setSeed(const int &s) {
    this->seed = s;
}

bool AdvGame::endRound() {
    return isCenterEmpty(center) && areFactoriesEmpty(factories);
}
