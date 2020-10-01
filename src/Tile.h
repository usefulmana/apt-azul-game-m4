#ifndef A2_TILE_H
#define A2_TILE_H

class Tile {
private:
    char name;
    char tile;
public:
    Tile(char n);
    Tile();
    ~Tile();
    char getName();
    void setName(char n);
};


#endif //A2_TILE_H
