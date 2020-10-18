//
// Created by usefulmana on 16/10/20.
//

#include "AdvGame.h"

AdvGame::AdvGame() {
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

    // Default seed
    seed = 1;
}

AdvGame::~AdvGame() {
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
    tileBag->clear();
    delete tileBag;

    // Delete Box Lid
    boxLid->clear();
    delete boxLid;
}

void AdvGame::addPlayers(std::vector<AdvPlayer *> p) {
    // Add Player to back of Vector
    for (auto &player: p) {

        players.push_back(player);
    }
}

std::vector<AdvPlayer *> AdvGame::getPlayers() {
    return players;
}

void AdvGame::play() {
    std::vector<std::string> savedInputs;

    savedInputs.push_back(ADVANCED_MODE_HEADER);

    std::string bag;

    for (int i = 0; i < ADV_NUM_OF_TILES_IN_TILE_BAG; ++i) {
        bag += tileBag->get(i)->getName();
    }
    // Save tile bag to input vector;
    savedInputs.push_back(bag);

    savedInputs.push_back(std::to_string(seed));

    // Save players name
    for (auto &player: players) {
        savedInputs.push_back(player->getName());
    }

    //Add "First" Tile to Centre Factory
    addFirstTileToCenter();

    //Fill Remaining Factories
    fillFactories();

    //Round Number Counter
    int round = 1;

    bool gameOver = false;
    while (!gameOver) {
        std::cout << "=== Round " << round << " Starts ===" << std::endl;
        bool end = endRound();
        if (players[0]->isFirst()) {
            while (!end) {
                for (size_t i = 0; i < NUM_OF_PLAYERS && !end; ++i) {
                    auto player = players[i];
                    if (checkIfEndGame()) {
                        end = true;
                        gameOver = true;
                    } else {
                        playTurn(player, end, savedInputs);
                    }
                }
            }
        } else {
            while (!end) {
                for (size_t i = 0; i < NUM_OF_PLAYERS && !end; ++i) {
                    auto player = players[NUM_OF_PLAYERS - 1 - i];
                    if (checkIfEndGame()) {
                        end = true;
                        gameOver = true;
                    } else {
                        playTurn(player, end, savedInputs);
                    }

                }
            }
        }

        engageTilePlacingPhase(savedInputs);

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

void AdvGame::testLoadGame(char *fileName) {
    std::ifstream file;
    file.open(fileName, std::ifstream::in);
    int lineCount = 1;
    std::string line;
    std::string validChars = ADV_VALID_CHARS;
    std::vector<AdvPlayer *> testPlayers;
    std::vector<std::string> savedInputs;

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
        if (count < ADV_NUM_OF_TILES_IN_TILE_BAG || count > ADV_NUM_OF_TILES_IN_TILE_BAG) {
            std::cout << "Corrupted save file. Initial tile bag must have exactly 120 tiles!" << std::endl;
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
        std::string tiles = ADV_ALL_TILES;

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
            players.push_back(new AdvPlayer(line, lineCount - 1, true));
        } else {
            players.push_back(new AdvPlayer(line, lineCount - 1, false));
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
                    if (checkIfEndGame()) {
                        end = true;
                        gameOver = true;
                    }
                    readLineAndQuit(file, line, player, end, lineCount);
                }
            }
        } else {
            while (!end) {
                for (size_t i = 0; i < NUM_OF_PLAYERS && !end; ++i) {
                    auto player = players[NUM_OF_PLAYERS - 1 - i];
                    // Check End Of File
                    if (checkIfEndGame()) {
                        end = true;
                        gameOver = true;
                    }
                    readLineAndQuit(file, line, player, end, lineCount);
                }
            }
        }
        testLoadTilePlacingPhase(file, line, lineCount, savedInputs);

        // Check if the next line is empty
        if (file.peek() == EOF) {
            for (auto &player: players) {
                deductBrokenTile(player);
            }
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

void AdvGame::load(const std::string &fileName) {
    // Initialize test mode variables
    std::ifstream file;
    file.open(fileName, std::ifstream::in);
    int lineCount = 1;
    std::string line;
    std::string validChars = ADV_VALID_CHARS;
    std::vector<AdvPlayer *> testPlayers;

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
        if (count < ADV_NUM_OF_TILES_IN_TILE_BAG || count > ADV_NUM_OF_TILES_IN_TILE_BAG) {
            std::cout << "Corrupted save file. Initial tile bag must have exactly 120 tiles!" << std::endl;
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
        std::string tiles = ADV_ALL_TILES;

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
            players.push_back(new AdvPlayer(line, lineCount - 1, true));
        } else {
            players.push_back(new AdvPlayer(line, lineCount - 1, false));
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
                    if (checkIfEndGame()) {
                        end = true;
                        gameOver = true;
                    } else {
                        readLineAndPlayTurn(file, line, player, end, savedInputs, lineCount);
                    }

                }
            }
        } else {
            while (!end) {
                for (size_t i = 0; i < NUM_OF_PLAYERS && !end; ++i) {
                    auto player = players[NUM_OF_PLAYERS - 1 - i];
                    // Check if End Of File is reached
                    if (checkIfEndGame()) {
                        end = true;
                        gameOver = true;
                    } else {
                        readLineAndPlayTurn(file, line, player, end, savedInputs, lineCount);
                    }
                }
            }
        }
        if (!checkIfEndGame()) {
            loadTilePlacingPhase(file, line, lineCount, savedInputs);
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

void AdvGame::execute(const std::string &command, AdvPlayer *player) {
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

//    moveExcessTilesToCenter(factories, factory, center);
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
//    setWhoGoesFirstNextRound(center, factory, chosenTiles, player, players);
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

    // If the player choose not to discard the tiles
    if (targetRow != 0) {
        placeOnRow(targetRow, player, chosenTiles);

        // Move excess tiles to deduct row
        handleFirstTile(chosenTiles, player, boxLid);

    } else {
        handleFirstTile(chosenTiles, player, boxLid);
    }
}

void AdvGame::setTileBagAutomatically() {
    std::default_random_engine engine(seed);
    std::string tiles = ADV_ALL_TILES;

    shuffleString(tiles, engine);
    for (size_t i = 0; i < tiles.length(); ++i) {
        tileBag->addBack(new Tile(tiles[i]));
    }
}

void AdvGame::setTileBagFromString(const std::string &line) {
    //Initialise Tile Bag
    tileBag = new LinkedList<Tile *>();

    //Fill Tile Bag
    for (size_t i = 0; i < line.length(); ++i) {
        tileBag->addBack(new Tile(line[i]));
    }
}

void AdvGame::fillFactories() {
    // Fill factories with tiles from the tile bag
    for (int i = 0; i < NUM_OF_FACTORIES && tileBag->getLength() > 0; ++i) {
        for (int j = 0; j < FACTORY_SIZE && tileBag->getLength() > 0; ++j) {
            factories[i][j].setName(tileBag->get(0)->getName());

            //Remove tile from tile bag
            tileBag->popFront();
        }
    }
}


void AdvGame::setSeed(const int &s) {
    this->seed = s;
}

bool AdvGame::endRound() {
    return isCenterEmpty(center) && areFactoriesEmpty(factories);
}

void AdvGame::printFinalResults() {

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

void AdvGame::printScores() {
    for (auto &player : players) {
        std::cout << "Score for " << player->getName() << ": " << player->getScore()
                  << std::endl;
    }
}

int AdvGame::getSeed() {
    return seed;
}

void AdvGame::addFirstTileToCenter() {
    center.push_back(new Tile(FIRST_TILE));
}

void AdvGame::playTurn(AdvPlayer *player, bool &end, std::vector<std::string> &savedInputs) {
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
        std::vector<std::string> errors = checkAdvInput(input, player, ADV_VALID_CHARS, factories, center);

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

void
AdvGame::interpretCommand(std::string &input, AdvPlayer *player, bool &validInput,
                          std::vector<std::string> &savedInputs) {
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

        std::cout << "Saved to  " << fileName << std::endl;
    }
}

void AdvGame::printNewTurnInformation(AdvPlayer *player) {
    std::cout << "TURN FOR PLAYER: " << player->getName() << std::endl;
    std::cout << "Factories:" << std::endl;
    printFactories(factories, center);
    std::cout << std::endl;
    std::cout << "Mosaic for " << player->getName() << ":" << std::endl;
    player->printMosaic();
    player->printBrokenRow();
    std::cout << std::endl;
}

bool AdvGame::checkIfEndGame() {
    bool result = false;

    // Any player with horizontal line = game over
    for (size_t i = 0; i < players.size(); ++i) {
        for (int j = 0; j < ADV_MOSAIC_DIM; ++j) {
            int count = 0;
            for (int k = 0; k < ADV_MOSAIC_DIM; ++k) {
                if (players[i]->getMosaic()[j][k].getName() != NO_TILE) {
                    count++;
                }
                if (count == ADV_MOSAIC_DIM) {
                    result = true;
                    i = players.size();
                    j = ADV_MOSAIC_DIM;
                    k = ADV_MOSAIC_DIM;
                }
            }
        }
    }
    return result;
}

void AdvGame::deductBrokenTile(AdvPlayer *player) {
    int deductBy = 0;
    int count = 0;
    std::cout << "Deducting points " << std::endl;
    //Check contents of Player's Broken Row
    for (int i = 0; i < ADV_BROKEN_ROW_SIZE; i++) {
        if (player->getBrokenRow()[i].getName() != WHITESPACE) {
            count++;
            if (count < ADV_BROKEN_ROW_SIZE - 4) {
                // First three tiles -1 each
                deductBy++;
            } else if (count <= ADV_BROKEN_ROW_SIZE - 3) {
                // Nx two tiles -2 each
                deductBy += 2;
            } else if (count <= ADV_BROKEN_ROW_SIZE - 1) {
                // Nx two tiles -3 each
                deductBy += 3;
            } else {
                deductBy += 4;
            }

        }
    }
    std::cout << "Deduct by " << deductBy << std::endl;
    //Perform deduction
    int score = player->getScore() - deductBy;

    //Allocate Player Score
    if (score > 0) {
        player->setScore(score);
    } else {
        player->setScore(0);
    }

}

void AdvGame::reset() {
    // Fill factories from tile bag
    fillFactories();
    // Add First tile to center
    addFirstTileToCenter();

    for (auto &player: players) {
        // Reset Broken Row
        for (int i = 0; i < ADV_BROKEN_ROW_SIZE; ++i) {
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
        for (int i = 0; i < ADV_MOSAIC_DIM; ++i) {
            if (isAdvRowFull(i + 1, player)) {
                for (int j = 0; j < rowCount; ++j) {
                    player->getUnlaidRow()[i][j].setName(NO_TILE);
                }
            }
            rowCount++;
        }
    }

    // Add Boxlid tile to tilebag
    if (tileBag->getLength() == 0 && boxLid->getLength() > 0) {
        moveTilesFromBoxLidToTileBag();
        // Shuffle the bag
        shuffleTileBag();
    }
}

bool AdvGame::areTileBagAndBoxLidEmpty() {
    return (tileBag->getLength() == 0 && boxLid->getLength() == 0);
}

void AdvGame::shuffleTileBag() {
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

void AdvGame::moveTilesFromBoxLidToTileBag() {
    for (int i = 0; i < boxLid->getLength() - 1; ++i) {
        tileBag->addBack(new Tile(boxLid->get(i)->getName()));
    }
    boxLid->clear();
}

std::string AdvGame::getPlaceCommand() {
    std::string result;
    std::cout << "> ";
    getline(std::cin, result);
    std::cout << std::endl;
    if (std::cin.eof()) {
        quitGame();
    }
    return result;
}

void AdvGame::engageTilePlacingPhase(std::vector<std::string> &savedInputs) {
    std::cout << "==== Tile Placing Phase ====" << std::endl;

    for (size_t i = 0; i < players.size(); ++i) {
        // Loop until no more tiles need to be place
        // Get All Tiles Need To Be Place
        std::string toBePlaced = getRowsToBePlaced(players[i]);
        std::cout << std::endl;
        std::cout << "======================================" << std::endl;
        std::cout << "TURN FOR PLAYER " << players[i]->getName() << std::endl;
        std::cout << "To place a tile on the mosaic: place <row> <color> <column>" << std::endl;
        size_t count = 1;
        while (count <= toBePlaced.length()) {
            players[i]->printMosaic();
            std::string command = getPlaceCommand();
            std::vector<std::string> errors = validatePlaceCommand(command, players[i]);
            if (errors.capacity() == 0) {
                if (command.substr(0, 5) == "place") {
                    place(players[i], command, savedInputs);
                    savedInputs.push_back(command);
                    count++;
                } else {
                    // Find position of first whitespace
                    int pos = command.find(WHITESPACE);

                    // Return substring of everything following the whitespace
                    std::string fileName = command.substr(pos + 1);
                    save(fileName, savedInputs);
                    std::cout << "Saved to" << fileName << std::endl;
                }

            } else {
                std::cout << "Errors: " << std::endl;
                for (auto &e: errors) {
                    std::cout << "- " << e << std::endl;
                }
            }
        }
        std::cout << "No more tile left to be placed. Ending turn! " << std::endl;

    }
}

void AdvGame::printGameState() {
    std::cout << "Factories: " << std::endl;
    printFactories(factories, center);
    std::cout << std::endl;

    for (auto &testPlayer: players) {
        std::cout << "Score for player " << testPlayer->getName() << ": " << testPlayer->getScore() << std::endl;
        std::cout << "Mosaic for " << testPlayer->getName() << ":" << std::endl;
        testPlayer->printMosaic();
        testPlayer->printBrokenRow();
        std::cout << std::endl;
    }
}

void AdvGame::place(AdvPlayer *player, const std::string &command, std::vector<std::string> &savedInputs) {
    std::vector<std::string> inputVector = splitString(command, WHITESPACE);
    int row = std::stoi(inputVector[1]);
    char color = inputVector[2][0];
    int column = std::stoi(inputVector[3]);
    player->getMosaic()[row - 1][column - 1].setName(color);
    score(player, row, column, color);
}

bool AdvGame::isTileAlone(int row, int col, Tile **mosaic) {
    bool alone = true;
    // check left
    if (col - 1 >= 0) {
        if (mosaic[row][col - 1].getName() != '.') {
            alone = false;
        }
    }

    // check right
    if (col + 1 < ADV_MOSAIC_DIM) {
        if (mosaic[row][col + 1].getName() != '.') {
            alone = false;
        }
    }

    // check up
    if (row - 1 >= 0) {
        if (mosaic[row - 1][col].getName() != '.') {
            alone = false;
        }
    }

    // check down
    if (row + 1 < ADV_MOSAIC_DIM) {
        if (mosaic[row + 1][col].getName() != '.') {
            alone = false;
        }
    }

    return alone;
}

bool AdvGame::isTileAdjacentHozVer(int row, int col, Tile **mosaic) {
    bool adjacent = false;
    // Up left
    if (row - 1 >= 0 && col - 1 >= 0){
        if (mosaic[row - 1][col].getName() != NO_TILE && mosaic[row][col - 1].getName() != NO_TILE) {
            adjacent = true;
        }
    }

    // up right
    if (row - 1 >= 0 && col + 1 < ADV_MOSAIC_DIM){
        if (mosaic[row - 1][col].getName() != NO_TILE && mosaic[row][col + 1].getName() != NO_TILE) {
            adjacent = true;
        }
    }


    // down left
    if (row + 1 < ADV_MOSAIC_DIM && col - 1 >= 0){
        if (mosaic[row + 1][col].getName() != NO_TILE && mosaic[row][col - 1].getName() != NO_TILE) {
            adjacent = true;
        }
    }
    // down right
    if (row + 1< ADV_MOSAIC_DIM && col + 1 < ADV_MOSAIC_DIM){
        if (mosaic[row + 1][col].getName() != NO_TILE && mosaic[row][col + 1].getName() != NO_TILE) {
            adjacent = true;
        }
    }


    return adjacent;
}


void AdvGame::score(AdvPlayer *player, int row, int col, char color) {
    int score = player->getScore();
    // Initialize variables
    int horizontalPoints = 0;
    int verticalPoints = 0;
    int finalScore;
    int x = row - 1;
    int y = col - 1;
    Tile **mosaic = player->getMosaic();

    // Check if tile is alone
    if (isTileAlone(x, y, mosaic)) {
        finalScore = score + 1;
    } else {
        // Horizontal scoring
        // Check Left
        bool left = true;
        int leftIndex = 0;
        while (left) {
            if (y - leftIndex >= 0) {
                if (mosaic[x][y - leftIndex].getName() != NO_TILE) {
                    horizontalPoints++;
                    leftIndex++;
                } else {
                    left = false;
                }
            } else {
                left = false;
            }
        }

        // Check right
        bool right = true;
        int rightIndex = 1;
        while (right) {
            if (y + leftIndex < ADV_MOSAIC_DIM) {
                if (mosaic[x][y + rightIndex].getName() != NO_TILE) {
                    horizontalPoints++;
                    rightIndex++;
                } else {
                    right = false;
                }
            } else {
                right = false;
            }
        }

        // Vertical scoring
        // Check up
        bool up = true;
        int upIndex = 1;
        while (up) {
            if (x - upIndex >= 0) {
                if (mosaic[x - upIndex][y].getName() != NO_TILE) {
                    verticalPoints++;
                    upIndex++;
                } else {
                    up = false;
                }
            } else {
                up = false;
            }
        }


        // Check down
        bool down = true;
        int downIndex = 1;
        while (down) {
            if (x + downIndex < ADV_MOSAIC_DIM) {
                if (mosaic[x + downIndex][y].getName() != NO_TILE) {
                    verticalPoints++;
                    downIndex++;
                } else {
                    down = false;
                }
            } else {
                down = false;
            }
        }

        // Compensate for missing points
        if (isTileAdjacentHozVer(x, y, mosaic)){
            verticalPoints++;
        }


        // Subtract 1 or nah?
        finalScore = score + verticalPoints + horizontalPoints;
    }
    player->setScore(finalScore);
}

std::vector<std::string> AdvGame::validatePlaceCommand(const std::string &command, AdvPlayer *player) {

    std::vector<std::string> errors;

    std::vector<std::string> inputVector = splitString(command, WHITESPACE);

    std::string colors = ADV_VALID_CHARS;

    // Check if save argument number was entered
    if (inputVector.size() == 2) {
        // Check for save command
        if (inputVector[0] != "save") {
            errors.push_back("Invalid input. Correct input = save. Your input = " + inputVector[0]);
        }
    } else if (inputVector.size() == 4) {
        if (inputVector[0] != "place") {
            errors.push_back("Invalid Input!. Please use the 'place' command!");
        }

        char color = inputVector[2][0];
        size_t found = colors.find(color);
        if (found == std::string::npos) {
            errors.push_back("<color> must be one of these values: R, Y, B, L, U or O in advanced mode");
        }

        try {
            int row = std::stoi(inputVector[1]);

            int column = std::stoi(inputVector[3]);

            if (row < ADV_MIN_ROW || row > ADV_MAX_ROW) {
                errors.push_back("<row> must be a number between 1 and 6");
            } else {
                if (column < ADV_MIN_COL || column > ADV_MAX_COL) {
                    errors.push_back("<column> must be a number between 1 and 6");
                } else {
                    if (getAdvColorOfaRow(row, player) != color) {
                        errors.push_back("The chosen row does not contain such color!");
                    } else {
                        if (!isRowQualifiedToBePlaced(player, row)) {
                            errors.push_back("The row is not yet full!");
                        } else {
                            if (!canColorBePlacedInARow(player, row)) {
                                errors.push_back("Illegal Move! The chosen row has already contained this color!");
                            } else {
                                if (!canColorBePlacedInAColumn(color, column, player)) {
                                    errors.push_back(
                                            "Illegal Move! The chosen column has already contained this color!");
                                }
                                else {
                                    if (checkIfSpotIsOccupied(row, column, player)){
                                        errors.push_back("That spot is occupied!");
                                    }
                                }
                            }
                        }
                    }
                }
            }

        }
        catch (std::exception const &e) {
            errors.push_back("<row> must be a number between 1 and 6");
            errors.push_back("<column> must be a number between 1 and 6");
        }


    } else {
        errors.push_back("Invalid number of args. Look out for excessive whitespaces.");
    }

    return errors;
}

bool AdvGame::checkIfSpotIsOccupied(int row, int col, AdvPlayer *player) {
    return player->getMosaic()[row - 1][col - 1].getName() != NO_TILE;
}


bool AdvGame::canColorBePlacedInARow(AdvPlayer *player, int row) {
    bool possible = true;
    char color = getAdvColorOfaRow(row, player);
    for (int i = 0; i < ADV_MOSAIC_DIM; ++i) {
        if (player->getMosaic()[row - 1][i].getName() == color) {
            possible = false;
            i = ADV_MOSAIC_DIM;
        }
    }

    return possible;
}

bool AdvGame::canColorBePlacedInAColumn(const char &color, int column, AdvPlayer *player) {
    bool possible = true;
    for (int i = 0; i < ADV_MOSAIC_DIM; ++i) {
        if (player->getMosaic()[i][column - 1].getName() == color) {
            possible = false;
            i = ADV_MOSAIC_DIM;
        }
    }

    return possible;
}

bool AdvGame::isRowQualifiedToBePlaced(AdvPlayer *player, int row) {
    bool qualified = false;
    char color = getAdvColorOfaRow(row, player);
    int count = 0;
    for (int i = 0; i < row; ++i) {
        if (player->getUnlaidRow()[row - 1][i].getName() == color) {
            count++;
        }
        if (count == row) {
            qualified = true;
        }
    }

    return qualified;
}

std::string AdvGame::getRowsToBePlaced(AdvPlayer *player) {
    std::string toBePlaced;

    int rowCount = 1;
    for (int i = 0; i < ADV_MOSAIC_DIM; ++i) {
        int count = 0;
        for (int j = 0; j < rowCount; ++j) {
            if (player->getUnlaidRow()[i][j].getName() != '.') {
                count++;
            }
            if (count == rowCount) {
                toBePlaced += player->getUnlaidRow()[i][j].getName();
            }
        }
        rowCount++;
    }

    return toBePlaced;
}

void AdvGame::readLineAndPlayTurn(std::ifstream &file, std::string &line, AdvPlayer *player, bool &end,
                                  std::vector<std::string> &savedInputs, int &lineCount) {
    if (getline(file, line)) {
        // Vector to store error messages
        std::vector<std::string> errors = checkAdvInput(line, player, ADV_VALID_CHARS, factories, center);

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

void AdvGame::loadTilePlacingPhase(std::ifstream &file, std::string &line, int &lineCount,
                                   std::vector<std::string> &savedInputs) {

    std::cout << "==== Tile Placing Phase ====" << std::endl;

    for (size_t i = 0; i < players.size(); ++i) {
        // Loop until no more tiles need to be place
        // Get All Tiles Need To Be Place
        std::cout << std::endl;
        std::cout << "======================================" << std::endl;
        std::cout << "TURN FOR PLAYER " << players[i]->getName() << std::endl;
        std::cout << "To place a tile: place <row> <color> <column>" << std::endl;
        std::string toBePlaced = getRowsToBePlaced(players[i]);
        size_t count = 1;

        while (count <= toBePlaced.length()) {
            players[i]->printMosaic();
            std::cout << std::endl;
            std::string command;
            if (getline(file, line)) {
                command = line;
                lineCount++;
            } else {
                std::cout << "Player " << players[i]->getName() << " continues" << std::endl;
                command = getPlaceCommand();
            }
            std::vector<std::string> errors = validatePlaceCommand(command, players[i]);
            if (errors.capacity() == 0) {

                if (command.substr(0, 5) == "place") {
                    place(players[i], command, savedInputs);
                    savedInputs.push_back(command);
                    count++;
                } else {
                    // Find position of first whitespace
                    int pos = command.find(WHITESPACE);

                    // Return substring of everything following the whitespace
                    std::string fileName = command.substr(pos + 1);
                    save(fileName, savedInputs);
                    std::cout << "Saved to " << fileName << std::endl;
                }
            } else {
                std::cout << "Errors: " << std::endl;
                for (auto &e: errors) {
                    std::cout << "- " << e << std::endl;
                }
            }
        }
        std::cout << "No more tile left to be placed. Ending turn! " << std::endl;
        std::cout << std::endl;
    }

}

void AdvGame::readLineAndQuit(std::ifstream &file, std::string &line, AdvPlayer *player, bool &end, int &lineCount) {
    if (getline(file, line)) {
        // Vector to store error messages
        std::vector<std::string> errors = checkAdvInput(line, player, ADV_VALID_CHARS, factories, center);

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

void AdvGame::testLoadTilePlacingPhase(std::ifstream &file, std::string &line, int &lineCount,
                                       std::vector<std::string> &savedInputs) {
    std::cout << "==== Tile Placing Phase ====" << std::endl;

    for (size_t i = 0; i < players.size(); ++i) {
        // Loop until no more tiles need to be place
        // Get All Tiles Need To Be Place
        std::string toBePlaced = getRowsToBePlaced(players[i]);

        size_t count = 1;

        while (count <= toBePlaced.length()) {
            std::string command;
            if (getline(file, line)) {
                command = line;
                lineCount++;
            } else {
                std::cout << "Game Loaded Successfully" << std::endl;
                printGameState();
                printFinalResults();
                quitGame();
            }
            std::vector<std::string> errors = validatePlaceCommand(command, players[i]);
            if (errors.capacity() == 0) {
                savedInputs.push_back(command);
                place(players[i], command, savedInputs);
                count++;
            } else {
                std::cout << "Errors: " << std::endl;
                for (auto &e: errors) {
                    std::cout << "- " << e << std::endl;
                }
            }
        }
        std::cout << "No more tile left to be placed. Ending turn! " << std::endl;

    }
}

