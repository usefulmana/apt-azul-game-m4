#include <iostream>
#include <limits>
#include <vector>
#include <string>
#include "Types.h"
#include "Game.h"
#include "Player.h"
#include "utils.h"

[[noreturn]] void showMenu();

void showCredits();

void playGame();

void loadGame();

std::vector<Player *> createPlayersFromUserInput();

bool isNameValid(const std::string &name);

void engageTestMode(char* fileName);

int main(int argc, char ** argv) {
    // Check num of argument
    if (argc == 1){
        // No additional arg => show menu
        showMenu();
    }
    else if (argc == 3){
        // 2 additional args => test mode
        const std::string flag = "-t";
        
        // If second argument is test flag
        if (argv[1] == flag){
            // If File Exists
            if (checkIfFileExists(argv[2])){
                engageTestMode(argv[2]);
            }
            else {
                std::cout << "No such file exists!" << std::endl;
            }
        }
        else {
            std::cout << "Wrong flag" << std::endl;
        }
    }
    else {
        std::cout << "Invalid number of arguments" << std::endl;
        std::cout << "./azul to run" << std::endl;
        std::cout << "./azul -t <testfile> to engage test mode" << std::endl;
    }
    return EXIT_SUCCESS;
}

[[noreturn]] void showMenu() {
    // Display welcome message
    std::cout << "Welcome to Azul!" << std::endl;
    std::cout << "-----------------------" << std::endl;
    std::cout << std::endl;


    while (true) {
        // Display menu
        std::cout << "Menu" << std::endl;
        std::cout << "-----" << std::endl;
        std::cout << "1. New Game" << std::endl;
        std::cout << "2. Load Game" << std::endl;
        std::cout << "3. Credits" << std::endl;
        std::cout << "4. Quit" << std::endl;

        std::cout << std::endl;
        std::cout << "> ";

        // Getting user input
        int choice;
        std::cin >> choice;

        // Check end of file
        if (std::cin.eof()) {
            quitGame();
        }

        // Check fail conditions
        else if (std::cin.fail() || choice < 0 || choice > 4) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Wrong Input. Please enter an integer number from 1 to 4" << std::endl;
            std::cout << std::endl;

        } else {
            if (choice == 1) {
                playGame();
            } else if (choice == 2) {
                loadGame();
            } else if (choice == 3) {
                showCredits();
            } else if (choice == 4) {
                quitGame();
            }
        }
    }
}

/**
 * Display the information of the authors of this program
 */
void showCredits() {
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
void playGame() {
    std::cout << std::endl;
    std::cout << "Starting a new Azul game" << std::endl;
    std::cout << std::endl;

    // Game Initialization
    Game *game = new Game();
    game->addPlayers(createPlayersFromUserInput());
    game->setTileBagAutomatically();

    std::cout << "Let's Play!" << std::endl;
    std::cout << std::endl;

    // Play the game
    game->play();

    std::cout << "=== Game Over ===" << std::endl;
    std::cout << "=== Scoreboard ===" << std::endl;
    // Print Scores
    for (int i = 0; i < game->getPlayers().size(); ++i) {
        std::cout << "Player " << game->getPlayers()[i]->getName() << ": " << game->getPlayers()[i]->getScore() << std::endl;
    }


    // delete objects
    // delete game;

}

/**
 * This functional will load an Azul game from a file
 */
void loadGame() {
    std::cout << "Loading Game" << std::endl;
}

/**
 * Check if a player's name is valid
 * @param name
 * @return valid: true if valid, false if invalid
 */
bool isNameValid(const std::string &name) {
    bool valid = true;
    if (name.empty()) {
        valid = false;
    }
    return valid;
}

/**
 * Create a player vector based on stdin
 * @return a vector of player objects
 */
std::vector<Player *> createPlayersFromUserInput() {
    // A vector to store player objects
    std::vector<Player *> players;

    // Player counter
    int playerCount = 1;

    // End loop when num of players exceeds the ceiling
    while (playerCount <= NUM_OF_PLAYERS) {
        std::string name;
        std::cout << "Enter a name for player " << playerCount << std::endl;
        std::cout << "> ";
        std::cin >> name;
        std::cout << std::endl;

        // Check end of file
        if (std::cin.eof()) {
            quitGame();
        }
        // Validate input
        else if (isNameValid(name)) {
            // Increase count by one
            playerCount++;
            // Initialize and add player object to the vector
            players.push_back(new Player(name));
        } else {
            std::cout << "Invalid name. Please try again" << std::endl;
        }
    }

    return players;
}

void engageTestMode(char* fileName){
    std::cout << "Engaged Test Mode" << std::endl;
}