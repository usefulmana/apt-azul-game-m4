#ifndef COSC_ASSIGN_TWO_SCORE
#define COSC_ASSIGN_TWO_SCORE
#include "Player.h"

enum Direction {
    UP,
    RIGHT,
    DOWN, 
    LEFT
};

class Score
{
public:
    Score(Player player, int placedX, int placedY);

    // Apply Scoring
    void addScoring();
    // Set Coordinates of Current Tile
    void setCurrent(int x, int y);
    // Set Coordinates of Next Tile
    void setNext(Direction direction);

    // Get Round Score
    int getRoundScore();

private:
    // Placed Piece in Mosaic
    int placedX;
    int placedY;

    // Checking From
    int currentX;
    int currentY;

    // Next Position to check
    int nextX;
    int nextY;
    char nextTileChar;

    // Keep Track of Direction
    Direction direction;

    int roundScore;
    Player player;
    Tile ** grid;

};

#endif // COSC_ASSIGN_TWO_SCORE

