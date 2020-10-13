#ifndef COSC_ASSIGN_TWO_GAME
#define COSC_ASSIGN_TWO_GAME

#include "Player.h"
#include "LinkedList.h"
#include <vector>
#include "utils.h"
#include <iostream>
#include "Types.h"
#include <algorithm>
#include "Score.h"
#include <random>

class Game
{
public:
    
    /*
    * Default Constructor
    */
    Game();

    /*
    *  Deconstructor
    */
    ~Game();

    /*
    * The initilisation of the Game.
    * This method aims to set up the physicals of the game, such as the Factories and Mosaics.
    */
    void play();

    /*
    * Translates up-to-date information from the user into a file which can be recalled from main to
    * continue playing where left off
    */
    void save(const std::string & fileName, std::vector<std::string> vector);

    /*
    * Reads file previously saved, and translates information in to resume an old game from where it
    * was left off
    */
    void load(const std::string & fileName);

    /*
    * Adds inserted player names into the initialised Vector to hold them as players of the current game
    */
    void addPlayers(std::vector<Player*> p);

    /**
    * Returns all players in the current game
    * @return : vector of players
    */
    std::vector<Player*> getPlayers();

    /*
    * Fills Tile Bag with predefined list of tiles
    */
    void setTileBagAutomatically();

    /**
    * Returns contents of Tile Bag
    * @return : tile bag
    */
    LinkedList<Tile *> * getTileBag();

    /*
    * Places 'F' Tile to the centre factory
    */
    void addFirstTileToCenter();

    /**
    * Fills Tile Bag with a list of tiles determined by a String input
    * @param line : string to be parsed
    */
    void setTileBagFromString(const std::string & line);

    /*
    * Administers the turn dependent on what the User has entered in the command line
    */
    void execute(const std::string & command, Player * player);

    /*
    * Fills factories dependent on the Tile Bag Content
    */
    void fillFactories();

    /*
    * Amends factories and rows back to their state at the beginning of the game
    */
    void reset();

    /*
    * Returns and Prints list of all factories to the Terminal
    */
    void printFactories();

    /**
    * Checks the status of Centre factory
    * @return true if empty, false if not;
    */
    bool isCenterEmpty();

    /**
    * Checks the status of all factories.
    * @return true if empty, false if not;
    */
    bool areFactoriesEmpty();

    /**
    * Checks the status of a particular factory. 
    * @return true if empty, false if not;
    */
    bool isAFactoryEmpty(int factory);

    /**
     * Reads the input provided by the User into Terminal; Boundary and type validation
     * @param input : input string to be checked
     * @return : a vector containing errors of the player's input
     */
    std::vector<std::string> checkInput(std::string input, Player * player);

    /**
    * Checks whether a particular tile exsists in a particular factory
    * @return true if it exists, false if not
    */
    bool tileExistsInAFactory(const char & tile, int factory);

    /*
    * Returns a char relating to the colour assigned to a particular Mosaic row
    */
    char getColorOfaRow(int row, Player * player);

    /*
    * Returns a string containing the colour of the grid
    */
    std::string getGridColor(int row, Player * player);

    /**
    * Checks whether a row has been filled.
    * @return true if full, false if not;
    */
    bool isRowFull(int row, Player * player);

    /**
    * Checks whether the end of a round is reached.
    * @return true if round is over, false if not;
    */
    bool endRound();

    /**
    * Checks whether a tile is marked to be removed.
    * @return true if marked, false if not;
    */
    bool markedToBeDeleted(Tile* tile, char color);

    /*
    * Testing method to review the status of the load game functionality
    */
    void testLoadGame(char* fileName);

    /*
    * Prints out the status of the game at execution
    */
    void printGameState();

    /**
    * Removes point from Player's score depending on their number of broken tiles
    * @param player : Us
    */
    void deductBrokenTile(Player * player);

    /**
     * Print final result of the game
     */
    void printFinalResults();

    /**
     * Print players' score
     */
    void printScores();

    /**
     * Print Instructions
     */
    static void printInstructions();

    /**
     * Print information about the new turn
     * @param player
     */
    void printNewTurnInformation(Player * player);

    /**
     * Get user's input and save it to a string
     * @param input
     */
    void getUserInput(std::string & input);

    /**
     * Print error messages
     * @param errors
     */
    void printEndErrorMessage(std::vector<std::string> & errors);

    /**
     * Interpret a command
     * @param input
     */
    void interpretCommand(std::string & input, Player * player, bool & valid, std::vector<std::string> & savedInputs);

    /**
     * Play a turn
     * @param player
     * @param end
     * @param savedInputs
     */
    void playTurn(Player * player, bool & end, std::vector<std::string> & savedInputs);

    /**
     * Read a line for a text file and execute that line. On EOF, resume play
     * @param file
     * @param line
     * @param player
     * @param end
     * @param savedInputs
     * @param lineCount
     */
    void readLineAndPlayTurn(std::ifstream & file, std::string & line, Player * player, bool & end,
                             std::vector<std::string> & savedInputs, int & lineCount);

    /**
     * Read a line for a text file and execute that line. On EOF, quit
     * @param file
     * @param line
     * @param player
     * @param end
     * @param savedInputs
     * @param lineCount
     */
    void readLineAndQuit(std::ifstream & file, std::string & line, Player * player, bool & end, int & lineCount);

    /**
     * Play with box lid and random shuffle of the tile bag
     */
    void playWithBoxLidAndRandomness();

    void setSeed(const int & s);

    int getSeed();

    void shuffleTileBag(const int & seed);
private:
    // Stores all game players
    std::vector<Player*> players;

    // Structure of Tile Bag
    LinkedList<Tile*> * tileBag;

    // Box lid
    LinkedList<Tile*> * boxLid;

    // Factories
    Tile ** factories;

    // Stores Tiles assigned to Centre Factory
    std::vector<Tile*> center;

    // Coordinates of Rcently Placed Tile
    int placedTileX;
    int placedTileY;

    // Seed
    int seed;
};

#endif // COSC_ASSIGN_TWO_GAME
