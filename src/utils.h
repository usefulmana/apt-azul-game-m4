#ifndef A2_UTILS_H
#define A2_UTILS_H

#include <vector>
#include <string>
#include <fstream>
#include "Game.h"

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
void writeToFile(const std::string & fileName, const std::string & str);

/**
 * Write a vector of strings to a file
 * @param fileName : target file's name
 * @param str : string vector to be written
 */
void writeMultipleStrToFile(const std::string & fileName, std::vector<std::string> vector);

/**
 * Delete a file
 * @param fileName: target file's name
 */
void deleteAFile(const std::string & fileName);

/**
 * Rename a file
 * @param oldName: old name of the file
 * @param newName: new name of the file
 */
void renameAFile(const std::string & oldName, const std::string & newName);

/**
 * Check if a file exists
 * @param file : file to check
 * @return : true if the file exists, false if not
 */
bool checkIfFileExists(const char* file);

/**
 * Quit the game
 */
void quitGame();

#endif //A2_UTILS_H
