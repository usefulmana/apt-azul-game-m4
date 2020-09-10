

#ifndef A2_TILE_H
#define A2_TILE_H


class Tile {
private:
    char name;
public:
    Tile(char n);
    Tile();
    ~Tile();
    char getName();
    void setName(const char& n);
};


#endif //A2_TILE_H
