#ifndef COSC_ASSIGN_TWO_GAME
#define COSC_ASSIGN_TWO_GAME

#include "Player.h"
#include "LinkedList.h"
#include <vector>
#include "utils.h"
#include <iostream>
#include "Types.h"

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

    void fillFactories();

    void printFactories();

private:
    std::vector<Player*> players;
    // Stores all Valid Turns
    std::vector<std::string> savedInputs;
    LinkedList<Tile*> * tileBag;
    Tile ** factories;
    std::vector<Tile*> center;
};

#endif // COSC_ASSIGN_TWO_GAME
