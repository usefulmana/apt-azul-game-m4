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

    //FILL TILE BAG
    std::string bag;
    for (int i = 0; i < 101; ++i) {
        bag += tileBag->get(i)->getName();
    }
    savedInputs.push_back(bag);

    //ADD PLAYERS
    for (auto &player: players) {
        savedInputs.push_back(player->getName());
    }

    //ADD FIRST TILE
    addFirstTileToCenter();

    // ADD FACTORIES
    fillFactories();

    // Variable to store round
    int round = 1;

    // While game hasn't finished last round
    while (round <= MAX_GAME_ROUNDS) {

        std::cout << "=== Start Round " << round << " ===" << std::endl;

        // End round if center and factories r empty
        while (!isCenterEmpty() && !areFactoriesEmpty()){

            for (auto &player: players) {

                //PRINT PLAYER NAME
                std::cout << "TURN FOR PLAYER: " << player->getName() << std::endl;

                //DISPLAY FACTORIES
                std::cout << "Factories:" << std::endl;
                printFactories();
                std::cout << std::endl;

                //DISPLAY MOSAIC
                std::cout << "Mosaic for " << player->getName() << ":" << std::endl;
                player->printMosaic();
                player->printBrokenRow();
                std::cout << std::endl;

                bool validInput = false;

                // INSTRUCTIONS
                std::cout << "To Play: turn <factory> <color> <row>" << std::endl;
                std::cout << "To Save: save <filename>" << std::endl;

                //IF THE ENTERED INSTRUCTION IS VALID
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
                    std::vector<std::string> errors = checkInput(input, player);

                    // Check if there is any error
                  //  if (errors.capacity() == 0) {

                        // Returns substring of first 4 characters in input
                        if (input.substr(0, 4) == "turn"){

                            execute(input, player);
                            // Add input to input vector
                            savedInputs.push_back(input);
                            std::cout << "Turn successful." << std::endl;
                            // Display score
                            std::cout << "Your score: " << player->getScore() << std::endl;
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

                     else {

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
    // TODO implement execute the command
     
    std::vector<std::string> commands = splitString(command, ' ');
    int factory = std::stoi(commands[1]);
    std::string color = commands[2];
    int targetRow = std::stoi(commands[3]);

    //BREAKING A TILE FUNCTIONALITY? APPARENTLY YOU CAN BREAK A TILE ON PURPOSE AND DRAG IT TO BOTTOM ROW
    //IF SO, INCLUDE BREAKACTION = 'B' (IF WE IMPLEMENT THIS) IN THIS LOOP
    bool gone = false;

     if (factory == 0){
        for (size_t i = 0; i < center.size(); ++i){
            //CHECKING WHETHER FIRST PLAYER TILE HAS BEEN TAKEN
            if (!isCenterEmpty()){
                if(center[i]->getName() == 'F'){
                    for(int j = 0; j < BROKEN_ROW_SIZE; j++){
                        if(player->getBrokenRow() == nullptr || !gone){
                            // INSERT FIRST PLAYER TOKEN INTO FLOOR LINE
                            player->addToBrokenRow('F');

                            // DISPLAY FIRST PLAYER TOKEN HAS BEEN TAKEN
                            std::cout << "FIRST PLAYER TOKEN" << std::endl;
                                        
                            // DELETE TILE FROM CENTRE FACTORY
                            center[0] = nullptr;
                            gone = true;
                        }
                    }
                }
            }           
        }
    }

    gone = false;

    // Draw from factory

    // Place on row

    // Check row color

    // Place on grid if row is full

    // Score
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
 * Boundary and type validation
 * @param input : input string to be checked
 * @return : a vector containing errors of the player's input
 */
std::vector<std::string> Game::checkInput(std::string input, Player * player) {
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
            int row = std::stoi(inputArr[3]);
            if (factory < FIRST_FACTORY || factory > LAST_FACTORY) {
                result.push_back("<factory> must be a number between 0 and 5");
            }
            if (row < FIRST_STORAGE_ROW || row > LAST_STORAGE_ROW) {
                result.push_back("<row> must be a number between 1 and 5");
            }

            if (isAFactoryEmpty(factory)){
                result.push_back("The factory you have entered is empty. Your input = "
                                 + inputArr[1]);
            }
            // Check Inputted Colour
            size_t correctColor = colors.find(inputArr[2]);
            if (correctColor == std::string::npos) {
                result.push_back("<color> must be one of these values: R, Y, B, L, U");
            }
            else if (!tileExistsInAFactory(inputArr[2][0], factory)){
                result.push_back("The tile you have chosen does not exist in the chosen factory.");
            }

            if (isRowFull(row, player)){
                result.push_back("Illegal move. Chosen row is full");
            }

            if (getGridColor(row, player).find(inputArr[2])){
                result.push_back("Illegal move. The grid has already had this color");
            }

            if(getColorOfaRow(row, player) != inputArr[2][0]){
                result.push_back("Illegal move. All tiles in the same row must have the same color");
            }

        }
        catch (std::exception const &e) {
            result.push_back("<factory> must be a number between 0 and 5");
            result.push_back("<row> must be a number between 1 and 5");
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

void Game::score(Player *player) {
    // TODO implement scoring
}

char Game::getColorOfaRow(int row, Player *player) {
    return player->getUnlaidRow()[row][0].getName();
}

std::string Game::getGridColor(int row, Player *player) {
    std::string result;
    for (int i = 0; i < row; ++i) {
        result += player->getGrid()[row][i].getName();
    }
    return result;
}

bool Game::isRowFull(int row, Player *player) {
    int count = 0;
    for (int i = 0; i < row; ++i) {
        if (player->getUnlaidRow()[row][0].getName() != '.'){
            count++;
        }
    }
    return count == row;
}

