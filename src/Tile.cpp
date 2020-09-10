
#include "Tile.h"

Tile::Tile(char n) {
    this->name = n;
}

Tile::~Tile() {};

char Tile::getName() {
    return name;
}

Tile::Tile() {
}
