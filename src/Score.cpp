#include "Score.h"
#include <ctype.h>
#define MAX_DIRECTIONS 4


Score::Score(Player player, int placedX, int placedY) {   
    // Declare Variables
    this->player = player;
    this->grid = player.getGrid();

    this->placedX = placedX;
    this->placedY = placedY;

    this->roundScore = 0;

    this->direction = Direction(UP);

    // Calculate Scoring
    addScoring();

    // Add Round Score to Player Total
    player.addScore(roundScore);
}

void Score::addScoring() {

    for(int i = 0; i < MAX_DIRECTIONS; i ++) {
        // orientation = i;
        direction = (Direction)i;

        // Set Current as Placed Piece
        setCurrent(placedX, placedY);
        // Set Next
        setNext(direction);
        // Set Next Char
        nextTileChar = grid[nextX][nextY].getName();

        // Look at all elements in selected direction that have next
        // Where next == capital
        while (isupper(nextTileChar)) {

            // Add Score
            roundScore++;   

            // Reset Current and Next Piece
            setCurrent(nextX, nextY);
            setNext(direction);
            nextTileChar = grid[nextX][nextY].getName();

        }
    }
}

void Score::setCurrent(int x, int y) {
    currentX = x;
    currentY = y;
}

void Score::setNext(Direction direction) {

    nextX = currentX;
    nextY = currentY;

    // Up
    if (direction == 0) {

        nextY = currentY + 1;

    // Right
    } else if (direction == 1) {

        nextX = currentX + 1;

    // Down
    } else if (direction == 2) {

        nextY = currentY - 1;

    // Left
    } else if (direction == 3) {

        nextX = currentX - 1;

    }
}

int Score::getRoundScore() {
    return roundScore;
}

