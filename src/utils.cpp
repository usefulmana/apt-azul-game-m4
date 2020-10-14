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