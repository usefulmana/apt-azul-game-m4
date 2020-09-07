
#ifndef COSC_ASSIGN_TWO_PLAYER
#define COSC_ASSIGN_TWO_PLAYER

#include <string>
typedef std::string string;

class Player
{
public:
    // Constructor/Desctructor
    Player(string name, string id, string email);
    ~Player();

    //Copy constructor to copy Player for saving
    Player(Player &other);

    // Save score of round
    void setScore(int score);

    // Get Final Score - get last element of vector
    void getFinalScore();

    // Reset Score at end of game
    void resetScore();

    //Print Player Information
    string toString();


    //Getters/Setters

    // name of player
    string getName();

    // id of player
    string getId();

    // email of player
    string getEmail();

private:
    string name;
    string id;
    string email;

    // Score of player
    //vector<int> scores;
};

#endif // COSC_ASSIGN_TWO_PLAYER
