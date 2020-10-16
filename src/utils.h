#ifndef A2_UTILS_H
#define A2_UTILS_H

#include <vector>
#include <string>
#include <fstream>
#include <random>
#include "Game.h"
#include "AdvPlayer.h"

/**
 * Split a string into elements of a vector
 * @param str : a string to be split
 * @param delimiter : a char to split
 * @return : a vector containing the split string
 */
std::vector<std::string> splitString(std::string str, char delimiter);

/**
 * Get current date time
 * @return a datetime string. Format is YYYYMMDDHHMMSS
 */
const std::string getDateTime();

/**
 * Write a string to a file
 * @param fileName : target file's name
 * @param str : string to be written
 */
void writeToFile(const std::string &fileName, const std::string &str);

/**
 * Write a vector of strings to a file
 * @param fileName : target file's name
 * @param str : string vector to be written
 */
void writeMultipleStrToFile(const std::string &fileName, std::vector<std::string> vector);

/**
 * Delete a file
 * @param fileName: target file's name
 */
void deleteAFile(const std::string &fileName);

/**
 * Rename a file
 * @param oldName: old name of the file
 * @param newName: new name of the file
 */
void renameAFile(const std::string &oldName, const std::string &newName);

/**
 * Check if a file exists
 * @param file : file to check
 * @return : true if the file exists, false if not
 */
bool checkIfFileExists(const char *file);

/**
 * Quit the game
 */
void quitGame();

/**
 * Shuffle a string
 * @param str : string to be shuffled
 * @param engine : a random engine
 */
void shuffleString(std::string &str, std::default_random_engine &engine);

/*
    * Translates up-to-date information from the user into a file which can be recalled from main to
    * continue playing where left off
    */
void save(const std::string &fileName, std::vector<std::string> vector);

/**
 * Print Instructions
 */
void printInstructions();

/**
 * Print error messages
 * @param errors
 */
void printEndErrorMessage(std::vector<std::string> &errors);

/**
    * Checks whether a particular tile exsists in a particular factory
    * @return true if it exists, false if not
    */
bool tileExistsInAFactory(const char &tile, int factory, Tile **factories, std::vector<Tile *> center);

/**
 * Reads the input provided by the User into Terminal; Boundary and type validation
 * @param input : input string to be checked
 * @return : a vector containing errors of the player's input
 */
std::vector<std::string> checkAdvInput(std::string input, AdvPlayer *player, const std::string &validChars, Tile **factories,
                                    std::vector<Tile *> center);

/**
* Checks the status of a particular factory.
* @return true if empty, false if not;
*/
bool isAFactoryEmpty(int factory, Tile **factories);

/*
* Returns and Prints list of all factories to the Terminal
*/
void printFactories(Tile **factories, std::vector<Tile *> center);

/**
    * Checks the status of Centre factory
    * @return true if empty, false if not;
    */
bool isCenterEmpty(std::vector<Tile *> center);

/**
* Checks the status of all factories.
* @return true if empty, false if not;
*/
bool areFactoriesEmpty(Tile **factory);

/**
   * Get user's input and save it to a string
   * @param input
   */
void getUserInput(std::string &input);

void drawFromFactories(Tile **factories, int factory, std::string &chosenTiles, std::vector<Tile *> &center,
                       const char &color);

void moveExcessTilesToCenter(Tile **factories, int factory, std::vector<Tile *> &center);

void setWhoGoesFirstNextRound(std::vector<Tile *> &center, int factory, std::string &chosenTiles, AdvPlayer *player,
                              std::vector<AdvPlayer *> &players);

void handleFirstTile(std::string &chosenTiles, AdvPlayer *player, LinkedList<Tile *> *boxLid);

void placeOnRow(int targetRow, AdvPlayer *player, std::string &chosenTiles);

/**
* Checks whether a row has been filled.
* @return true if full, false if not;
*/
bool isAdvRowFull(int row, AdvPlayer *player);

/*
* Returns a string containing the colour of the grid
*/
std::string getAdvGridColor(int row, AdvPlayer *player);


/*
* Returns a char relating to the colour assigned to a particular Mosaic row
*/
char getAdvColorOfaRow(int row, AdvPlayer *player);

#endif //A2_UTILS_H
