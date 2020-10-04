#include "Score.h"

Score::Score(Player * player, int placedX, int placedY) {   
    // Declare Variables
    this->player = player;
    this->grid = player->getGrid();

    this->placedX = placedX;
    this->placedY = placedY;

    this->roundScore = 0;

    this->wasVertical = false;
    this->wasHoriz = false;

    // Check if placement was made
    if (placedY != INVALID_COORDINATE && placedY != INVALID_COORDINATE) {
        // Calculate Scoring
        addScoring();
    }

    player->addScore(roundScore);
}

Score::~Score(){
    
}

void Score::addScoring() {

    bool extraGiven = false;

    roundScore++;

    // Cycle through direction
    for(int i = 0; i < MAX_DIRECTIONS; i ++) {

        // Direction from index
        direction = (Direction)i;

        // Set Current as Placed Piece
        setCurrent(placedX, placedY);

        // Set Next Piece
        setNext(direction);

        //Check for Invalid Coordinates
        if (nextX != INVALID_COORDINATE){
            // Set Next Char
            nextTileChar = grid[nextY][nextX].getName();
        }

        //Check for Capitilisation
        while (isupper(nextTileChar) && nextX != -2) {
            roundScore++; 

            // If there is a Vertical connection
            if (direction == 0 || direction == 2) {
                wasVertical = true;
            }

            // If there is a Horizontal connection
            if (direction == 1 || direction == 3) {
                wasHoriz = true;
            }

            // If there is a dual (horizontal and vertical) connection
            if (wasVertical && wasHoriz && extraGiven != true) {    
                roundScore++;
                // Only allows one extra point
                extraGiven = true;
            }

            // Reset Current and Next Piece
            setCurrent(nextX, nextY);
            setNext(direction);

            // If the Next Coordinate is Valid
            if (nextX != INVALID_COORDINATE){
                //Fetch Coordinate
                nextTileChar = grid[nextY][nextX].getName();
            }
        }
    }
}

void Score::setCurrent(int x, int y) {
    //Set Variables
    currentX = x;
    currentY = y;
}

void Score::setNext(Direction direction) {
    //Set Variables
    nextX = currentX;
    nextY = currentY;

    // Check Upwards Direction
    if (direction == 0 && currentY != MAX_UP) {
        nextY = currentY - 1;

    // Check Right Direction
    } else if (direction == 1 && currentX != MAX_RIGHT) {
        nextX = currentX + 1;

    // Check Downwards Direction
    } else if (direction == 2 && currentY != MAX_DOWN) {
        nextY = currentY + 1;

    // Check Left Direction
    } else if (direction == 3 && currentX != MAX_LEFT) {
        nextX = currentX - 1;
    }

    // Check for inability to set next coordinates
    if (nextX == currentX && nextY == currentY) {
        //Declare Out-Of-Bounds
        nextX = INVALID_COORDINATE;
        nextY = INVALID_COORDINATE;
    }
}

int Score::getRoundScore() {
    return roundScore;
}

