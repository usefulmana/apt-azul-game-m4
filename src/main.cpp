#include <iostream>
#include <limits>
#include <vector>
#include <string>
#include "Types.h"
#include "LinkedList.h"

[[noreturn]] void showMenu();
void showCredits();
void playGame();
void loadGame();
void quitGame();
bool isNameValid(const std::string & name);

int main() {
    
    showMenu();
    /*auto* linkedList =  new LinkedList<int>();
    
    linkedList->addBack(3);
    linkedList->addBack(5);
    linkedList->addBack(7);
    linkedList->addFront(2);
    linkedList -> popFront();
    for (int i = 0; i < linkedList->getLength(); ++i) {
        std::cout << linkedList->get(i) << std::endl;
    }

    delete linkedList;*/

    return EXIT_SUCCESS;
}

[[noreturn]] void showMenu(){
    // Display welcome message
    std::cout << "Welcome to Azul!" << std::endl;
    std::cout << "-----------------------" << std::endl;
    std::cout << std::endl;


    while (true){
        // Display menu
        std::cout << "Menu" << std::endl;
        std::cout << "-----" << std::endl;
        std::cout << "1. New Game" << std::endl;
        std::cout << "2. Load Game" << std::endl;
        std::cout << "3. Credits" << std::endl;
        std::cout << "4. Quit" << std::endl;

        std::cout << std::endl;
        std::cout << "> " ;

        // Getting user input
        int choice;
        std::cin >> choice;

        // Check end of file
        if (std::cin.eof()){
            quitGame();
        }
        // Check fail conditions
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
                quitGame();
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

    // A vector to store players' names
    std::vector<std::string> playerNames;

    // Player counter
    int playerCount = 1;

    // End loop when num of players exceeds the ceiling
    while (playerCount < NUM_OF_PLAYERS + 1){
        std::string name;
        std::cout << "Enter a name for player " << playerCount << std::endl;
        std::cout << "> ";
        std::cin >> name;
        std::cout << std::endl;

        // Check end of file
        if (std::cin.eof()){
            quitGame();
        }
        // Validate input
        else if (isNameValid(name)){
            // Increase count by one
            playerCount++;
            // Add name to the name vector
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
void quitGame(){
    std::cout << std::endl;
    std::cout << "Quitting the game. See you again!" << std::endl;
    exit(0);
}

/**
 * Check if a player's name is valid
 * @param name
 * @return valid: true if valid, false if invalid
 */
bool isNameValid(const std::string & name){
    bool valid = true;
    if (name.empty()){
        valid = false;
    }
    return valid;
}