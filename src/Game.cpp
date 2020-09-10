#include "Game.h"
#include "utils.h"
#include <iostream>
#include "Types.h"

Game::Game() {

    // Declare factories
    factories = new Tile*[NUM_OF_FACTORIES];
    for (int i = 0; i < NUM_OF_FACTORIES; ++i) {
        factories[i] = new Tile[FACTORY_SIZE];
    }

    // TODO Fill Factories
    // TODO Declare and Fill Tile Bag

}

Game::~Game() {
    // Delete players
    for(auto & player: players){
        delete player;
    }

    // Delete factories
    for (int i = 0; i < NUM_OF_FACTORIES; ++i) {
        delete factories[i];
    }
    delete [] factories;
}

void Game::addPlayers(std::vector<Player *> p) {
    for(auto & player: p){
        players.push_back(player);
    }
}

std::vector<Player *> Game::getPlayers() {
    return players;
}

void Game::save(const std::string &fileName, std::vector<std::string> vector) {
    writeMultipleStrToFile(fileName, vector);
}

void Game::play() {

    // TODO Add tile Bag to input vector
    // Add players' names to file
    for (auto & player: players){
        savedInputs.push_back(player->getName());
    }

    // Variable to store turn
    int round = 1;

    while (round <= MAX_GAME_ROUNDS) {
        std::cout << "=== Start Round " << round << " ===" << std::endl;
        for (auto &player: players) {
            std::cout << "TURN FOR PLAYER: " << player->getName() << std::endl;
            std::cout << "Factories:" << std::endl;
            // TODO print factories
            std::cout << std::endl;
            std::cout << "Mosaic for " << player->getName() << ":" << std::endl;
            // TODO print mosaic
            // TODO print broken

            bool validInput = false;

            std::cout << "To Play: turn <factory> <color> <row>" << std::endl;
            std::cout << "To Save: save <filename>" << std::endl;

            while (!validInput) {

                // Get user input
                std::string input;

                std::cout << "Your input:" << std::endl;
                std::cout << "> ";

                std::getline(std::cin >> std::ws, input);

                // Check EOF
                if (std::cin.eof()){
                    quitGame();
                }

                // Check for errors
                std::vector<std::string> errors = checkInput(input);

                // Check if there is any error
                if (errors.capacity() == 0) {

                    if (input.substr(0, 4) == "turn"){
                        // TODO execute the command
                        // Add input to input vector
                        savedInputs.push_back(input);
                        std::cout << "Turn successful." << std::endl;

                        // End input loop
                        validInput = true;
                    }
                    else if (input.substr(0, 4) == "save"){
                        int pos = input.find(' ');

                        // Add datetime to the end of the file name to avoid collision
                        std::string fileName = input.substr(pos + 1);

                        // Save game
                        save(fileName, savedInputs);

                        std::cout << "Saved to " << fileName << std::endl;

                    }

                } else {
                    std::cout << "Invalid Input!" << std::endl;
                    std::cout << "Error(s): " << std::endl;

                    for (auto & error : errors){
                        std::cout << "- " << error << std::endl;
                    }
                    std::cout << "Please try again " << std::endl;
                    std::cout << std::endl;
                }
            }
            std::cout << std::endl;
        }
        round++;
    }
}
