#include "Score.h"

Score::Score(Tile newlyPlaced, Player player) {   
    // Declare Variables
    this->newlyPlaced = newlyPlaced;
    this->roundScore = 0;
    this->player = player;

    // Calculate Scoring
    horizontalScoring();
    verticalScoring();

    // Add Round Score to Player Total
    player.addScore(roundScore);
}

void Score::horizontalScoring() {
    current = newlyPlaced;
    while (isRight(current)) {
        roundScore++;
        current = next;
    }
}


bool Score::isRight(Tile current) {
    if () { // Tile found next to current
        next = ; // Position of Next Tile
        return true; 
    } else {
        return false; 
    }
}

int Score::getRoundScore() {
    return roundScore;
}