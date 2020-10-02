#ifndef COSC_ASSIGN_TWO_GAME
#define COSC_ASSIGN_TWO_GAME

#include "Player.h"
#include "LinkedList.h"
#include <vector>
#include "utils.h"
#include <iostream>
#include "Types.h"
#include <algorithm>
#include "Score.h"

class Game
{
public:
    // Constructor/Destructor
    Game();
    ~Game();

    // Play
    void play();

    // Score
    // void score();

    // Save the Game
    void save(const std::string & fileName, std::vector<std::string> vector);

    // Load the Game
    void load(const std::string & fileName);

    // Add Players
    void addPlayers(std::vector<Player*> p);

    // Get All Players
    std::vector<Player*> getPlayers();

    void setTileBagAutomatically();

    LinkedList<Tile *> * getTileBag();

    void addFirstTileToCenter();

    void setTileBagFromString(const std::string & line);

    void execute(const std::string & command, Player * player);

    void score(Player * player);

    void fillFactories();

    void reset();

    void printFactories();

    bool isCenterEmpty();

    bool areFactoriesEmpty();

    bool isAFactoryEmpty(int factory);

    std::vector<std::string> checkInput(std::string input, Player * player);

    bool tileExistsInAFactory(const char & tile, int factory);

    char getColorOfaRow(int row, Player * player);

    std::string getGridColor(int row, Player * player);

    bool isRowFull(int row, Player * player);

    bool endRound();

    bool markedToBeDeleted(Tile* tile, char color);

    void testLoadGame(char* fileName);

    void printGameState();

    void deductBrokenTile(Player player);

private:
    std::vector<Player*> players;
    // Stores all Valid Turns
    std::vector<std::string> savedInputs;
    LinkedList<Tile*> * tileBag;
    Tile ** factories;
    std::vector<Tile*> center;

    // Coordinates of Rcently Placed Tile
    int placedTileX;
    int placedTileY;
};

#endif // COSC_ASSIGN_TWO_GAME
