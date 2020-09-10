#include "Player.h"

Player::Player(std::string name)
{
    this->name = name;
    this->score = 0;
}

Player::Player(Player &other) : name(other.name)
{
}

Player::~Player()
{
}

std::string Player::getName()
{
    return name;
}

void Player::addScore(int s) {
    score += s;
}

int Player::getScore() {
    return score;
}

void Player::resetScore() {
    score = 0;
}
