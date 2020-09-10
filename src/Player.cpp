#include "Player.h"

Player::Player(std::string name)
{
    this->name = name;
    this->score = 0;

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

Player::Player(Player &other) : name(other.name)
{
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

std::string Player::getName()
{
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

void Player::printMosaic() {

    rowCount = 1;

    for (int i = 0; i < MOSAIC_DIM; ++i) {
        std::cout << i + 1 << ":";
        for (int k = 0; k < MOSAIC_DIM - rowCount + 1; ++k) {
            std::cout << "  ";
        }
        for (int j = 0; j < rowCount; ++j) {
            std::cout << unlaidRow[i][j].getName() << " ";
        }
        std::cout << "|| ";
        for (int m = 0; m < MOSAIC_DIM; ++m) {
            std::cout << grid[i][m].getName() << " ";
        }
        rowCount++;
        std::cout << std::endl;
    }
}
