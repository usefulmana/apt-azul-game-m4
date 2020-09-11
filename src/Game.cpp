#include "Game.h"


Game::Game() {
    // Declare factories
    factories = new Tile *[NUM_OF_FACTORIES];
    for (int i = 0; i < NUM_OF_FACTORIES; ++i) {
        factories[i] = new Tile[FACTORY_SIZE];
    }


}

Game::~Game() {
    // Delete players
    for (auto &player: players) {
        delete player;
    }

    // Delete factories
    for (int i = 0; i < NUM_OF_FACTORIES; ++i) {
        delete factories[i];
    }
    delete[] factories;

    // Delete tile bag;
    delete tileBag;
}

void Game::addPlayers(std::vector<Player *> p) {

    // Add Player to back of Vector
    for(auto & player: p){

        players.push_back(player);
    }
}

std::vector<Player *> Game::getPlayers() {
    return players;
}

void Game::save(const std::string &fileName, std::vector<std::string> vector) {
    // Write All Game Inputs to a Save File
    writeMultipleStrToFile(fileName, vector);
}

void Game::play() {


    //Add tile Bag to input vector
    std::string bag;
    for (int i = 0; i < 101; ++i) {
        bag += tileBag->get(i)->getName();
    }
    savedInputs.push_back(bag);

    // Add players' names to input vector
    for (auto &player: players) {
        savedInputs.push_back(player->getName());

        // Add 'First' tile to first player's broken row
//        if (tileBag->get(0)->getName() == 'F'){
//            player->addToBrokenRow(*new Tile(tileBag->get(0)->getName()));
//            tileBag->popFront();
//        }
    }

    // TODO Fill Factories and center
    addFirstTileToCenter();
    fillFactories();

    // Variable to store turn
    int round = 1;

    // While game hasn't finished last round
    while (round <= MAX_GAME_ROUNDS) {
        std::cout << "=== Start Round " << round << " ===" << std::endl;

        // For all players
        for (auto &player: players) {
            std::cout << "TURN FOR PLAYER: " << player->getName() << std::endl;
            std::cout << "Factories:" << std::endl;
            printFactories();
            std::cout << std::endl;
            std::cout << "Mosaic for " << player->getName() << ":" << std::endl;
            player->printMosaic();
            player->printBrokenRow();
            std::cout << std::endl;

            bool validInput = false;

            std::cout << "To Play: turn <factory> <color> <row>" << std::endl;
            std::cout << "To Save: save <filename>" << std::endl;

            // Exit if Invalid Input Entered
            while (!validInput) {

                // Get user input
                std::string input;

                std::cout << "Your input:" << std::endl;
                std::cout << "> ";

                // Stores console input without leading whitespace
                std::getline(std::cin >> std::ws, input);


                // Check EOF Character (^D) 
                if (std::cin.eof()){
                    quitGame();
                }

                // Check for errors
                std::vector<std::string> errors = checkInput(input);

                // Check if there is any error
                if (errors.capacity() == 0) {

                    // Returns substring of first 4 characters in input
                    if (input.substr(0, 4) == "turn"){
                        // TODO execute the command
                        
                        // Add input to input vector
                        savedInputs.push_back(input);
                        std::cout << "Turn successful." << std::endl;

                        // End input loop
                        validInput = true;

                    }
                    else if (input.substr(0, 4) == "save"){
                        // Find position of first whitespace 
                        int pos = input.find(' ');

                        // Add datetime to the end of the file name to avoid collision

                        // Return substring of everything following the whitespace
                        std::string fileName = input.substr(pos + 1);

                        // Save game
                        save(fileName, savedInputs);

                        std::cout << "Saved to " << fileName << std::endl;
                    }

                } else {
                    std::cout << "Invalid Input!" << std::endl;
                    std::cout << "Error(s): " << std::endl;

                    for (auto &error : errors) {
                        std::cout << "- " << error << std::endl;
                    }
                    std::cout << "Please try again " << std::endl;
                    std::cout << std::endl;
                }
            }
            std::cout << std::endl;
        }
        // Next Round
        round++;
    }
}

void Game::setTileBagAutomatically() {
    tileBag = new LinkedList<Tile *>();
    tileBag->addBack(new Tile('F'));
    for (int i = 0; i < 20; ++i) {
        tileBag->addBack(new Tile('R'));
        tileBag->addBack(new Tile('B'));
        tileBag->addBack(new Tile('Y'));
        tileBag->addBack(new Tile('U'));
        tileBag->addBack(new Tile('L'));
    }
}

void Game::setTileBagFromString(const std::string &line) {
    tileBag = new LinkedList<Tile *>();
    for (size_t i = 0; i < line.length(); ++i) {
        tileBag->addBack(new Tile(line[i]));
    }
}

LinkedList<Tile *> * Game::getTileBag(){
    return tileBag;
}

void Game::fillFactories() {
    for (int i = 0; i < NUM_OF_FACTORIES; ++i) {
        for (int j = 0; j < FACTORY_SIZE; ++j) {
            factories[i][j] = *new Tile(tileBag->get(0)->getName());
            tileBag->popFront();
        }
    }
}

void Game::printFactories() {
    std::cout << "0: ";
    for (size_t i = 0; i < center.size(); ++i) {
        std::cout << center[i]->getName() << ' ';
    }
    std::cout << std::endl;

    for (int i = 0; i < NUM_OF_FACTORIES; ++i) {
        std::cout << i + 1 << ": ";
        for (int j = 0; j < FACTORY_SIZE; ++j) {
            std::cout << factories[i][j].getName() << ' ';
        }
        std::cout << std::endl;
    }
}

void Game::addFirstTileToCenter() {
    center.push_back(new Tile(tileBag->get(0)->getName()));
    tileBag->popFront();
}
