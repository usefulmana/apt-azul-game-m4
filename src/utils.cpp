#include "utils.h"
#include <sstream>
#include <iostream>
#include "Game.h"

std::vector<std::string> splitString(std::string str, char delimiter) {
    std::vector<std::string> result;
    std::stringstream ss(str);
    std::string temp;
    while (std::getline(ss, temp, delimiter)){
        result.push_back(temp);
    }
    return result;
}

std::vector<std::string> checkInput(std::string input) {
    std::vector<std::string> result;
    std::vector<std::string> inputArr = splitString(input, ' ');
    std::string colors = "RYBLU";

    // Check num of args


    if (inputArr.size() != 4){
        result.push_back("Wrong number of arguments or arguments are not separated by space. Your input = " + input);
    }
    else {
        // Check turn
        if (inputArr[0] != "turn") {
            result.push_back("Invalid input. Correct input = turn. Your input = " + inputArr[0]);
        }

        // Check Factory
        try {
            int factory = std::stoi(inputArr[1]);
            if (factory < 0 || factory > 5) {
                result.push_back("Invalid Factory #. Please enter an integer number for factories (0->5). Your input = "
                                 + inputArr[1]);
            }
        }
        catch (std::exception const &e) {
            result.push_back(
                    "Invalid factory #. Please enter an integer number for factories (0->5). Your input = " + inputArr[1]);
        }

        // Check Color
        size_t correctColor = colors.find(inputArr[2]);
        if (correctColor == std::string::npos){
            result.push_back("Invalid color. Color should be R,Y,B,L,U. Your input: " + inputArr[2]);
        }

        // TODO Check move validity
    }

    return result;
}
