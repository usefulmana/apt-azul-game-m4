#ifndef COSC_ASSIGN_TWO_GAME
#define COSC_ASSIGN_TWO_GAME

#include "Player.h"

class Game
{
public:
    // Constructor/Destructor
    Game();
    ~Game();

    // Save the Game
    void save();

    // Save the Game
    void load(Game game);

    // Player takes turn
    void takeTurn(Player player);

    // Calculate Score of Round
    void endRound(Player player, Player player2);

    // Determine Winner
    void endGame(Player player, Player player2);

    // Add Player
    void addPlayer(Player player);

    // Get Player
    void getPlayer(string id);

private:
};

#endif // COSC_ASSIGN_TWO_GAME
