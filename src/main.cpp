#include <iostream>
#include <limits>
#include <vector>
#include <string>
#include "Types.h"

void showMenu();
void showCredits();
void playGame();
void loadGame();
void quitGame(bool & quit);
bool isNameValid(const std::string & name);

int main() {
    showMenu();
    return EXIT_SUCCESS;
}

void showMenu(){
    std::cout << "Welcome to Azul!" << std::endl;
    std::cout << "-----------------------" << std::endl;
    std::cout << std::endl;

    bool quit = false;

    while (!quit){

        std::cout << "Menu" << std::endl;
        std::cout << "-----" << std::endl;
        std::cout << "1. New Game" << std::endl;
        std::cout << "2. Load Game" << std::endl;
        std::cout << "3. Credits" << std::endl;
        std::cout << "4. Quit" << std::endl;

        std::cout << std::endl;
        std::cout << "> " ;
        int choice;
        std::cin >> choice;

        if (std::cin.eof()){
            quitGame(quit);
        }
        else if (std::cin.fail() || choice < 0 || choice > 4){
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Wrong Input. Please enter an integer number from 1 to 4" << std::endl;
            std::cout << std::endl;
        }
        else {
            if (choice == 1){
                playGame();
            }
            else if (choice == 2){
                loadGame();
            }
            else if (choice == 3){
                showCredits();
            }
            else if (choice == 4){
                quitGame(quit);
            }
        }
    }
}

/**
 * Display the information of the authors of this program
 */
void showCredits(){
    std::cout << "--------------------------" << std::endl;
    std::cout << "Name: Anh Nguyen" << std::endl;
    std::cout << "Student ID: s3616128" << std::endl;
    std::cout << "Email: s3616128@rmit.edu.vn" << std::endl;
    std::cout << "--------------------------" << std::endl;
    std::cout << std::endl;
    std::cout << "--------------------------" << std::endl;
    std::cout << "Name: Mitchell Gust" << std::endl;
    std::cout << "Student ID: s3782095" << std::endl;
    std::cout << "Email: s3782095@student.rmit.edu.au" << std::endl;
    std::cout << "--------------------------" << std::endl;
    std::cout << std::endl;
    std::cout << "--------------------------" << std::endl;
    std::cout << "Name: Ruby Rio" << std::endl;
    std::cout << "Student ID: s3786695" << std::endl;
    std::cout << "Email: s3786695@student.rmit.edu.au" << std::endl;
    std::cout << "--------------------------" << std::endl;
    std::cout << std::endl;
}

/**
 * This functional will initialize an Azul game
 */
void playGame(){
    std::cout << "Starting a new Azul game" << std::endl;
    std::cout << std::endl;

    std::vector<std::string> playerNames;

    int playerCount = 1;

    while (playerCount < NUM_OF_PLAYERS + 1){
        std::string name;
        std::cout << "Enter a name for player " << playerCount << std::endl;
        std::cout << "> ";
        std::cin >> name;
        std::cout << std::endl;

        if (std::cin.eof()){
            std::cout << "Quitting the game. See you again" << std::endl;
            exit(0);
        }
        else if (isNameValid(name)){
            playerCount++;
            playerNames.push_back(name);
        }
        else {
            std::cout << "Invalid name. Please try again" << std::endl;
        }
    }

    // TODO initialize player objects here
    for (size_t i = 0; i < playerNames.size(); ++i) {
        std::cout << "Player " << i + 1 << " : " << playerNames[i] << std::endl;
    }

    std::cout << "Let's Play!" << std::endl;
    std::cout << std::endl;
}

/**
 * This functional will load an Azul game from a file
 */
void loadGame(){
    std::cout << "Loading Game" << std::endl;
}

/**
 * Quit the game by modifying the "quit" value
 * @param quit : state of the menu
 */
void quitGame(bool & quit){
    std::cout << "Quitting the game. See you again!" << std::endl;
    quit = true;
}

bool isNameValid(const std::string & name){
    bool valid = true;
    if (name.empty()){
        valid = false;
    }
    return valid;
}