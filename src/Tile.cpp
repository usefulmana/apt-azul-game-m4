#include "Tile.h"

//Constructor
Tile::Tile(char n) {
    this->name = n;
}

//Deconstructor
Tile::~Tile() {
};

char Tile::getName() {
    return name;
}

Tile::Tile() {
}

void Tile::setName(const char &n) {
    this->name = n;
}

char Tile::getTile(){
    return tile;
}

