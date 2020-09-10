#include "Player.h"

Player::Player(string name)
{
    this->name = name;
    // Create score vector for player
}

Player::Player(Player &other) : name(other.name)
{
}

Player::~Player()
{
}

string Player::getName()
{
    return name;
}

//string Player::getId()
//{
//    return id;
//}
//
//string Player::getEmail()
//{
//    return email;
//}
