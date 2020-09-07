#include "Player.h"

Player::Player(string name, string id, string email) : name(name), id(id), email(email)
{
    // Create score vector for player
}

Player::Player(Player &other) : name(other.name), id(other.id), email(other.email)
{
}

Player::~Player()
{
}

string Player::getName()
{
    return name;
}

string Player::getId()
{
    return id;
}

string Player::getEmail()
{
    return email;
}
