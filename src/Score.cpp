#include "Score.h"
#include <ctype.h>
#define MAX_DIRECTIONS 4
#define MAX_UP 0
#define MAX_DOWN 4
#define MAX_RIGHT 4
#define MAX_LEFT 0

Score::Score(Player * player, int placedX, int placedY) {   
    // Declare Variables
    this->player = player;
    this->grid = player->getGrid();

    this->placedX = placedX;
    this->placedY = placedY;

    this->roundScore = 0;

    this->wasVertical = false;
    this->wasHoriz = false;

    // Was a placement actually made?
    if (placedY != INVALID_COORDINATE && placedY != INVALID_COORDINATE) {
        // Calculate Scoring
        addScoring();
    }

    // Add Round Score to Player Total
    player->addScore(roundScore);
}

void Score::addScoring() {
    
    //Inital Point for Placement
    roundScore++;

    // For each Direction
    for(int i = 0; i < MAX_DIRECTIONS; i ++) {
        
        std::cout << "Direction Checking: " << i << std::endl;

        // Direction from index
        direction = (Direction)i;

        // Set Current as Placed Piece
        setCurrent(placedX, placedY);
        std::cout << "Current Tile (x,y): " << currentX << ", " << currentY << " Character on Tile: " << grid[currentY][currentX].getName() << std::endl;

        // Set Next Piece
        setNext(direction);
        std::cout << "Next Tile (x,y): " << nextX << ", " << nextY << std::endl;

        
        // If setNext returns invalid coordinates
        if (nextX != INVALID_COORDINATE){

            // Set Next Char
            nextTileChar = grid[nextY][nextX].getName();

        }

        // Look at all elements in selected direction that are capital
        while (isupper(nextTileChar) && nextX != -2) {

            std::cout << "Found Tile (x,y): " << nextX << ", " << nextY << " Character on Tile: " << nextTileChar << std::endl;

            // Add Score
            roundScore++; 

            // If Touching Placed Vertical Block
            if (direction == 0 || direction == 2) {
                wasVertical = true;
                std::cout << "==Found Vertical Placed" << std::endl;

            }
            // If Touching Placed Horizontal Block
            if (direction == 1 || direction == 3) {
                wasHoriz = true;
                std::cout << "==Found Horizontal Placed" << std::endl;

            }
            // If Touching Horzonital and Vertical Placed Block
            if (wasVertical && wasHoriz) {
                // Add extra point
                roundScore++;
                std::cout << "Added Extra Point" << std::endl;
            }

            // Reset Current and Next Piece
            setCurrent(nextX, nextY);
            setNext(direction);

            // If the Next Coordinate is Valid
            if (nextX != INVALID_COORDINATE){
                // Get Value of Next Tile
                nextTileChar = grid[nextY][nextX].getName();
            }
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

    // Go Up
    if (direction == 0 && currentY != MAX_UP) {

        nextY = currentY - 1;

    // Go Right
    } else if (direction == 1 && currentX != MAX_RIGHT) {

        nextX = currentX + 1;

    // Go Down
    } else if (direction == 2 && currentY != MAX_DOWN) {

        nextY = currentY + 1;

    // Go Left
    } else if (direction == 3 && currentX != MAX_LEFT) {

        nextX = currentX - 1;
    }

    // If it fails to set new Next Coordinate
    if (nextX == currentX && nextY == currentY) {
        // Next Coordinate must be out-of-bounds
        nextX = INVALID_COORDINATE;
        nextY = INVALID_COORDINATE;
    }

}

int Score::getRoundScore() {
    return roundScore;
}

