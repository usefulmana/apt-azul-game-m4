#include "utils.h"
#include <sstream>
#include <iostream>
#include <time.h>


std::vector<std::string> splitString(std::string str, char delimiter) {
    std::vector<std::string> result;
    std::stringstream ss(str);
    std::string temp;
    
    while (std::getline(ss, temp, delimiter)) {
        result.push_back(temp);
    }
    return result;
}

const std::string getDateTime(){
    // Current time of system
    time_t now = time(0);
    struct tm tstruct;
    char buf[80];
    tstruct = *localtime(&now);
    strftime(buf, sizeof(buf), "%Y%m%d%H%M%S", &tstruct);
    
    return buf;
}

void writeToFile(const std::string &fileName, const std::string &str) {
    std::ofstream file;
    file.open(fileName, std::ios_base::app);
    file << str + '\n';
    file.close();
}

void writeMultipleStrToFile(const std::string &fileName, std::vector<std::string> vector) {
    std::ofstream file;
    file.open(fileName);

    for (auto &str: vector) {
        file << str + '\n';
    }

    file.close();
}

void deleteAFile(const std::string &fileName) {
    const int success = std::remove(fileName.c_str());
    if (success == 0) {
        std::cout << "Successfully deleted " << fileName << std::endl;
    } 
    
    else {
        std::cout << "Failed to delete " << fileName << std::endl;
    }
}

void renameAFile(const std::string &oldName, const std::string &newName) {
    std::rename(oldName.c_str(), newName.c_str());
}

bool checkIfFileExists(const char *file) {
    std::ifstream f(file);
    return f.good();
}

void quitGame() {
    std::cout << std::endl;
    std::cout << "Quitting the game. See you again!" << std::endl;

    // Quit
    exit(0);
}


void save(const std::string &fileName, std::vector<std::string> vector) {
    // Write All Game Inputs to a Save File
    writeMultipleStrToFile(fileName, vector);
}


void shuffleString(std::string & str, std::default_random_engine & engine){
    std::uniform_int_distribution<int> distribution(0, str.size() - 1);
    int value = -1;
    char temp;
    for (size_t i = 0; i < str.size(); ++i) {
        value = distribution(engine);
        // Save current pos
        temp = str[i];
        // Swap current pos value with another
        str[i] = str[value];
        str[value] = temp;
    }
}

bool isRowFull(int row, Player *player) {
    int full = true;
    if (row != 0) {
        for (int i = 0; i < row; ++i) {
            if (player->getUnlaidRow()[row - 1][i].getName() == '.') {
                full = false;
                // Break loop
                i = row;
            }
        }
    } else {
        full = false;
    }
    return full;
}

std::string getGridColor(int row, Player *player) {
    std::string result;
    for (int i = 0; i < 5; ++i) {
        result += player->getGrid()[row - 1][i].getName();
    }
    return result;
}

char getColorOfaRow(int row, Player *player) {
    return player->getUnlaidRow()[row - 1][0].getName();
}

void printEndErrorMessage(std::vector<std::string> &errors) {
    std::cout << "Invalid Input!" << std::endl;
    std::cout << "Error(s): " << std::endl;

    for (auto &error : errors) {
        std::cout << "- " << error << std::endl;
    }
    std::cout << "Please try again " << std::endl;
    std::cout << std::endl;
}

bool tileExistsInAFactory(const char & tile, int factory, Tile** factories, std::vector<Tile*> center){
    bool exist = false;

    //Search Centre Factory first
    if (factory == 0) {
        for (size_t i = 0; i < center.size(); ++i) {
            if (center[i]->getName() == tile) {
                exist = true;
                // Break loop
                i = center.size();
            }
        }
    } else if (factory > FIRST_FACTORY && factory < LAST_FACTORY + 1) {
        for (int i = 0; i < FACTORY_SIZE; ++i) {
            if (factories[factory - 1][i].getName() == tile) {
                exist = true;
                // Break loop
                i = FACTORY_SIZE;
            }
        }
    }
    return exist;
}

std::vector<std::string> checkInput(std::string input, Player *player, const std::string & validChars, Tile** factories, std::vector<Tile*> center) {
    // a vector that contains all error messages
    std::vector<std::string> result;

    // Split input string into pieces
    std::vector<std::string> inputArr = splitString(input, WHITESPACE);

    // Valid color characters
    std::string colors = validChars;


    // Check if save argument number was entered
    if (inputArr.size() == 2) {
        // Check for save command
        if (inputArr[0] != "save") {
            result.push_back("Invalid input. Correct input = save. Your input = " + inputArr[0]);
        }
    }
        // Check if turn argument number was entered
    else if (inputArr.size() == 4) {
        // Check for turn command
        if (inputArr[0] != "turn") {
            result.push_back("Invalid input. Correct input = turn. Your input = " + inputArr[0]);
        }

        // Check Factory Number entered
        try {
            // Convert input from string to int
            int factory = std::stoi(inputArr[1]);
            int row = std::stoi(inputArr[3]);
            if (factory < FIRST_FACTORY || factory > LAST_FACTORY) {
                result.push_back("<factory> must be a number between 0 and 5");
            } else if (isAFactoryEmpty(factory, factories)) {
                result.push_back("The factory you have entered is empty. Your input = "
                                 + inputArr[1]);
            }

            if (row < FIRST_STORAGE_ROW || row > LAST_STORAGE_ROW) {
                result.push_back("<row> must be a number between 0 and 5");
            } else {
                if (isRowFull(row, player)) {
                    result.push_back("Illegal move. Chosen row is full");
                }
                if (row != 0) {
                    size_t grid = getGridColor(row, player).find(inputArr[2]);
                    if (grid != std::string::npos) {
                        result.push_back("Illegal move. The grid has already had this color");
                    }

                    if (getColorOfaRow(row, player) != '.' && (getColorOfaRow(row, player) != inputArr[2][0])) {
                        result.push_back("Illegal move. All tiles in the same row must have the same color");
                    }
                }
            }

            // Check Colour entered
            size_t correctColor = colors.find(inputArr[2]);
            if (correctColor == std::string::npos) {
                result.push_back("<color> must be one of these values: R, Y, B, L, U");
            } else if (!tileExistsInAFactory(inputArr[2][0], factory, factories, center)) {
                result.push_back("The tile you have chosen does not exist in the chosen factory.");
            }

        } //Check other exceptions
        catch (std::exception const &e) {
            result.push_back("<factory> must be a number between 0 and 5");
            result.push_back("<row> must be a number between 0 and 5");
        }

    } else {
        result.push_back(
                "Wrong number of arguments or arguments are not separated by whitespace or excessive whitespaces. "
                "Your input = " + input);
    }
    return result;
}


bool isAFactoryEmpty(int factory, Tile ** factories) {
    // Initialize a counter
    int count = 0;

    if (factory != 0) {
        // Loop through the chosen factory
        for (int i = 0; i < FACTORY_SIZE; ++i) {
            if (factories[factory - 1][i].getName() == WHITESPACE) {
                count++;
            }
        }
    }
    return count == FACTORY_SIZE;
}

void printInstructions() {
    std::cout << "To Play   : turn <factory> <color> <row>" << std::endl;
    std::cout << "To Save   : save <filename>" << std::endl;
    std::cout << "To Discard: turn <factory> <color> 0" << std::endl;
}