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

    // Save the Game
    void load(Game game);

    // Player takes turn
    void takeTurn(Player player);

    // Calculate Score of Round
    void endRound(Player player, Player player2);

    // Determine Winner
    void endGame(Player player, Player player2);

    // Add Player
    void addPlayers(std::vector<Player*> p);

    // Get Player
    std::vector<Player*> getPlayers();

private:
    std::vector<Player*> players;
};

#endif // COSC_ASSIGN_TWO_GAME
