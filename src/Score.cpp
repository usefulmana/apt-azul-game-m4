#include "Score.h"
#include <ctype.h>
#define MAX_DIRECTIONS 4
#define MAX_UP 0
#define MAX_DOWN 4
#define MAX_RIGHT 4
#define MAX_LEFT 0

#define INVALID_COORDINATE -2


Score::Score(Player * player, int placedX, int placedY) {   
    // Declare Variables
    this->player = player;
    this->grid = player->getGrid();

    this->placedX = placedX;
    this->placedY = placedY;

    this->roundScore = 0;

    // // Calculate Scoring
    addScoring();

    // // Add Round Score to Player Total
    player->addScore(roundScore);
}

void Score::addScoring() {

    roundScore++;

    for(int i = 0; i < MAX_DIRECTIONS; i ++) {
        
        // For each Direction
        direction = (Direction)i;

        std::cout << "passed 1 - Direction: " << direction << std::endl;

        // Set Current as Placed Piece
        setCurrent(placedX, placedY);

        // Set Next
        setNext(direction);
        
        // If setNext returns invalid coordinates
        if (nextX != INVALID_COORDINATE){


            // Set Next Char
            nextTileChar = grid[nextY][nextX].getName();
            std::cout << "passed 4 - nextTileChar to check: " << nextTileChar << std::endl;
        }

        // Look at all elements in selected direction that have next
        // Where next == capital
        while (isupper(nextTileChar) && nextX != -2) {
            std::cout << "passed 5 - That tile is a capital letter" << std::endl;
            // Add Score
            roundScore++; 
            std::cout << "roundScore: " << roundScore << std::endl;

            if (direction == 0 || direction == 2) {
                wasVertical = true;
            }
            if (direction == 1 || direction == 4) {
                wasHoriz = true;
            }
            if (wasVertical && wasHoriz) {
                roundScore++;
            }

            // Reset Current and Next Piece
            setCurrent(nextX, nextY);
            
            setNext(direction);

            if (nextX != INVALID_COORDINATE){
                nextTileChar = grid[nextY][nextX].getName();
                std::cout << "passed 4 - nextTileChar to check: " << nextTileChar << std::endl;
            }


        }
    }
    std::cout << "got out of for loop alive" << std::endl;
    std::cout << "Final roundScore: " << roundScore << std::endl;


}

void Score::setCurrent(int x, int y) {
    currentX = x;
    currentY = y;
    std::cout << "currentX: " << currentX << std::endl;
    std::cout << "currentY: " << currentY << std::endl;

}

void Score::setNext(Direction direction) {

    nextX = currentX;
    nextY = currentY;

    // Up
    if (direction == 0 && currentY != MAX_UP) {

        nextY = currentY - 1;

    // Right
    } else if (direction == 1 && currentX != MAX_RIGHT) {

        nextX = currentX + 1;

    // Down
    } else if (direction == 2 && currentY != MAX_DOWN) {

        nextY = currentY + 1;

    // Left
    } else if (direction == 3 && currentX != MAX_LEFT) {

        nextX = currentX - 1;
    }

    // If it fails to set new Next Coordinate
    if (nextX == currentX && nextY == currentY) {
        nextX = INVALID_COORDINATE;
        nextY = INVALID_COORDINATE;
    }

    std::cout << "nextX: " << nextX << std::endl;
    std::cout << "nextY: " << nextY << std::endl;

}

int Score::getRoundScore() {
    return roundScore;
}

