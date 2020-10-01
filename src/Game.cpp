#include "Game.h"


Game::Game() {
    // Declare factories
    factories = new Tile *[NUM_OF_FACTORIES];
    for (int i = 0; i < NUM_OF_FACTORIES; ++i) {
        factories[i] = new Tile[FACTORY_SIZE];
    }

    for (int i = 0; i < NUM_OF_FACTORIES; ++i) {
        for (int j = 0; j < FACTORY_SIZE; ++j) {
            factories[i][j] = *new Tile(' ');
        }
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
        std::cout << "=== Round " << round << " Starts ===" << std::endl;
        // End round if center and factories r empty
        bool end = endRound();
        while (!end){
            for (auto &player: players) {
                // Check if end round condition is met
                if (endRound()){
                    // End loop
                    end = true;
                }
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
                    std::vector<std::string> errors = checkInput(input, player);

                    // Check if there is any error
                    if (errors.capacity() == 0) {

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
        std::cout << "=== Round " << round << " Ends ===" << std::endl;
        round++;
        // TODO RESET
        reset();
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
            factories[i][j].setName(tileBag->get(0)->getName());
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
            if (factories[i][j].getName() != ' '){
                std::cout << factories[i][j].getName() << ' ';
            }
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
    return center.empty();
}

/**
 * Check if the factories are empty
 * @return true if empty, false if not;
 */
bool Game::areFactoriesEmpty() {
    int count = 0;
    for (int i = 0; i < NUM_OF_FACTORIES; ++i) {
        for (int j = 0; j < FACTORY_SIZE; ++j) {
            if (factories[i][j].getName() == ' '){
                count++;
            }
        }
    }
    std::cout << "FACTORIES TILES COUNT: " << count << std::endl;
    return count == 20;
}

bool Game::isAFactoryEmpty(int factory) {
    int count = 0;
    if (factory != 0){
        for (int i = 0; i < FACTORY_SIZE; ++i) {
            if (factories[factory - 1][i].getName() == '\0'){
                count++;
            }
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
            else if (isRowFull(row, player)){
                result.push_back("Illegal move. Chosen row is full");
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

            size_t grid = getGridColor(row, player).find(inputArr[2]);
            if ( grid != std::string::npos){
                result.push_back("Illegal move. The grid has already had this color");
            }

            if( getColorOfaRow(row, player) != '.' && (getColorOfaRow(row, player) != inputArr[2][0])){
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
    if (factory == 0) {
        for (size_t i = 0; i < center.size(); ++i) {
            if (center[i]->getName() == tile){
                exist = true;
                i = center.size();
            }
        }
    }
    else {
        for (int i = 0; i < FACTORY_SIZE; ++i) {
            if (factories[factory - 1][i].getName() == tile){
                exist = true;
                // Break loop
                i = FACTORY_SIZE;
            }
        }
    }
    return exist;
}

void Game::score(Player *player) {
    // TODO implement scoring
}

void Game::execute(const std::string &command, Player * player) {
    std::vector<std::string> commands = splitString(command, ' ');
    int factory = std::stoi(commands[1]) - 1;
    char color = commands[2][0];
    int targetRow = std::stoi(commands[3]);

    // A variable to store chosen tiles
    std::string chosenTiles;

    // Draw from factory or center
    std::cout << "BEFORE DRAW: " << chosenTiles << std::endl;
    if (factory + 1 != 0){
        for (int i = 0; i < FACTORY_SIZE; ++i) {
            if (factories[factory][i].getName() == color){
                // Add Tile to tiles list
                chosenTiles += color;
                // Assign empty value to factory tiles
                factories[factory][i] = ' ';
            }
        }

    }
    else {
        for (size_t i = 0; i < center.size(); ++i) {
            if (center[i]->getName() == color){
                chosenTiles += color;
            }
        }
        // Delete chosen tiles
        std::vector<Tile *>::iterator it = center.begin();
        while (it != center.end()){
            if ((*it)->getName() == color){
                it = center.erase(it);
            }
            else {
                it++;
            }
        }

    }
    std::cout << "AFTER DRAW: " << chosenTiles << std::endl;

    // Move excess tiles to centre factory
    std::cout << "BEFORE MOVING: " << chosenTiles << std::endl;
    if (factory + 1 != 0){
        for (int i = 0; i < FACTORY_SIZE; ++i) {
            if (factories[factory][i].getName() != ' '){
                // Add tile to centre factory
                center.push_back(new Tile(factories[factory][i].getName()));
                // Set non-chosen tiles to empty space
                factories[factory][i].setName(' ');
            }
        }
    }
    std::cout << "AFTER MOVING: " << chosenTiles << std::endl;

    // Add F at the of the string if player chooses centre factory
    if (factory + 1 == 0 && center.size() > 0 && center[0]->getName() == 'F'){
        chosenTiles += 'F';
        // Delete F tile from centre
        center.erase(center.begin());
    }

    // Place on row
    std::cout << "BEFORE ADDING TO ROW: " << chosenTiles << std::endl;
    for (int i = 0; i < targetRow; ++i) {

        if (player->getUnlaidRow()[targetRow - 1][i].getName() == '.'){
            if (chosenTiles[0] == 'B'){
                player->getUnlaidRow()[targetRow - 1][i].setName( 'B');
            }
            else if (chosenTiles[0] == 'Y'){
                player->getUnlaidRow()[targetRow - 1][i].setName( 'Y');
            }
            else if (chosenTiles[0] == 'R'){
                player->getUnlaidRow()[targetRow - 1][i].setName( 'R');
            }
            else if (chosenTiles[0] == 'U'){
                player->getUnlaidRow()[targetRow - 1][i].setName( 'U');
            }
            else if (chosenTiles[0] == 'L'){
                player->getUnlaidRow()[targetRow - 1][i].setName( 'L');
            }
            // Delete first tile
            if (chosenTiles.length() > 0 && chosenTiles[0] != 'F') {
                chosenTiles.erase(chosenTiles.begin());
            }
        }
    }
    std::cout << "AFTER ADDING TO ROW: " << chosenTiles << std::endl;


    // Move leftover tiles to broken rows
    int brokenRowCount = player->getBrokenRowCount();
    if (chosenTiles[chosenTiles.length() - 1] == 'F'){

        if (player->getBrokenRow()[0].getName() == ' '){
            player->addToBrokenRow('F');
        }
        else {
            std::string savedBrokenTiles;
            for (int i = 0; i < BROKEN_ROW_SIZE; ++i) {
                char temp = player->getBrokenRow()[i].getName();
                if (temp != ' '){
                    savedBrokenTiles += temp;
                }
            }
            // Reset Counter
            player->setBrokenRowCount(0);
            player->addToBrokenRow('F');

            // Add Broken tile back to broken row
            for (size_t i = 0; i < savedBrokenTiles.size(); ++i) {
                std::cout << savedBrokenTiles[i] << std::endl;
                player->addToBrokenRow(savedBrokenTiles[i]);
            }
        }

        // Delete F at the end of the string
        chosenTiles.pop_back();
        std::cout << "BEFORE BROKEN: " << chosenTiles[chosenTiles.length() - 1] << std::endl;
        for (size_t i = 0; i < chosenTiles.length(); ++i) {
            if (brokenRowCount <= BROKEN_ROW_SIZE){
                player->addToBrokenRow(chosenTiles[i]);
                if (chosenTiles.length() > 0){
                    chosenTiles.erase(chosenTiles.begin());
                }
            }
        }
        std::cout << "AFTER BROKEN: " << chosenTiles << std::endl;
    }
    else {
        for (size_t i = 0; i < chosenTiles.length(); ++i) {
            if (brokenRowCount <= BROKEN_ROW_SIZE){
                player->addToBrokenRow(chosenTiles[i]);
                // Delete the first character
                if (chosenTiles.length() > 0){
                    chosenTiles.erase(chosenTiles.begin());
                }
            }
        }
    }

    // Capitalize corresponding tile on the mosaic if applicable;
    int countColorInRow = 0;
    for (int i = 0; i < targetRow; ++i) {
        if (player->getUnlaidRow()[targetRow - 1][i].getName() != '.'){
            countColorInRow++;
        }
    }

//    std::cout << "Row Count: " << countColorInRow << std::endl;
//    std::cout << "Target Row Count: " << targetRow << std::endl;
    // if the number of color = target row number
    if (countColorInRow == targetRow){
        for (int i = 0; i < MOSAIC_DIM; ++i) {
            char temp = player->getGrid()[targetRow - 1][i].getName();
            if (color == toupper(temp)){
                player->getGrid()[targetRow - 1][i].setName(color);
                // Break loop
                i = MOSAIC_DIM;
            }
        }
    }

    // Score
}


char Game::getColorOfaRow(int row, Player *player) {
    return player->getUnlaidRow()[row - 1][0].getName();
}

std::string Game::getGridColor(int row, Player *player) {
    std::string result;
    for (int i = 0; i < 5; ++i) {
        result += player->getGrid()[row - 1][i].getName();
    }
    return result;
}

bool Game::isRowFull(int row, Player *player) {
    int full = true;
    for (int i = 0; i < row; ++i) {
        if (player->getUnlaidRow()[row - 1][i].getName() == '.'){
            full = false;
            i = row;
        }
    }
    return full;
}

bool Game::endRound() {
    // TODO CHECK IF MOVE IS POSSIBLE. IF NOT AUTOMATICALLY END ROUND
    std::cout << "EMPTY CENTER: " << isCenterEmpty();
    std::cout << "EMPTY FACTORIES: " << areFactoriesEmpty();
    return isCenterEmpty() && areFactoriesEmpty();
}

void Game::reset() {
    setTileBagAutomatically();
    fillFactories();
    for (auto &player: players) {
        // Reset Broken Row
        for (int i = 0; i < BROKEN_ROW_SIZE; ++i) {
            player->getBrokenRow()[i].setName(' ');
        }

        // Reset Broken Row Count
        player->setBrokenRowCount(0);

        // Reset Unlaid Rows
        int rowCount = 1;
        for (int i = 0; i < MOSAIC_DIM; ++i) {
            for (int j = 0; j < rowCount; ++j) {
                player->getUnlaidRow()[i][j].setName('.');
            }
            rowCount++;
        }

    }
}

bool Game::markedToBeDeleted(Tile *tile, char color) {
    return tile->getName() == color;
}

void Game::testLoadGame(char* fileName) {

    // Initialize test mode variables
    std::ifstream file;
    file.open(fileName, std::ifstream::in);
    int lineCount = 1;
    std::string line;
    std::string validChars = "RYBLUF";
    std::vector<Player *> testPlayers;

    while (lineCount <= 1) {
        getline(file, line);

        // Validate tile bag input
        for (size_t i = 0; i < line.size(); ++i) {
            size_t checked = validChars.find(line[i]);
            if (checked == std::string::npos) {
                std::cout << "Corrupted save file. Tile bag contains invalid characters!" << std::endl;
                std::cout << "Disengaging test mode..." << std::endl;
                quitGame();
            }
        }
        // Setting up game
        setTileBagFromString(line);
        addFirstTileToCenter();
        fillFactories();
        lineCount++;
    }

    // Grab players' names
    while (lineCount <= 3) {
        getline(file, line);
        if (line.empty()){
            std::cout << "Corrupted save file. A player's name cannot be blank!" << std::endl;
            std::cout << "Disengaging test mode..." << std::endl;
            quitGame();
        }

        testPlayers.push_back(new Player(line));
        lineCount++;
    }

    // Add players to game;
    addPlayers(testPlayers);


    // Count round
    int round = 1;
    while (round <= MAX_GAME_ROUNDS){
        bool end = endRound();
        while (!end){
            // Check if end round condition is met
            if (endRound()){
                // End loop
                end = true;
                std::cout << "ROUND ENDS" << std::endl;
            }
            // Play
            for (auto &player: players) {

                // Check Eof
                if (getline(file, line)){
                    // Vector to store error messages
                    std::vector<std::string> errors = checkInput(line, player);
                    if (errors.capacity() == 0){
                        execute(line, player);
                    }
                    else {
                        std::cout << "Corrupted save file. Error at line " << lineCount + 1 << std::endl;
                        std::cout << "Disengaging test mode..." << std::endl;
                        quitGame();
                    }
                }
                else {
                    // Print result
                    std::cout << "Factories: " <<std::endl;
                    printFactories();
                    std::cout << std::endl;

                    for (auto &testPlayer: players) {
                        // TODO add scoring
                        std::cout << "Score for player " << testPlayer->getName() << ": " << testPlayer->getScore() <<  std::endl;
                        std::cout << "Mosaic for " << testPlayer->getName() << ":" <<  std::endl;
                        testPlayer->printMosaic();
                        testPlayer->printBrokenRow();
                        std::cout << std::endl;
                    }
                    std::cout << "=== Game Loaded Successfully ===" << std::endl;
                    quitGame();
                }
                lineCount++;
            }
        }

        round++;
        // TODO Reset game
    }
    // Cleaning up
    file.close();
}
