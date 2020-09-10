
#ifndef COSC_ASSIGN_TWO_PLAYER
#define COSC_ASSIGN_TWO_PLAYER

#include <string>

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


private:
    std::string name;
    int score;
    // TODO BROKEN
};

#endif // COSC_ASSIGN_TWO_PLAYER
