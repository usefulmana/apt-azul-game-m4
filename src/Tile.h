#ifndef A2_TILE_H
#define A2_TILE_H

class Tile {

public:

    /*
    * Copy Constructor assining Tile Name/Colour
    */
    Tile(char n);

    /*
    * Default Constructor
    */
    Tile();

    /*
    * Deconstructor
    */
    ~Tile();

    /**
    * Retrieve name of Tile in question
    * @return char name
    */
    char getName();

    /**
    * Assign name of Tile in question
    * @param char n: name passed to Tile
    */
    void setName(char n);

    private:
    char name;
};


#endif //A2_TILE_H
