#include "Player.h"

Player::Player() {
    name = DEFAULT_NAME;
}

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

    // Index of board color
    int count = 0;
    // Initialize Grid
    for (int i = 0; i < MOSAIC_DIM; ++i) {
        for (int j = 0; j < MOSAIC_DIM; ++j) {
            grid[i][j] = *new Tile(MOSAIC_BOARD_COLOR[count]);
            count++;
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

    // Initilize broken row
    for (int i = 0; i < BROKEN_ROW_SIZE; ++i) {
        brokenRow[i] = *new Tile(' ');
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

void Player::setScore(int s) {
    score = s;
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
        
        // Print whitespaces
        for (int k = 0; k < MOSAIC_DIM - rowCount + 1; ++k) {
            std::cout << DOUBLE_WHITESPACE;
        }
        // Print unlaid row
        for (int j = 0; j < rowCount; ++j) {
            std::cout << unlaidRow[i][rowCount - 1 - j].getName() << WHITESPACE;
        }
        std::cout << "|| ";
        // Print grid
        for (int m = 0; m < MOSAIC_DIM; ++m) {
            std::cout << grid[i][m].getName() << WHITESPACE;
        }

        //Increment Count
        rowCount++;
        std::cout << std::endl;
    }
}
void Player::printBrokenRow() {
    std::cout << "broken: ";
    for (int i = 0; i < BROKEN_ROW_SIZE; ++i) {
        std::cout << brokenRow[i].getName() << WHITESPACE;
    }
    std::cout << std::endl;
}

void Player::addToBrokenRow(char tile) {
    if (brokenRowCount < BROKEN_ROW_SIZE){
        brokenRow[brokenRowCount].setName(tile);
        brokenRowCount++;
    }
}

Tile **Player::getUnlaidRow() {
    return unlaidRow;
}

Tile **Player::getGrid() {
    return grid;
}

Tile* Player::getBrokenRow() {
    return brokenRow;
}

int Player::getBrokenRowCount() {
    return brokenRowCount;
}

void Player::setBrokenRowCount(int count) {
    brokenRowCount = count;
}
