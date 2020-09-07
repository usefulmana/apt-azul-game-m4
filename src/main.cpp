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

void quitGame();

std::vector<Player *> getPlayers();

bool isNameValid(const std::string &name);

int main() {
    showMenu();

    // Test script. Delete before submission
//    std::string test = "turn 0 R 3";
//    std::vector<std::string> errors = checkInput(test);
//    for (auto & str: errors){
//        std::cout << str << std::endl;
//    }
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

    // Object Initialization
    Game *game = new Game();
    game->addPlayers(getPlayers());

    std::cout << "Let's Play!" << std::endl;
    std::cout << std::endl;



    // Variable to store turn
    int round = 1;

    while (round <= MAX_GAME_ROUNDS) {
        std::cout << "=== Start Round " << round << " ===" << std::endl;
        for (auto &player: game->getPlayers()) {
            std::cout << "TURN FOR PLAYER: " << player->getName() << std::endl;
            std::cout << "Factories:" << std::endl;
            // TODO print factories
            std::cout << std::endl;
            std::cout << "Mosaic for " << player->getName() << ":" << std::endl;
            // TODO print mosaic
            // TODO print broken

            bool validInput = false;


            while (!validInput) {

                // Get user input
                std::string input;

                std::cout << "Your input (turn <factory> <color> <row>):" << std::endl;
                std::cout << "> ";

                std::getline(std::cin >> std::ws, input);

                std::vector<std::string> errors = checkInput(input);

                // Check end of file
                if (errors.capacity() == 0) {
                    // TODO execute the command
                    std::cout << "Turn successful." << std::endl;
                    validInput = true;
                } else {
                    std::cout << "Invalid Input!" << std::endl;
                    std::cout << "Error(s): " << std::endl;

                    for (auto & str : errors){
                        std::cout << "- " << str << std::endl;
                    }

                    std::cout << "Please try again " << std::endl;
                    std::cout << std::endl;
                }
            }


            std::cout << std::endl;
        }

        round++;
    }

    std::cout << "=== Game Over ===" << std::endl;
    std::cout << "=== Score Boards ===" << std::endl;
    // TODO RESULT

    // delete
    delete game;
}

/**
 * This functional will load an Azul game from a file
 */
void loadGame() {
    std::cout << "Loading Game" << std::endl;
}

/**
 * Quit the game by modifying the "quit" value
 * @param quit : state of the menu
 */
void quitGame() {
    std::cout << std::endl;
    std::cout << "Quitting the game. See you again!" << std::endl;
    exit(0);
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
std::vector<Player *> getPlayers() {
    // A vector to store player objects
    std::vector<Player *> players;

    // Player counter
    int playerCount = 1;

    // End loop when num of players exceeds the ceiling
    while (playerCount < NUM_OF_PLAYERS + 1) {
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

