//
// Created by usefulmana on 16/10/20.
//

#ifndef A2_ADVGAME_H
#define A2_ADVGAME_H
#include <vector>
#include <iostream>
#include <string>
#include "Types.h"
#include "AdvPlayer.h"
#include "LinkedList.h"
#include <random>
#include "utils.h"

class AdvGame {
private:
    std::vector<AdvPlayer*> players;

    LinkedList<Tile*> * tileBag;

    LinkedList<Tile*> * boxLid;

    // Factories
    Tile ** factories;

    std::vector<Tile*> center;

    int seed;
public:
    /**
     * Default Construct
     */
    AdvGame();
    /**
     * Desctructor
     */
    ~AdvGame();
    /**
     * Play an advanced Azul game
     */
    void play();
    /**
     * Load an advanced game from a file
     * @param fileName
     */
    void load(const std::string & fileName);
    /**
     * Test load an advanced game
     * @param fileName
     */
    void testLoadGame(char* fileName);
    /**
     * Add players to the game
     * @param p
     */
    void addPlayers(std::vector<AdvPlayer*> p);
    /**
     * Get players
     * @return
     */
    std::vector<AdvPlayer*> getPlayers();
    /**
     * Fill tile bag automatically
     */
    void setTileBagAutomatically();
    /**
     * Fill tile bag from a string
     * @param line
     */
    void setTileBagFromString(const std::string & line);
    /**
     * Move first tile to the center factory
     */
    void addFirstTileToCenter();
    /**
     * Execute a play command
     * @param command
     * @param player
     */
    void execute(const std::string & command, AdvPlayer * player);
    /**
     * Print new turn information for a player
     * @param player
     */
    void printNewTurnInformation(AdvPlayer * player);
    /**
     * Check if a tile can be placed in a row of the mosaic
     * @param player
     * @param row
     * @return
     */
    bool canColorBePlacedInARow(AdvPlayer * player, int row);
    /**
     * Check if a tile can be placed in a column of the mosaic
     * @param color
     * @param column
     * @param player
     * @return
     */
    bool canColorBePlacedInAColumn(const char & color, int column, AdvPlayer * player);
    /**
     * Fill factories with tiles from the tile bag
     */
    void fillFactories();
    /**
     * Player a turn of Azul
     * @param player
     * @param end
     * @param savedInputs
     */
    void playTurn(AdvPlayer *player, bool &end, std::vector<std::string> &savedInputs);
    /**
     * Interpret a play command
     * @param input
     * @param player
     * @param valid
     * @param savedInputs
     */
    void interpretCommand(std::string & input, AdvPlayer * player, bool & valid, std::vector<std::string> & savedInputs);
    /**
     * Reset the game after a round ends
     */
    void reset();
    /**
     * Check if end of round condition is met
     * @return
     */
    bool endRound();
    /**
     * Check if a tile is alone in the mosaic
     * @param row
     * @param col
     * @param mosaic
     * @return
     */
    bool isTileAlone(int row, int col, Tile ** mosaic);
    /**
     * Check if a tile has both horizontally and vertically adjacent tiles
     * @param row
     * @param col
     * @param mosaic
     * @return
     */
    bool isTileAdjacentHozVer(int row, int col, Tile ** mosaic);
    /**
     * Scoring
     * @param player
     * @param row
     * @param col
     * @param color
     */
    void score(AdvPlayer * player, int row, int col, char color);
    /**
     * Trigger the tile placing phase before the end of a round
     * @param savedInputs
     */
    void engageTilePlacingPhase(std::vector<std::string> & savedInputs);
    /**
     * Trigger the tile placing phase before the end of a round for a loaded game
     * @param file
     * @param line
     * @param lineCount
     * @param savedInputs
     */
    void loadTilePlacingPhase(std::ifstream &file, std::string &line, int &lineCount, std::vector<std::string> & savedInputs);
    /**
     * Read line and then quit if end of file is reached
     * @param file
     * @param line
     * @param player
     * @param end
     * @param lineCount
     */
    void readLineAndQuit(std::ifstream &file, std::string &line, AdvPlayer *player, bool &end,
                         int &lineCount);
    /**
     * Trigger the tile placing phase before the end of a round for a loaded game from test mode
     * @param file
     * @param line
     * @param lineCount
     * @param savedInputs
     */
    void testLoadTilePlacingPhase(std::ifstream &file, std::string &line, int &lineCount, std::vector<std::string> & savedInputs);

    /**
     * Ask user for input
     * @return
     */
    std::string getPlaceCommand();
    /**
     * Validate the place command
     * @param command
     * @param player
     * @return
     */
    std::vector<std::string> validatePlaceCommand(const std::string & command, AdvPlayer * player);
    /**
     * Execute the place command
     * @param player
     * @param command
     * @param savedInputs
     */
    void place(AdvPlayer * player, const std::string & command, std::vector<std::string> & savedInputs);
    /**
     * Read line and execute each line. One EOF, ask for user to continue inputting
     * @param file
     * @param line
     * @param player
     * @param end
     * @param savedInputs
     * @param lineCount
     */
    void readLineAndPlayTurn(std::ifstream &file, std::string &line, AdvPlayer *player, bool &end,
                                   std::vector<std::string> &savedInputs, int &lineCount);
    /**
     * Get the rows that are full
     * @param player
     * @return
     */
    std::string getRowsToBePlaced(AdvPlayer * player);
    /**
     * Check if a chosen spot in the mosaic is occupied by a tile
     * @param row
     * @param col
     * @param player
     * @return
     */
    bool checkIfSpotIsOccupied(int row, int col, AdvPlayer * player);
    /**
     * Check if a row is full
     * @param player
     * @param row
     * @return
     */
    bool isRowQualifiedToBePlaced(AdvPlayer * player, int row);
    /**
     * Print current game state
     */
    void printGameState();
    /**
     * Print final results of the game
     */
    void printFinalResults();
    /**
     * Deduct points for tiles in the broken row
     * @param player
     */
    void deductBrokenTile(AdvPlayer * player);
    /**
     * Print scores of players
     */
    void printScores();
    /**
     * Shuffle tile bag
     */
    void shuffleTileBag();
    /**
     * Check if the tilebag and box lid are empty
     * @return
     */
    bool areTileBagAndBoxLidEmpty();
    /**
     * Move tiles from the box lid to the tilebag
     */
    void moveTilesFromBoxLidToTileBag();
    /**
     * Check if end game condition is met
     * @return
     */
    bool checkIfEndGame();
    /*
     * Set a seed
     */
    void setSeed(const int & s);
    /**
     * Get the seed
     * @return
     */
    int getSeed();
};


#endif //A2_ADVGAME_H
