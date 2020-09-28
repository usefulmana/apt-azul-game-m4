#include "Score.h"
#define EMPTY_SPACE '.'

Score::Score(Tile ** newlyPlaced, Player player) {   
    // Declare Variables
    this->newlyPlaced = newlyPlaced;
    this->roundScore = 0;
    this->player = player;
    this->grid = player.getGrid();

    // Calculate Scoring
    addScoring();

    // Add Round Score to Player Total
    player.addScore(roundScore);
}

void Score::addScoring() {
    // For up, down, left, right
    for (int i = 0; i < 4; i ++){

        current = newlyPlaced;
        while (nextExists(current)) {
            roundScore++;
            current = next;
        }
    }
}


bool Score::nextExists(Tile ** current) {
    int currentX = current.getX();
    int currentY = current.getY();

    getNextCoordinates(currentX, currentY);
    
    if (grid[nextX][nextY] != EMPTY_SPACE) { // Tile found next to current
        next = grid[nextX][nextY]; // Position of Next Tile
        return true; 
    } else {
        return false; 
    }
}

void Score::getNextCoordinates(int currentX, int currentY) {

    nextY = currentY;
    nextX = currentX;

    if (rightDone == false) {
        // Right
        nextX = currentX + 1;
    } else if (leftDone == false) {
        // Left
        nextX = currentX - 1;
    } else if (upDone == false) {
        // Up
        nextY = currentY + 1;
    } else if (downDone == false) {
        // Down
        nextY = currentY - 1;
    }

}

int Score::getRoundScore() {
    return roundScore;
}