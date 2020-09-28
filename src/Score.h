#ifndef COSC_ASSIGN_TWO_SCORE
#define COSC_ASSIGN_TWO_SCORE
#include "Player.h"

class Score
{
public:
    Score(Tile ** newlyPlaced, Player player);

    // Apply Horizontal Scoring
    void addScoring();
    // Check if there is a next tile
    bool nextExists(Tile ** current);
    // Decide to go up, down, left or right
    void getNextCoordinates(int currentX, int currentY);

    // Get Round Score
    int getRoundScore();

private:
    // Placed Piece in Mosaic
    Tile ** newlyPlaced;

    // Checking From
    Tile ** current;
    // Checking
    Tile ** next;

    // Next Position to check
    int nextX;
    int nextY;

    int roundScore;
    Player player;
    Tile ** grid;
};

#endif // COSC_ASSIGN_TWO_SCORE

