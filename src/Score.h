#ifndef COSC_ASSIGN_TWO_SCORE
#define COSC_ASSIGN_TWO_SCORE
#include "Player.h"


class Score
{
public:
    Score(Tile newlyPlaced, Player player);

    // Apply Horizontal Scoring
    void horizontalScoring();
    // Check if Tile on Right
    bool isRight(Tile current);
    // Check if Tile on Left
    bool isLeft(Tile current);

    // Apply Vertical Scoring
    void verticalScoring();
    // Check if Tile on Top
    bool isTop(Tile current);
    // Check if Tile on Bottom
    bool isBottom(Tile current);

    // Get Round Score
    int getRoundScore();

private:
    // Placed Piece in Mosaic
    Tile newlyPlaced;

    // Checking From
    Tile current;
    // Checking
    Tile next;

    int roundScore;
    Player player;
};

#endif // COSC_ASSIGN_TWO_SCORE

