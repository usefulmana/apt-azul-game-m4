#include "Player.h"

Player::Player(std::string name)
{   
    //Declare Variables
    this->name = name;
    this->score = 0;
    this->brokenRowCount = 0;

    // Declare grid
    grid = new Tile*[MOSAIC_DIM];
    for (int i = 0; i < MOSAIC_DIM; ++i) {
        grid[i] = new Tile[MOSAIC_DIM];
    }

    // Initialize Grid
    for (int i = 0; i < MOSAIC_DIM; ++i) {
        for (int j = 0; j < MOSAIC_DIM; ++j) {
            grid[i][j] = *new Tile('.');
        }
    }

    // Declare unlaid row
    unlaidRow = new Tile*[MOSAIC_DIM];
    rowCount = 1;
    for (int i = 0; i < MOSAIC_DIM; ++i) {
        unlaidRow[i] = new Tile[rowCount];
        rowCount++;
    }

    // Initialize unlaid row
    rowCount = 1;
    for (int i = 0; i < MOSAIC_DIM; ++i) {
        for (int j = 0; j < rowCount; ++j) {
            unlaidRow[i][j] = *new Tile('.');
        }
        rowCount++;
    }
}

Player::Player(Player &other) : name(other.name){
}

Player::~Player()
{
    // Delete grid
    for (int i = 0; i < MOSAIC_DIM; ++i) {
        delete grid[i];
    }
    delete [] grid;

    // Delete unlaidrow
    for (int i = 0; i < MOSAIC_DIM; ++i) {
        delete unlaidRow[i];
    }
    delete [] unlaidRow;

}

std::string Player::getName(){
    return name;
}

void Player::addScore(int s) {
    score += s;
}

int Player::getScore() {
    return score;
}

void Player::resetScore() {
    score = 0;
}

/**
 * Print out the mosaic
 */
void Player::printMosaic() {

    rowCount = 1;

    for (int i = 0; i < MOSAIC_DIM; ++i) {
        std::cout << i + 1 << ":";

        // Print whitespaces
        for (int k = 0; k < MOSAIC_DIM - rowCount + 1; ++k) {
            std::cout << "  ";
        }
        // Print unlaid row
        for (int j = 0; j < rowCount; ++j) {
            std::cout << unlaidRow[i][j].getName() << " ";
        }
        std::cout << "|| ";
        // Print grid
        for (int m = 0; m < MOSAIC_DIM; ++m) {
            std::cout << grid[i][m].getName() << " ";
        }
        
        //Increment Count
        rowCount++;
        std::cout << std::endl;
    }
}

/**
 * Print out the broken row
 */
void Player::printBrokenRow() {
    std::cout << "broken: ";
    for (int i = 0; i < BROKEN_ROW_SIZE; ++i) {
        if (brokenRow[i].getName() != '1') std::cout << brokenRow[i].getName() << " ";
    }
    std::cout << std::endl;
}

/**
 * Add tile to broken row
 * @param tile : tile to be added
 */
void Player::addToBrokenRow(Tile tile) {
    if (brokenRowCount < 7){
        brokenRow[brokenRowCount] = tile;
        std::cout << tile.getName() << std::endl;
        brokenRowCount++;
    }
}

Tile *Player::getBrokenRow() {
    for(int i = 0; i < 7; i++){
        return &brokenRow[i];
    }
}

Tile **Player::getUnlaidRow() {
    return unlaidRow;
}

Tile **Player::getGrid() {
    return grid;
}

void Player::createPlayers(){

}
