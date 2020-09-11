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
    }

    // Add first tile to center and fill factories
    addFirstTileToCenter();
    fillFactories();

    // Variable to store round
    int round = 1;

    // While game hasn't finished last round
    while (round <= MAX_GAME_ROUNDS) {
        std::cout << "=== Start Round " << round << " ===" << std::endl;
//        std::cout << areFactoriesEmpty() << std::endl;
        // End round if center and factories r empty
        while (!isCenterEmpty() && !areFactoriesEmpty()){
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

                // Instruction help
                std::cout << "To Play: turn <factory> <color> <row>" << std::endl;
                std::cout << "To Save: save <filename>" << std::endl;

                // Exit if Valid Input Entered
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
                            execute(input, player);
                            // Add input to input vector
                            savedInputs.push_back(input);
                            std::cout << "Turn successful." << std::endl;
                            std::cout << std::endl;
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

                        // Notify users of errors
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
        }
        // Next Round
        round++;
    }
}

/**
 * Fill tile bag automatically in a pre-determined order
 */
void Game::setTileBagAutomatically() {
    // Initialize the tile bag
    tileBag = new LinkedList<Tile *>();
    // Add first tile to tile bag
    tileBag->addBack(new Tile('F'));

    // 10R, 0B, 5Y, 5U, 5L
    for (int i = 0; i < 5; ++i) {
        tileBag->addBack(new Tile('R'));
        tileBag->addBack(new Tile('Y'));
        tileBag->addBack(new Tile('U'));
        tileBag->addBack(new Tile('L'));
        tileBag->addBack(new Tile('R'));
    }
    // 0R, 10B, 5Y, 0U, 5L
    for (int i = 0; i < 5; ++i) {
        tileBag->addBack(new Tile('B'));
        tileBag->addBack(new Tile('Y'));
        tileBag->addBack(new Tile('B'));
        tileBag->addBack(new Tile('L'));
    }

    // 10R, 10B, 5Y, 10U, 0L
    for (int i = 0; i < 5; ++i) {
        tileBag->addBack(new Tile('R'));
        tileBag->addBack(new Tile('Y'));
        tileBag->addBack(new Tile('U'));
        tileBag->addBack(new Tile('U'));
        tileBag->addBack(new Tile('R'));
        tileBag->addBack(new Tile('B'));
        tileBag->addBack(new Tile('B'));
    }
    // 0R, 0B, 5Y, 5U, 10L
    for (int i = 0; i < 5; ++i) {
        tileBag->addBack(new Tile('L'));
        tileBag->addBack(new Tile('Y'));
        tileBag->addBack(new Tile('U'));
        tileBag->addBack(new Tile('L'));
    }
}

/**
 * Parse a string to get fill the tile bag wil tiles
 * @param line : string to be parsed
 */
void Game::setTileBagFromString(const std::string &line) {
    tileBag = new LinkedList<Tile *>();
    for (size_t i = 0; i < line.length(); ++i) {
        tileBag->addBack(new Tile(line[i]));
    }
}

/**
 * return the tile bag
 * @return : return the tile bag
 */
LinkedList<Tile *> * Game::getTileBag(){
    return tileBag;
}

/**
 * Fill factories with tiles from the tile bag
 */
void Game::fillFactories() {
    for (int i = 0; i < NUM_OF_FACTORIES; ++i) {
        for (int j = 0; j < FACTORY_SIZE; ++j) {
            factories[i][j] = *new Tile(tileBag->get(0)->getName());
            tileBag->popFront();
        }
    }
}

/**
 * Print factories to console
 */
void Game::printFactories() {

    // Print center
    std::cout << "0: ";
    for (size_t i = 0; i < center.size(); ++i) {
        std::cout << center[i]->getName() << ' ';
    }
    std::cout << std::endl;
    // Print factories
    for (int i = 0; i < NUM_OF_FACTORIES; ++i) {
        std::cout << i + 1 << ": ";
        for (int j = 0; j < FACTORY_SIZE; ++j) {
            std::cout << factories[i][j].getName() << ' ';
        }
        std::cout << std::endl;
    }
}

/**
 * Add first tile to Center
 */
void Game::addFirstTileToCenter() {
    center.push_back(new Tile(tileBag->get(0)->getName()));
    tileBag->popFront();
}

/**
 * Check if the center factory is empty
 * @return true if empty, false if not
 */
bool Game::isCenterEmpty() {
    return  center.empty();
}

/**
 * Check if the factories are empty
 * @return true if empty, false if not;
 */
bool Game::areFactoriesEmpty() {
    int count = 0;
    for (int i = 0; i < NUM_OF_FACTORIES; ++i) {
        for (int j = 0; j < FACTORY_SIZE; ++j) {
            if (factories[i][j].getName() == '\0'){
                count++;
            }
        }
    }
    return count == 16;
}

void Game::execute(const std::string &command, Player * player) {

}

bool Game::isAFactoryEmpty(int factory) {
    int count = 0;
    for (int i = 0; i < FACTORY_SIZE; ++i) {
        if (factories[factory][i].getName() == '\0'){
            count++;
        }
    }
    return count == 4;
}

/**
 * Checking player's input
 * @param input : input string to be checked
 * @return : a vector containing errors of the player's input
 */
std::vector<std::string> Game::checkInput(std::string input) {
    std::vector<std::string> result;
    std::vector<std::string> inputArr = splitString(input, ' ');
    std::string colors = "RYBLUF.";


    // Check if entered num of args for save
    if (inputArr.size() == 2){
        // Check for save command
        if (inputArr[0] != "save") {
            result.push_back("Invalid input. Correct input = save. Your input = " + inputArr[0]);
        }
    }
        // Check if entered num of args for turn
    else if (inputArr.size() == 4){
        // Check for turn command
        if (inputArr[0] != "turn") {
            result.push_back("Invalid input. Correct input = turn. Your input = " + inputArr[0]);
        }

        // Check Inputted Factory Number
        try {
            // Convert input from string to int
            int factory = std::stoi(inputArr[1]);
            if (factory < FIRST_FACTORY || factory > LAST_FACTORY) {
                result.push_back("Invalid Factory #. Please enter an integer number for factories (0->5). Your input = "
                                 + inputArr[1]);
            }

            if (isAFactoryEmpty(factory)){
                result.push_back("The factory you have entered is empty. Your input = "
                                 + inputArr[1]);
            }
            // Check Inputted Colour
            size_t correctColor = colors.find(inputArr[2]);
            if (correctColor == std::string::npos) {
                result.push_back("Invalid color. Color should be R,Y,B,L,U. Your input: " + inputArr[2]);
            }
            else if (!tileExistsInAFactory(inputArr[2][0], factory)){
                result.push_back("The tile you have chosen does not exist in the chosen factory.");
            }
        }
        catch (std::exception const &e) {
            result.push_back(
                    "Invalid factory #. Please enter an integer number for factories (0->5). Your input = " +
                    inputArr[1]);
        }

        // Check Inputted Storage Row
        try {
            // Convert input from string to int
            int storageRow = std::stoi(inputArr[3]);
            if (storageRow < FIRST_STORAGE_ROW || storageRow > LAST_STORAGE_ROW) {
                result.push_back(
                        "Invalid Storage #. Please enter an integer number for storage number (1->5). Your input = " + inputArr[3]);
            }

            // TODO Check if move is valid
        }
        catch (std::exception const &e) {
            result.push_back(
                    "Invalid Storage #. Please enter an integer number for storage number (1->5). Your input = " + inputArr[3]);
        }


    } else {
        result.push_back(
                "Wrong number of arguments or arguments are not separated by space or excessive whitespaces. "
                "Your input = " + input);
    }

    return result;
}

bool Game::tileExistsInAFactory(const char &tile, int factory) {
    bool exist = false;
    for (int i = 0; i < FACTORY_SIZE; ++i) {
        if (factories[factory][i].getName() == tile){
            exist = true;
        }
    }
    return exist;
}
