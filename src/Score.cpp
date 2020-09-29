#include "Score.h"
#include <ctype.h>
#define maxDirections 3


Score::Score(Player player, int placedX, int placedY) {   
    // Declare Variables
    this->player = player;
    this->grid = player.getGrid();

    this->placedX = placedX;
    this->placedY = placedY;

    this->roundScore = 0;

    // Calculate Scoring
    addScoring();

    // Add Round Score to Player Total
    player.addScore(roundScore);
}

void Score::addScoring() {

    for(int i = 0; i < maxDirections; i ++) {

        orientation = i;

        // Set Current as Placed Piece
        setCurrent(placedX, placedY);
        // Set Next
        setNext(orientation);
        // Set Next Char
        nextTileChar = grid[nextX][nextY].getName();

        // If nextChar == capital
        while (isupper(nextTileChar)) {

            // Add Score
            roundScore++;   

            // Reset Current and Next Piece
            setCurrent(nextX, nextY);
            setNext(orientation);
            nextTileChar = grid[nextX][nextY].getName();

        }
    }
}

void Score::setCurrent(int x, int y) {
    currentX = x;
    currentY = y;
}

void Score::setNext(int orientation) {

    nextX = currentX;
    nextY = currentY;

    // Up
    if (orientation == 0) {

        nextY = currentY + 1;

    // Right
    } else if (orientation == 1) {

        nextX = currentX + 1;

    // Down
    } else if (orientation == 2) {

        nextY = currentY - 1;

    // Left
    } else if (orientation == 3) {

        nextX = currentX - 1;

    }
}

int Score::getRoundScore() {
    return roundScore;
}

