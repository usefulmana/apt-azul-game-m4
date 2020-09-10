#ifndef COSC_ASSIGN_TWO_GAME
#define COSC_ASSIGN_TWO_GAME

#include "Player.h"
#include <vector>

class Game
{
public:
    // Constructor/Destructor
    Game();
    ~Game();

    // Save the Game
    void save(const std::string & fileName, std::vector<std::string> vector);

    // Play
    void play();

    // Score
    void score();

    // Save the Game
    void load(Game game);

    // Add Player
    void addPlayers(std::vector<Player*> p);

    // Get Player
    std::vector<Player*> getPlayers();

    void printTileBag();
    void printFactories();

private:
    std::vector<Player*> players;
    std::vector<std::string> savedInputs;
    Tile ** factories;
    std::vector<Tile*> center;
};

#endif // COSC_ASSIGN_TWO_GAME
