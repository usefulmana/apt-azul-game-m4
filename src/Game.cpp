#include "Game.h"

Game::Game() {
    // Declare factories
    factories = new Tile *[NUM_OF_FACTORIES];
    for (int i = 0; i < NUM_OF_FACTORIES; ++i) {
        factories[i] = new Tile[FACTORY_SIZE];
    }

    // Initialize factories
    for (int i = 0; i < NUM_OF_FACTORIES; ++i) {
        for (int j = 0; j < FACTORY_SIZE; ++j) {
            factories[i][j] = *new Tile(WHITESPACE);
        }
    }

    // Initialize the tile bag
    tileBag = new LinkedList<Tile *>();

    // Initialize the box lid
    boxLid = new LinkedList<Tile *>();

    // Default values
    isRandom = false;
    isAdvanced = false;

    // Default seed
    seed = 1;
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
    for (auto &player: p) {

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

    // A vector to save inputs
    std::vector<std::string> savedInputs;

    //Fill Tile Bag
    std::string bag;

    for (int i = 0; i < NUM_OF_TILES_IN_TILE_BAG; ++i) {
        bag += tileBag->get(i)->getName();
    }
    // Save tile bag to input vector;
    savedInputs.push_back(bag);


    //Add Players to Game
    for (auto &player: players) {
        savedInputs.push_back(player->getName());
    }

    //Add "First" Tile to Centre Factory
    addFirstTileToCenter();

    //Fill Remaining Factories
    fillFactories();

    //Round Number Counter
    int round = 1;

    // While game hasn't reached last round
    while (round <= MAX_GAME_ROUNDS) {
        std::cout << "=== Round " << round << " Starts ===" << std::endl;
        // End round if all factories including Centre are empty

        bool end = endRound();
        if (players[0]->isFirst()) {
            while (!end) {
                for (size_t i = 0; i < NUM_OF_PLAYERS && !end; ++i) {
                    auto player = players[i];
                    playTurn(player, end, savedInputs);
                }
            }
        } else {
            while (!end) {
                for (size_t i = 0; i < NUM_OF_PLAYERS && !end; ++i) {
                    auto player = players[NUM_OF_PLAYERS - 1 - i];
                    playTurn(player, end, savedInputs);
                }
            }
        }

        // Next Round
        std::cout << "=== Round " << round << " Ends ===" << std::endl;
        round++;

        // Error Checking
        if (round <= MAX_GAME_ROUNDS) {
            // Deduct players' scores from tiles in the broken row
            for (auto &player: players) {
                deductBrokenTile(player);
            }
            printScores();
            // Reset game state
            reset();
        }
    }
}

void Game::deductBrokenTile(Player *player) {
    int deductBy = 0;
    int count = 0;
    //Check contents of Player's Broken Row
    for (int i = 0; i < BROKEN_ROW_SIZE; i++) {
        if (player->getBrokenRow()[i].getName() != WHITESPACE) {
            count++;
            if (count <= BROKEN_ROW_SIZE - 4) {
                // First three tiles -1 each
                deductBy++;
            } else if (count <= BROKEN_ROW_SIZE - 2) {
                // Nx two tiles -2 each
                deductBy += 2;
            } else if (count <= BROKEN_ROW_SIZE) {
                // Nx two tiles -3 each
                deductBy += 3;
            }

        }
    }

    //Perform deduction
    int score = player->getScore() - deductBy;

    //Allocate Player Score
    player->setScore(score);
}

void Game::setTileBagAutomatically() {
    std::default_random_engine engine(seed);
    std::string tiles;

    if (!isAdvanced) {
        tiles = NORMAL_ALL_TILES;
    }

    shuffleString(tiles, engine);

    for (size_t i = 0; i < tiles.length(); ++i) {
        tileBag->addBack(new Tile(tiles[i]));
    }
}

void Game::setTileBagFromString(const std::string &line) {
    //Initialise Tile Bag
    tileBag = new LinkedList<Tile *>();

    //Fill Tile Bag
    for (size_t i = 0; i < line.length(); ++i) {
        tileBag->addBack(new Tile(line[i]));
    }
}

LinkedList<Tile *> *Game::getTileBag() {
    return tileBag;
}

void Game::fillFactories() {
    // Fill factories with tiles from the tile bag
    for (int i = 0; i < NUM_OF_FACTORIES && tileBag->getLength() > 0; ++i) {
        for (int j = 0; j < FACTORY_SIZE && tileBag->getLength() > 0; ++j) {
            factories[i][j].setName(tileBag->get(0)->getName());

            //Remove tile from tile bag
            tileBag->popFront();
        }
    }
}

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
            if (factories[i][j].getName() != ' ') {
                std::cout << factories[i][j].getName() << ' ';
            }
        }
        std::cout << std::endl;
    }
}

void Game::addFirstTileToCenter() {
    center.push_back(new Tile(FIRST_TILE));
}

bool Game::isCenterEmpty() {
    return center.empty();
}

bool Game::areFactoriesEmpty() {
    int count = 0;
    for (int i = 0; i < NUM_OF_FACTORIES; ++i) {
        for (int j = 0; j < FACTORY_SIZE; ++j) {
            if (factories[i][j].getName() == WHITESPACE) {
                count++;
            }
        }
    }
    return count == MAX_TILE_NUM;
}

bool Game::isAFactoryEmpty(int factory) {
    // Initialize a counter
    int count = 0;

    if (factory != 0) {
        // Loop through the chosen factory
        for (int i = 0; i < FACTORY_SIZE; ++i) {
            if (factories[factory - 1][i].getName() == WHITESPACE) {
                count++;
            }
        }
    }
    return count == FACTORY_SIZE;
}

std::vector<std::string> Game::checkInput(std::string input, Player *player) {
    // a vector that contains all error messages
    std::vector<std::string> result;

    // Split input string into pieces
    std::vector<std::string> inputArr = splitString(input, WHITESPACE);

    // Valid color characters
    std::string colors = VALID_CHARS;


    // Check if save argument number was entered
    if (inputArr.size() == 2) {
        // Check for save command
        if (inputArr[0] != "save") {
            result.push_back("Invalid input. Correct input = save. Your input = " + inputArr[0]);
        }
    }
        // Check if turn argument number was entered
    else if (inputArr.size() == 4) {
        // Check for turn command
        if (inputArr[0] != "turn") {
            result.push_back("Invalid input. Correct input = turn. Your input = " + inputArr[0]);
        }

        // Check Factory Number entered
        try {
            // Convert input from string to int
            int factory = std::stoi(inputArr[1]);
            int row = std::stoi(inputArr[3]);
            if (factory < FIRST_FACTORY || factory > LAST_FACTORY) {
                result.push_back("<factory> must be a number between 0 and 5");
            } else if (isAFactoryEmpty(factory)) {
                result.push_back("The factory you have entered is empty. Your input = "
                                 + inputArr[1]);
            }

            if (row < FIRST_STORAGE_ROW || row > LAST_STORAGE_ROW) {
                result.push_back("<row> must be a number between 0 and 5");
            } else {
                if (isRowFull(row, player)) {
                    result.push_back("Illegal move. Chosen row is full");
                }
                if (row != 0) {
                    size_t grid = getGridColor(row, player).find(inputArr[2]);
                    if (grid != std::string::npos) {
                        result.push_back("Illegal move. The grid has already had this color");
                    }

                    if (getColorOfaRow(row, player) != '.' && (getColorOfaRow(row, player) != inputArr[2][0])) {
                        result.push_back("Illegal move. All tiles in the same row must have the same color");
                    }
                }
            }

            // Check Colour entered
            size_t correctColor = colors.find(inputArr[2]);
            if (correctColor == std::string::npos) {
                result.push_back("<color> must be one of these values: R, Y, B, L, U");
            } else if (!tileExistsInAFactory(inputArr[2][0], factory)) {
                result.push_back("The tile you have chosen does not exist in the chosen factory.");
            }

        } //Check other exceptions
        catch (std::exception const &e) {
            result.push_back("<factory> must be a number between 0 and 5");
            result.push_back("<row> must be a number between 0 and 5");
        }

    } else {
        result.push_back(
                "Wrong number of arguments or arguments are not separated by whitespace or excessive whitespaces. "
                "Your input = " + input);
    }
    return result;
}

bool Game::tileExistsInAFactory(const char &tile, int factory) {
    bool exist = false;

    //Search Centre Factory first
    if (factory == 0) {
        for (size_t i = 0; i < center.size(); ++i) {
            if (center[i]->getName() == tile) {
                exist = true;
                // Break loop
                i = center.size();
            }
        }
    } else if (factory > FIRST_FACTORY && factory < LAST_FACTORY + 1) {
        for (int i = 0; i < FACTORY_SIZE; ++i) {
            if (factories[factory - 1][i].getName() == tile) {
                exist = true;
                // Break loop
                i = FACTORY_SIZE;
            }
        }
    }

    return exist;
}

void Game::execute(const std::string &command, Player *player) {

    // Split command
    std::vector<std::string> commands = splitString(command, WHITESPACE);

    // Store variables from the command
    int factory = std::stoi(commands[1]) - 1;
    char color = commands[2][0];
    int targetRow = std::stoi(commands[3]);

    // Storage of Chosen Tile
    std::string chosenTiles;

    // Draw from factory or center
    if (factory + 1 != 0) {
        // Draw from factory
        for (int i = 0; i < FACTORY_SIZE; ++i) {
            if (factories[factory][i].getName() == color) {
                // Add Tile to tiles list
                chosenTiles += color;
                // Assign empty value to factory tiles
                factories[factory][i] = WHITESPACE;
            }
        }

    } else {
        // Draw from center
        for (size_t i = 0; i < center.size(); ++i) {
            if (center[i]->getName() == color) {
                chosenTiles += color;
            }
        }
        // Delete chosen tiles
        std::vector<Tile *>::iterator it = center.begin();
        while (it != center.end()) {
            if ((*it)->getName() == color) {
                it = center.erase(it);
            } else {
                it++;
            }
        }
    }

    // Move excess tiles to centre factory
    if (factory + 1 != 0) {
        for (int i = 0; i < FACTORY_SIZE; ++i) {
            if (factories[factory][i].getName() != WHITESPACE) {
                // Add tile to centre factory
                center.push_back(new Tile(factories[factory][i].getName()));
                // Set non-chosen tiles to empty space
                factories[factory][i].setName(WHITESPACE);
            }
        }
    }

    // Add F at the of the string if player chooses centre factory
    if (factory + 1 == 0 && center.size() > 0 && center[0]->getName() == FIRST_TILE) {
        chosenTiles += FIRST_TILE;
        // Set player with first tile to go first nx round
        player->setFirst(true);
        for (size_t i = 0; i < players.size(); ++i) {
            if (player->getId() != players[i]->getId()) {
                players[i]->setFirst(false);
                i = players.size();
            }
        }
        // Remove F tile from centre
        center.erase(center.begin());
    }

    if (targetRow != 0) {
        // Place on row
        for (int i = 0; i < targetRow; ++i) {

            if (player->getUnlaidRow()[targetRow - 1][i].getName() == '.') {
                if (chosenTiles[0] == DARK_BLUE) {
                    player->getUnlaidRow()[targetRow - 1][i].setName(DARK_BLUE);
                } else if (chosenTiles[0] == YELLOW) {
                    player->getUnlaidRow()[targetRow - 1][i].setName(YELLOW);
                } else if (chosenTiles[0] == RED) {
                    player->getUnlaidRow()[targetRow - 1][i].setName(RED);
                } else if (chosenTiles[0] == BLACK) {
                    player->getUnlaidRow()[targetRow - 1][i].setName(BLACK);
                } else if (chosenTiles[0] == LIGHT_BLUE) {
                    player->getUnlaidRow()[targetRow - 1][i].setName(LIGHT_BLUE);
                }
                // Delete tiles
                if (chosenTiles.length() > 0 && chosenTiles[0] != FIRST_TILE) {
                    chosenTiles.erase(chosenTiles.begin());
                }
            }
        }

        // Check if there is a first tile
        if (chosenTiles[chosenTiles.length() - 1] == FIRST_TILE) {

            if (player->getBrokenRow()[0].getName() == WHITESPACE) {
                player->addToBrokenRow(FIRST_TILE);
            } else {
                std::string savedBrokenTiles;
                for (int i = 0; i < BROKEN_ROW_SIZE; ++i) {
                    char temp = player->getBrokenRow()[i].getName();
                    if (temp != WHITESPACE) {
                        savedBrokenTiles += temp;
                    }
                }
                // Reset Counter
                player->setBrokenRowCount(0);
                player->addToBrokenRow('F');

                // Add previous tiles back to broken row
                for (size_t i = 0; i < savedBrokenTiles.size(); ++i) {
                    if (player->getBrokenRowCount() == 7) {
                        // add fallen tiles to box lid if broken tile is full
                        boxLid->addBack(new Tile(savedBrokenTiles[i]));
                    } else {
                        player->addToBrokenRow(savedBrokenTiles[i]);
                    }
                }
            }

            // Delete F from the Tail
            chosenTiles.pop_back();

            // Add the rest of tiles to the broken row
            for (size_t i = 0; i < chosenTiles.length(); ++i) {
                if (player->getBrokenRowCount() == 7) {
                    // add fallen tiles to box lid if broken tile is full
                    boxLid->addBack(new Tile(chosenTiles[i]));
                } else {
                    player->addToBrokenRow(chosenTiles[i]);
                }
            }

            // Delete after adding things to broken row
            chosenTiles.clear();
        } else {
            for (size_t i = 0; i < chosenTiles.length(); ++i) {
                player->addToBrokenRow(chosenTiles[i]);

            }
            // Delete after adding things to broken row
            chosenTiles.clear();
        }

        // Set Placed as Invalid to Ensure it Holds a Placed Value
        placedTileX = INVALID_COORDINATE;
        placedTileY = INVALID_COORDINATE;

        // Capitalize corresponding tile on the mosaic if applicable;
        int countColorInRow = 0;
        for (int i = 0; i < targetRow; ++i) {
            if (player->getUnlaidRow()[targetRow - 1][i].getName() != NO_TILE) {
                countColorInRow++;
            }
        }

        if (countColorInRow == targetRow) {
            for (int i = 0; i < MOSAIC_DIM; ++i) {
                char temp = player->getGrid()[targetRow - 1][i].getName();
                if (color == toupper(temp)) {
                    player->getGrid()[targetRow - 1][i].setName(color);

                    placedTileY = targetRow - 1;
                    placedTileX = i;

                    i = MOSAIC_DIM;
                }
            }
        }

        // Initialise Score
        auto score = Score(player, placedTileX, placedTileY);
        score.getRoundScore();
    } else {
        // Add to broken row;
        // Check if there is a first tile
        if (chosenTiles[chosenTiles.length() - 1] == FIRST_TILE) {

            if (player->getBrokenRow()[0].getName() == WHITESPACE) {
                player->addToBrokenRow(FIRST_TILE);
            } else {
                std::string savedBrokenTiles;
                for (int i = 0; i < BROKEN_ROW_SIZE; ++i) {
                    char temp = player->getBrokenRow()[i].getName();
                    if (temp != WHITESPACE) {
                        savedBrokenTiles += temp;
                    }
                }
                // Reset Counter
                player->setBrokenRowCount(0);
                player->addToBrokenRow('F');

                // Add previous tiles back to broken row
                for (size_t i = 0; i < savedBrokenTiles.size(); ++i) {
                    player->addToBrokenRow(savedBrokenTiles[i]);
                }
            }

            // Delete F from the Tail
            chosenTiles.pop_back();

            // Add the rest of tiles to the broken row
            for (size_t i = 0; i < chosenTiles.length(); ++i) {
                player->addToBrokenRow(chosenTiles[i]);
            }

            // Delete after adding things to broken row
            chosenTiles.clear();
        } else {
            for (size_t i = 0; i < chosenTiles.length(); ++i) {
                player->addToBrokenRow(chosenTiles[i]);

            }
            // Delete after adding things to broken row
            chosenTiles.clear();
        }
    }
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
    if (row != 0) {
        for (int i = 0; i < row; ++i) {
            if (player->getUnlaidRow()[row - 1][i].getName() == '.') {
                full = false;
                // Break loop
                i = row;
            }
        }
    } else {
        full = false;
    }

    return full;
}

bool Game::endRound() {
    return isCenterEmpty() && areFactoriesEmpty();
}

void Game::reset() {
    // Fill factories from tile bag
    fillFactories();
    // Add First tile to center
    addFirstTileToCenter();

    for (auto &player: players) {
        // Reset Broken Row
        for (int i = 0; i < BROKEN_ROW_SIZE; ++i) {
            // Add broken tiles back to the box lid
            if (player->getBrokenRow()[i].getName() != WHITESPACE &&
                player->getBrokenRow()[i].getName() != FIRST_TILE) {
                boxLid->addBack(new Tile(player->getBrokenRow()[i].getName()));
            }
            // Reset Broken Row
            player->getBrokenRow()[i].setName(WHITESPACE);
        }

        // Reset Broken Row Count
        player->setBrokenRowCount(0);

        // Reset Unlaid Rows
        int rowCount = 1;
        for (int i = 0; i < MOSAIC_DIM; ++i) {
            if (isRowFull(i + 1, player)) {
                for (int j = 0; j < rowCount; ++j) {
                    player->getUnlaidRow()[i][j].setName(NO_TILE);
                }
            }
            rowCount++;
        }
    }

    // Add Boxlid tile to tilebag
    if (isRandom && tileBag->getLength() == 0 && boxLid->getLength() > 0) {
        moveTilesFromBoxLidToTileBag();
        // Shuffle the bag
        shuffleTileBag();
    }
}

bool Game::markedToBeDeleted(Tile *tile, char color) {
    return tile->getName() == color;
}

void Game::testLoadGame(char *fileName) {

    // Initialize test mode variables
    int lineCount = 1;

    std::ifstream file;
    file.open(fileName, std::ifstream::in);

    std::string line;
    std::string validChars = VALID_CHARS;
    std::vector<Player *> testPlayers;

    while (lineCount <= 1) {
        getline(file, line);

        // Validate tile bag input
        int count = 0;
        for (size_t i = 0; i < line.size(); ++i) {
            size_t checked = validChars.find(line[i]);
            if (checked == std::string::npos) {
                std::cout << "Corrupted save file. Tile bag contains invalid characters!" << std::endl;
                std::cout << "Disengaging test mode..." << std::endl;
                quitGame();
            } else {
                count++;
            }
        }
        if (count < NUM_OF_TILES_IN_TILE_BAG || count > NUM_OF_TILES_IN_TILE_BAG) {
            std::cout << "Corrupted save file. Initial tile bag must have exactly 100 tiles!" << std::endl;
            std::cout << "Disengaging test mode..." << std::endl;
            quitGame();
        } else {
            // Setting up game
            setTileBagFromString(line);
            addFirstTileToCenter();
            fillFactories();
            lineCount++;
        }
    }

    // Fetch players' names
    while (lineCount <= 3) {
        getline(file, line);
        if (line.empty()) {
            std::cout << "Corrupted save file. A player's name cannot be blank!" << std::endl;
            std::cout << "Disengaging test mode..." << std::endl;
            quitGame();
        }
        if (lineCount == 2) {
            players.push_back(new Player(line, lineCount - 1, true));
        } else {
            players.push_back(new Player(line, lineCount - 1, false));
        }

        lineCount++;
    }

    // Add players to game;
    addPlayers(testPlayers);

    // Count round
    int round = 1;
    while (round <= MAX_GAME_ROUNDS) {
        std::cout << "=== Round " << round << " ===" << std::endl;
        bool end = endRound();
        if (players[0]->isFirst()) {
            while (!end) {
                for (size_t i = 0; i < NUM_OF_PLAYERS && !end; ++i) {
                    auto player = players[i];
                    // Check End Of File
                    readLineAndQuit(file, line, player, end, lineCount);
                }
            }
        } else {
            while (!end) {
                for (size_t i = 0; i < NUM_OF_PLAYERS && !end; ++i) {
                    auto player = players[NUM_OF_PLAYERS - 1 - i];
                    // Check End Of File
                    readLineAndQuit(file, line, player, end, lineCount);
                }
            }
        }

        // Check if the next line is empty
        if (file.peek() == EOF) {
            printGameState();
            std::cout << "=== Game Loaded Successfully ===" << std::endl;
            quitGame();
        } else {
            round++;
            for (auto &player: players) {
                deductBrokenTile(player);
            }
            reset();
        }
    }

    // Cleaning up
    file.close();
}

void Game::printGameState() {
    std::cout << "Factories: " << std::endl;
    printFactories();
    std::cout << std::endl;

    for (auto &testPlayer: players) {
        std::cout << "Score for player " << testPlayer->getName() << ": " << testPlayer->getScore() << std::endl;
        std::cout << "Mosaic for " << testPlayer->getName() << ":" << std::endl;
        testPlayer->printMosaic();
        testPlayer->printBrokenRow();
        std::cout << std::endl;
    }
}

void Game::load(const std::string &fileName) {
    // Initialize test mode variables
    std::ifstream file;
    file.open(fileName, std::ifstream::in);
    int lineCount = 1;
    std::string line;
    std::string validChars = VALID_CHARS;
    std::vector<Player *> testPlayers;

    // A vector to save inputs
    std::vector<std::string> savedInputs;

    while (lineCount <= 1) {
        getline(file, line);

        // Validate tile bag input
        int count = 0;
        for (size_t i = 0; i < line.size(); ++i) {
            size_t checked = validChars.find(line[i]);
            if (checked == std::string::npos) {
                std::cout << "Corrupted save file. Tile bag contains invalid characters!" << std::endl;
                std::cout << "Disengaging test mode..." << std::endl;
                quitGame();
            } else {
                count++;
            }
        }
        if (count < NUM_OF_TILES_IN_TILE_BAG || count > NUM_OF_TILES_IN_TILE_BAG) {
            std::cout << "Corrupted save file. Initial tile bag must have exactly 100 tiles!" << std::endl;
            std::cout << "Disengaging test mode..." << std::endl;
            quitGame();
        } else {
            savedInputs.push_back(line);
            // Setting up game
            setTileBagFromString(line);
            addFirstTileToCenter();
            fillFactories();
            lineCount++;
        }
    }

    // Grab players' names
    while (lineCount <= 3) {
        getline(file, line);
        if (line.empty()) {
            std::cout << "Corrupted save file. A player's name cannot be blank!" << std::endl;
            std::cout << "Disengaging test mode..." << std::endl;
            quitGame();
        } else {
            savedInputs.push_back(line);
        }

        if (lineCount == 2) {
            players.push_back(new Player(line, lineCount - 1, true));
        } else {
            players.push_back(new Player(line, lineCount - 1, false));
        }

        lineCount++;
    }

    // Add players to game;
    addPlayers(testPlayers);

    // Count round
    int round = 1;
    while (round <= MAX_GAME_ROUNDS) {
        std::cout << "=== Round " << round << " ===" << std::endl;
        bool end = endRound();
        if (players[0]->isFirst()) {
            while (!end) {
                for (size_t i = 0; i < NUM_OF_PLAYERS && !end; ++i) {
                    auto player = players[i];
                    // Check if End Of File is reached
                    readLineAndPlayTurn(file, line, player, end, savedInputs, lineCount);
                }
            }
        } else {
            while (!end) {
                for (size_t i = 0; i < NUM_OF_PLAYERS && !end; ++i) {
                    auto player = players[NUM_OF_PLAYERS - 1 - i];
                    // Check if End Of File is reached
                    readLineAndPlayTurn(file, line, player, end, savedInputs, lineCount);
                }
            }
        }

        // Next Round
        std::cout << "=== Round " << round << " Ends ===" << std::endl;
        round++;

        // Error Checking
        if (round <= MAX_GAME_ROUNDS) {
            for (auto &player: players) {
                deductBrokenTile(player);
            }
            printScores();
            reset();
        }
    }
    // Cleaning up
    file.close();

    std::cout << "=== Game Over ===" << std::endl;
    std::cout << "=== Scoreboard ===" << std::endl;
    printFinalResults();
    quitGame();
}

void Game::printFinalResults() {
    printScores();
    // Print result
    if (players[0]->getScore() > players[1]->getScore()) {
        std::cout << "Player " << players[0]->getName() << " wins!" << std::endl;
    } else if (players[0]->getScore() < players[1]->getScore()) {
        std::cout << "Player " << players[1]->getName() << " wins!" << std::endl;
    } else {
        std::cout << "It's a tie!" << std::endl;
    }
    std::cout << std::endl;
}

void Game::printScores() {
    for (auto &player : players) {
        std::cout << "Score for " << player->getName() << ": " << player->getScore()
                  << std::endl;
    }
}

void Game::printInstructions() {
    std::cout << "To Play: turn <factory> <color> <row>" << std::endl;
    std::cout << "To Save: save <filename>" << std::endl;
    std::cout << "To Discard: turn <factory> <color> 0" << std::endl;
}

void Game::printNewTurnInformation(Player *player) {
    std::cout << "TURN FOR PLAYER: " << player->getName() << std::endl;
    std::cout << "Factories:" << std::endl;
    printFactories();
    std::cout << std::endl;
    std::cout << "Mosaic for " << player->getName() << ":" << std::endl;
    player->printMosaic();
    player->printBrokenRow();
    std::cout << std::endl;
}

void Game::getUserInput(std::string &input) {
    std::cout << "Your input:" << std::endl;
    std::cout << "> ";

    // Stores console input without leading whitespace
    std::getline(std::cin >> std::ws, input);

    // Check for EOF Character (^D)
    if (std::cin.eof()) {
        quitGame();
    }
}

void Game::printEndErrorMessage(std::vector<std::string> &errors) {
    std::cout << "Invalid Input!" << std::endl;
    std::cout << "Error(s): " << std::endl;

    for (auto &error : errors) {
        std::cout << "- " << error << std::endl;
    }
    std::cout << "Please try again " << std::endl;
    std::cout << std::endl;
}

void
Game::interpretCommand(std::string &input, Player *player, bool &validInput, std::vector<std::string> &savedInputs) {
    if (input.substr(0, 4) == "turn") {
        execute(input, player);
        // Add input to input vector
        savedInputs.push_back(input);
        std::cout << "Turn successful." << std::endl;

        std::cout << std::endl;
        // End input loop
        validInput = true;

    } else if (input.substr(0, 4) == "save") {
        // Find position of first whitespace
        int pos = input.find(WHITESPACE);

        // Return substring of everything following the whitespace
        std::string fileName = input.substr(pos + 1);

        // Save game
        save(fileName, savedInputs);

        std::cout << "Saved to " << fileName << std::endl;
    }
}

void Game::playTurn(Player *player, bool &end, std::vector<std::string> &savedInputs) {
    printNewTurnInformation(player);

    bool validInput = false;

    // Instructions/Help
    printInstructions();

    // Exit if Valid Input Entered
    while (!validInput) {

        // Get user input
        std::string input;

        getUserInput(input);

        // Check for errors
        std::vector<std::string> errors = checkInput(input, player);

        // Check if there is any error
        if (errors.capacity() == 0) {
            interpretCommand(input, player, validInput, savedInputs);
        } else {

            // Notify users of errors
            printEndErrorMessage(errors);
        }
        // Check if end round condition is met
        if (endRound()) {
            // End loops
            validInput = true;
            end = true;
        }
    }
    std::cout << std::endl;
}

void Game::readLineAndPlayTurn(std::ifstream &file, std::string &line, Player *player, bool &end,
                               std::vector<std::string> &savedInputs, int &lineCount) {
    if (getline(file, line)) {
        // Vector to store error messages
        std::vector<std::string> errors = checkInput(line, player);

        // If no errors are found
        if (errors.capacity() == 0) {
            execute(line, player);
            savedInputs.push_back(line);
        } else {
            std::cout << "Corrupted save file. Error at line " << lineCount << std::endl;
            std::cout << "Disengaging test mode..." << std::endl;
            quitGame();
        }
        // Check if end round condition is met
        if (endRound()) {
            end = true;
        }
        // Increment line counter
        lineCount++;
    } else {

        // End Of File is reached
        playTurn(player, end, savedInputs);
    }
}

void Game::readLineAndQuit(std::ifstream &file, std::string &line, Player *player, bool &end,
                           int &lineCount) {
    if (getline(file, line)) {
        // Vector to store error messages
        std::vector<std::string> errors = checkInput(line, player);

        // If no errors
        if (errors.capacity() == 0) {
            execute(line, player);
        } else {
            std::cout << "Corrupted save file. Error at line " << lineCount << std::endl;
            std::cout << "Disengaging test mode..." << std::endl;
            quitGame();
        }
        // Check if end round condition is met
        if (endRound()) {
            // End loop
            end = true;
        }
        // Increment line counter
        lineCount++;
    } else {
        // Check if End Of File is Reached
        printGameState();
        std::cout << "=== Game Loaded Successfully ===" << std::endl;
        quitGame();
    }
}

void Game::playWithBoxLidAndRandomness() {
    // A vector to save inputs
    std::vector<std::string> savedInputs;

    savedInputs.push_back(RANDOM_MODE_HEADER);
    //Fill Tile Bag
    std::string bag;
    for (int i = 0; i < NUM_OF_TILES_IN_TILE_BAG; ++i) {
        bag += tileBag->get(i)->getName();
    }

    // Save tile bag to input vector;
    savedInputs.push_back(bag);

    // Save seed at the end of the string
    savedInputs.push_back(std::to_string(seed));

    //Add Players to Game
    for (auto &player: players) {
        savedInputs.push_back(player->getName());
    }

    //Add "First" Tile to Centre Factory
    addFirstTileToCenter();

    //Fill Remaining Factories
    fillFactories();

    //Round Number Counter
    int round = 1;

    // While tilebag
    //while (!areTileBagAndBoxLidEmpty())
    bool gameOver = false;
    while (!gameOver) {
        std::cout << "=== Round " << round << " Starts ===" << std::endl;
        // End round if all factories including Centre are empty

        bool end = endRound();
        if (players[0]->isFirst()) {
            while (!end) {
                for (size_t i = 0; i < NUM_OF_PLAYERS && !end; ++i) {
                    auto player = players[i];
                    playTurn(player, end, savedInputs);
                    if (checkIfEndGame()) {
                        end = true;
                        gameOver = true;
                    }
                }
            }
        } else {
            while (!end) {
                for (size_t i = 0; i < NUM_OF_PLAYERS && !end; ++i) {
                    auto player = players[NUM_OF_PLAYERS - 1 - i];
                    playTurn(player, end, savedInputs);
                    if (checkIfEndGame()) {
                        end = true;
                        gameOver = true;
                    }
                }
            }
        }

        // Next Round
        std::cout << "=== Round " << round << " Ends ===" << std::endl;
        round++;

        // Error Checking

        for (auto &player: players) {
            deductBrokenTile(player);
        }

        // Reset game state
        if (!areTileBagAndBoxLidEmpty()) {
            printScores();
            reset();
        }

        // Display box lid at the end of the round
        std::cout << "Box Lid : ";
        for (int i = 0; i < boxLid->getLength(); ++i) {
            std::cout << boxLid->get(i)->getName() << " ";
        }
        std::cout << std::endl;
    }
    std::cout << "=== Game Over ===" << std::endl;
    std::cout << "=== Scoreboard ===" << std::endl;
    printFinalResults();
}

void Game::loadWithBoxLidAndRandomness(const std::string &fileName) {
// Initialize test mode variables
    std::ifstream file;
    file.open(fileName, std::ifstream::in);
    int lineCount = 1;
    std::string line;
    std::string validChars = VALID_CHARS;
    std::vector<Player *> testPlayers;

    // A vector to save inputs
    std::vector<std::string> savedInputs;
    // A variable to store tile bag. This will be used later to validate the tile bag and the seed
    std::string tileBag;

    // Skip first line
    getline(file, line);
    lineCount++;
    savedInputs.push_back(line);

    while (lineCount <= 2) {
        getline(file, line);

        // Validate tile bag input
        int count = 0;
        for (size_t i = 0; i < line.size(); ++i) {
            size_t checked = validChars.find(line[i]);
            if (checked == std::string::npos) {
                std::cout << "Corrupted save file. Tile bag contains invalid characters!" << std::endl;
                std::cout << "Disengaging test mode..." << std::endl;
                quitGame();
            } else {
                count++;
            }
        }
        if (count < NUM_OF_TILES_IN_TILE_BAG || count > NUM_OF_TILES_IN_TILE_BAG) {
            std::cout << "Corrupted save file. Initial tile bag must have exactly 100 tiles!" << std::endl;
            quitGame();
        } else {
            tileBag = line;
            savedInputs.push_back(tileBag);
            // Setting up game
            lineCount++;
        }
    }

    try {
        getline(file, line);
        setSeed(std::stoi(line));
        std::default_random_engine engine(seed);
        std::string tiles;

        if (!isAdvanced) {
            tiles = NORMAL_ALL_TILES;
        }

        shuffleString(tiles, engine);
        if (tiles == tileBag) {
            savedInputs.push_back(line);
            setTileBagAutomatically();
            addFirstTileToCenter();
            fillFactories();
            lineCount++;
        } else {
            std::cout
                    << "Corrupted save file. The tile bag generated by the seed does not match the one in the save file!"
                    << std::endl;
            quitGame();
        }
    }
    catch (std::exception const &e) {
        std::cout << "Corrupted save file. Seed must be a number" << std::endl;
        quitGame();
    }

    // Grab players' names
    while (lineCount <= 5) {
        getline(file, line);
        if (line.empty()) {
            std::cout << "Corrupted save file. A player's name cannot be blank!" << std::endl;
            std::cout << "Disengaging test mode..." << std::endl;
            quitGame();
        } else {
            savedInputs.push_back(line);
        }

        if (lineCount == 4) {
            players.push_back(new Player(line, lineCount - 1, true));
        } else {
            players.push_back(new Player(line, lineCount - 1, false));
        }

        lineCount++;
    }

    // Add players to game;
    addPlayers(testPlayers);

    // Count round
    int round = 1;
    bool gameOver = false;
    while (!gameOver) {
        std::cout << "=== Round " << round << " ===" << std::endl;
        bool end = endRound();
        if (players[0]->isFirst()) {
            while (!end) {
                for (size_t i = 0; i < NUM_OF_PLAYERS && !end; ++i) {
                    auto player = players[i];
                    // Check if End Of File is reached
                    readLineAndPlayTurn(file, line, player, end, savedInputs, lineCount);
                    if (checkIfEndGame()) {
                        end = true;
                        gameOver = true;
                    }
                }
            }
        } else {
            while (!end) {
                for (size_t i = 0; i < NUM_OF_PLAYERS && !end; ++i) {
                    auto player = players[NUM_OF_PLAYERS - 1 - i];
                    // Check if End Of File is reached
                    readLineAndPlayTurn(file, line, player, end, savedInputs, lineCount);
                    if (checkIfEndGame()) {
                        end = true;
                        gameOver = true;
                    }
                }
            }
        }

        // Next Round
        std::cout << "=== Round " << round << " Ends ===" << std::endl;
        round++;
        // Display box lid at the end of the round
        std::cout << "Box Lid : ";
        for (int i = 0; i < boxLid->getLength(); ++i) {
            std::cout << boxLid->get(i)->getName() << " ";
        }
        std::cout << std::endl;

        for (auto &player: players) {
            deductBrokenTile(player);
        }

        // Reset game state
        if (!areTileBagAndBoxLidEmpty()) {
            printScores();
            reset();
        }

    }
    // Cleaning up
    file.close();

    std::cout << "=== Game Over ===" << std::endl;
    std::cout << "=== Scoreboard ===" << std::endl;
    printFinalResults();
    quitGame();
}

void Game::shuffleTileBag() {
    // Setting up

    int max = tileBag->getLength();
    std::default_random_engine engine(seed);
    std::string tiles;

    std::cout << "Length " << tiles.length() << std::endl;

    for (int i = 0; i < max; ++i) {
        tiles += tileBag->get(i)->getName();
    }

    // Clear tilebag
    tileBag->clear();

    // Shuffle
    shuffleString(tiles, engine);

    for (int i = 0; i < max; ++i) {
        tileBag->addBack(new Tile(tiles[i]));
    }
}

void Game::setSeed(const int &s) {
    this->seed = s;
}

int Game::getSeed() {
    return this->seed;
}

bool Game::areTileBagAndBoxLidEmpty() {
    return (tileBag->getLength() == 0 && boxLid->getLength() == 0);
}

void Game::moveTilesFromBoxLidToTileBag() {
    for (int i = 0; i < boxLid->getLength() - 1; ++i) {
        tileBag->addBack(new Tile(boxLid->get(i)->getName()));
    }
    boxLid->clear();
}

void Game::setRandomGameMode(bool random) {
    this->isRandom = random;
}

bool Game::checkIfEndGame() {
    bool result = false;

    // Any player with horizontal line = game over
    for (size_t i = 0; i < players.size(); ++i) {
        for (int j = 0; j < MOSAIC_DIM; ++j) {
            int count = 0;
            for (int k = 0; k < MOSAIC_DIM; ++k) {
                if (std::isupper(players[i]->getGrid()[j][k].getName())) {
                    count++;
                }
                if (count == MOSAIC_DIM) {
                    result = true;
                    i = players.size();
                    j = MOSAIC_DIM;
                    k = MOSAIC_DIM;
                }
            }
        }
    }
    return result;
}

void Game::testLoadRandomGame(char *fileName) {
    // Initialize test mode variables
    std::ifstream file;
    file.open(fileName, std::ifstream::in);
    int lineCount = 1;
    std::string line;
    std::string validChars = VALID_CHARS;
    std::vector<Player *> testPlayers;

    // A variable to store tile bag. This will be used later to validate the tile bag and the seed
    std::string tileBag;

    // Skip first line
    getline(file, line);
    lineCount++;

    while (lineCount <= 2) {
        getline(file, line);

        // Validate tile bag input
        int count = 0;
        for (size_t i = 0; i < line.size(); ++i) {
            size_t checked = validChars.find(line[i]);
            if (checked == std::string::npos) {
                std::cout << "Corrupted save file. Tile bag contains invalid characters!" << std::endl;
                std::cout << "Disengaging test mode..." << std::endl;
                quitGame();
            } else {
                count++;
            }
        }
        if (count < NUM_OF_TILES_IN_TILE_BAG || count > NUM_OF_TILES_IN_TILE_BAG) {
            std::cout << "Corrupted save file. Initial tile bag must have exactly 100 tiles!" << std::endl;
            quitGame();
        } else {
            tileBag = line;
            // Setting up game
            lineCount++;
        }
    }

    try {
        getline(file, line);
        setSeed(std::stoi(line));
        std::default_random_engine engine(seed);
        std::string tiles;

        if (!isAdvanced) {
            tiles = NORMAL_ALL_TILES;
        }

        shuffleString(tiles, engine);
        if (tiles == tileBag) {
            setTileBagAutomatically();
            addFirstTileToCenter();
            fillFactories();
            lineCount++;
        } else {
            std::cout
                    << "Corrupted save file. The tile bag generated by the seed does not match the one in the save file!"
                    << std::endl;
            quitGame();
        }
    }
    catch (std::exception const &e) {
        std::cout << "Corrupted save file. Seed must be a number" << std::endl;
        quitGame();
    }

    // Grab players' names
    while (lineCount <= 5) {
        getline(file, line);
        if (line.empty()) {
            std::cout << "Corrupted save file. A player's name cannot be blank!" << std::endl;
            std::cout << "Disengaging test mode..." << std::endl;
            quitGame();
        }

        if (lineCount == 4) {
            players.push_back(new Player(line, lineCount - 1, true));
        } else {
            players.push_back(new Player(line, lineCount - 1, false));
        }

        lineCount++;
    }

    // Add players to game;
    addPlayers(testPlayers);

    // Count round
    int round = 1;
    bool gameOver = false;
    while (!gameOver) {
        std::cout << "=== Round " << round << " ===" << std::endl;
        bool end = endRound();
        if (players[0]->isFirst()) {
            while (!end) {
                for (size_t i = 0; i < NUM_OF_PLAYERS && !end; ++i) {
                    auto player = players[i];
                    // Check End Of File
                    readLineAndQuit(file, line, player, end, lineCount);
                    if (checkIfEndGame()) {
                        end = true;
                        gameOver = true;
                    }
                }
            }
        } else {
            while (!end) {
                for (size_t i = 0; i < NUM_OF_PLAYERS && !end; ++i) {
                    auto player = players[NUM_OF_PLAYERS - 1 - i];
                    // Check End Of File
                    readLineAndQuit(file, line, player, end, lineCount);
                    if (checkIfEndGame()) {
                        end = true;
                        gameOver = true;
                    }
                }
            }
        }

        // Check if the next line is empty
        if (file.peek() == EOF) {
            printGameState();
            std::cout << "=== Game Loaded Successfully ===" << std::endl;
            quitGame();
        } else {
            round++;
            for (auto &player: players) {
                deductBrokenTile(player);
            }
            // Reset game state
            if (!areTileBagAndBoxLidEmpty()) {
                printScores();
                reset();
            }
        }
    }

    // Cleaning up
    file.close();
}
