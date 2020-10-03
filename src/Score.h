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

    /**
    * Constructor
    * @param player : user of whos points it is
    * @param placedX : x-coordinate of tile placed
    * @param placedY : y-coordinate of tile placed
    */
    Score(Player *player, int placedX, int placedY);

    /*
    * Add scoring to an aggregate
    */
    void addScoring();

    /**
    * Sets current tile being assessedy
    * @param x : x-coordinate of tile
    * @param y : y-coordinate of tile
    */
    void setCurrent(int x, int y);

    /**
    * Sets current coordinates of the next tile to be assessed
    * @param direction : sets enum value to be checked next
    */
    void setNext(Direction direction);

    /**
    * Fetches value of current round points
    * @return : int roundScore
    */
    int getRoundScore();

private:

    // Placed Piece in Mosaic
    int placedX;
    int placedY;

    // Position of current score evaluatee
    int currentX;
    int currentY;

    // Next Position to be evaluated
    int nextX;
    int nextY;
    char nextTileChar;

    // Instantiation of direction
    Direction direction;

    //Function return objects
    int roundScore;
    Player * player;
    Tile ** grid;

    //Check on Vertical Scoring
    bool wasVertical;

    //Check on Horizontal Scoring
    bool wasHoriz;

};

#endif // COSC_ASSIGN_TWO_SCORE

