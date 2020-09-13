//
// Created by usefulmana on 7/9/20.
//

#ifndef A2_UTILS_H
#define A2_UTILS_H

#include <vector>
#include <string>
#include <fstream>


std::vector<std::string> splitString(std::string str, char delimiter);

std::vector<std::string> checkInput(std::string input);

const std::string getDateTime();

void writeToFile(const std::string & fileName, const std::string & str);
void writeMultipleStrToFile(const std::string & fileName, std::vector<std::string> vector);
void deleteAFile(const std::string & fileName);
void renameAFile(const std::string & oldName, const std::string & newName);
bool checkIfFileExists(const char* file);
void quitGame();
#endif //A2_UTILS_H
