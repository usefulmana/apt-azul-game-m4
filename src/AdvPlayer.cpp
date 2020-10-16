//
// Created by usefulmana on 16/10/20.
//

#include "AdvPlayer.h"

AdvPlayer::AdvPlayer() {
    name = DEFAULT_NAME;
}

AdvPlayer::AdvPlayer(std::string n, int id, bool f) {
    this->name = n;
    this->score = 0;
    this->first = f;
    this->id = id;
    this->brokenRowCount = 0;

    // Declare grid
    mosaic = new Tile*[ADV_MOSAIC_DIM];
    for (int i = 0; i < ADV_MOSAIC_DIM; ++i) {
        mosaic[i] = new Tile[ADV_MOSAIC_DIM];
    }

    // Index of board color
    int count = 0;
    // Initialize Grid
    for (int i = 0; i < ADV_MOSAIC_DIM; ++i) {
        for (int j = 0; j < ADV_MOSAIC_DIM; ++j) {
            mosaic[i][j] = *new Tile('.');
            count++;
        }
    }

    // Declare unlaid row
    unlaidRow = new Tile*[ADV_MOSAIC_DIM];
    rowCount = 1;
    for (int i = 0; i < ADV_MOSAIC_DIM; ++i) {
        unlaidRow[i] = new Tile[rowCount];
        rowCount++;
    }

    // Initialize unlaid row
    rowCount = 1;
    for (int i = 0; i < ADV_MOSAIC_DIM; ++i) {
        for (int j = 0; j < rowCount; ++j) {
            unlaidRow[i][j] = *new Tile('.');
        }
        rowCount++;
    }

    // Initilize broken row
    for (int i = 0; i < ADV_BROKEN_ROW_SIZE; ++i) {
        brokenRow[i] = *new Tile(' ');
    }
}

AdvPlayer::~AdvPlayer() {
    // Delete mosaic
    for (int i = 0; i < MOSAIC_DIM; ++i) {
        delete mosaic[i];
    }
    delete [] mosaic;

    // Delete unlaidrow
    for (int i = 0; i < MOSAIC_DIM; ++i) {
        delete unlaidRow[i];
    }
    delete [] unlaidRow;
}

std::string AdvPlayer::getName() {
    return name;
}

void AdvPlayer::addScore(int s) {
    score += s;
}

int AdvPlayer::getScore() {
    return score;
}

void AdvPlayer::resetScore() {
    score = 0;
}

void AdvPlayer::printMosaic() {
    rowCount = 1;
    // Print Mosaic coordinate
    std::cout << "                   " << "1 2 3 4 5 6" << std::endl;
    for (int i = 0; i < ADV_MOSAIC_DIM; ++i) {
        std::cout << i + 1 << ":";

        // Print whitespaces
        for (int k = 0; k < ADV_MOSAIC_DIM - rowCount + 1; ++k) {
            std::cout << DOUBLE_WHITESPACE;
        }
        // Print unlaid row
        for (int j = 0; j < rowCount; ++j) {
            std::cout << unlaidRow[i][rowCount - 1 - j].getName() << WHITESPACE;
        }
        std::cout << "|| ";
        // Print grid
        for (int m = 0; m < ADV_MOSAIC_DIM; ++m) {
            std::cout << mosaic[i][m].getName() << WHITESPACE;
        }

        //Increment Count
        rowCount++;
        std::cout << std::endl;
    }
}

void AdvPlayer::printBrokenRow() {
    std::cout << "broken: ";
    for (int i = 0; i < ADV_BROKEN_ROW_SIZE; ++i) {
        std::cout << brokenRow[i].getName() << WHITESPACE;
    }
    std::cout << std::endl;
}

void AdvPlayer::addToBrokenRow(char tile) {
    if (brokenRowCount < ADV_BROKEN_ROW_SIZE){
        brokenRow[brokenRowCount].setName(tile);
        brokenRowCount++;
    }
}

Tile **AdvPlayer::getUnlaidRow() {
    return unlaidRow;
}

Tile **AdvPlayer::getMosaic() {
    return mosaic;
}

Tile* AdvPlayer::getBrokenRow() {
    return brokenRow;
}

int AdvPlayer::getBrokenRowCount() {
    return brokenRowCount;
}

void AdvPlayer::setBrokenRowCount(int count) {
    brokenRowCount = count;
}

bool AdvPlayer::isFirst() {
    return first;
}

void AdvPlayer::setFirst(bool f) {
    this->first = f;
}

int AdvPlayer::getId() {
    return id;
}
