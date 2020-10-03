
#ifndef COSC_ASSIGN_TWO_PLAYER
#define COSC_ASSIGN_TWO_PLAYER

#include <string>
#include "Tile.h"
#include "Types.h"
#include <iostream>

class Player
{
public:

    /**
    * Default Constructor
    */
    Player();

    Player(std::string name);

    /*
    * Deconstructor
    */
    ~Player();

    /**
    * Copy Constructor for Player Saving
    * @param other : Player to be saved
    */
    Player(Player &other);

    /*
    * Add current round score to previous score
    */
    void addScore(int s);

    void setScore(int s);

    /**
    * Return current player's score
    * @return int score
    */

    int getScore();

    /*
    * Set score back to 0
    */
    void resetScore();

    /**
    * Return current player's name
    * @return : std::string name
    */
    std::string getName();

    /*
    * Return and Print Mosaic to Console
    */
    void printMosaic();

    /*
    * Return and Print Broken Row to Console
    */
    void printBrokenRow();

    /**
    * Add tile to player's broken row
    * @param tile : char to be added to broken row
    */
    void addToBrokenRow(char tile);


  

    void createPlayers();



    /**
    * Fetch Player's Unlaid Row
    * @return : Tile
    */
    Tile ** getUnlaidRow();

    /**
    * Fetch Player's Grid
    * @return : Tile
    */
    Tile ** getGrid();

    /**
    * Fetch Player's Broken Row
    * @return : Tile
    */
    Tile* getBrokenRow();

    /**
    * Return number of Tile's in Player's Broken Row
    * @return : int brokenRowCount
    */
    int getBrokenRowCount();

    /**
    * Set players broken row
    * @param count : length broken row it to be set to
    */
    void setBrokenRowCount(int count);

private:
    std::string name;
    int score;
    int rowCount;
    Tile ** grid;
    Tile ** unlaidRow;
    Tile brokenRow[BROKEN_ROW_SIZE];
    int brokenRowCount;
};

#endif // COSC_ASSIGN_TWO_PLAYER
