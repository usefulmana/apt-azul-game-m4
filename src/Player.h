
#ifndef COSC_ASSIGN_TWO_PLAYER
#define COSC_ASSIGN_TWO_PLAYER

#include <string>
#include "Tile.h"
#include "Types.h"
#include <iostream>

class Player
{
public:
    // Constructor/Desctructor
    Player(std::string name);
    ~Player();

    //Copy constructor to copy Player for saving
    Player(Player &other);

    // Save score of round
    void addScore(int s);

    int getScore();

    // Reset Score at end of game
    void resetScore();

    //Getters/Setters
    std::string getName();

    void printMosaic();

    void printBrokenRow();

    void addToBrokenRow(Tile tile);

    void createPlayers();

    Tile ** getUnlaidRow();

    Tile* getBrokenRow();

    Tile ** getGrid();

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
