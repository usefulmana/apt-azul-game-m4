#include <iostream>
#include <limits>
#include <vector>
#include <string>
#include "Types.h"
#include "Game.h"
#include "Player.h"
#include "utils.h"
#include "AdvPlayer.h"
#include "AdvGame.h"

int showMenu();

[[noreturn]] void playAzul();

void showCredits();

void playGame();

void loadGame();

std::string getFile();

std::vector<Player *> createPlayersFromUserInput();

int getSeedFromUserInput();

std::vector<AdvPlayer *> getAdvancedPlayers();

bool isNameValid(const std::string &name);

void engageTestMode(char *fileName);

[[noreturn]] void engageRandomMode(int seed);

[[noreturn]] void engageAdvancedMode();

std::string detectSaveGameType(const std::string &fileName);

int main(int argc, char **argv) {
    // Check number of argument
    if (argc == 1) {
        // No additional arguments shows menu
        playAzul();
    } else if (argc == 2) {
        std::string advFlag = "--adv";
        if (argv[1] == advFlag) {
            engageAdvancedMode();

        }
    } else if (argc == 3) {
        // 2 additional arguments directs to test mode
        std::vector<std::string> flags;
        flags.emplace_back("-t");
        flags.emplace_back("-s");
        // Check for Flag
        if (argv[1] == flags[0]) {
            // If File Exists
            if (checkIfFileExists(argv[2])) {
                engageTestMode(argv[2]);
            } else {
                std::cout << "No such file exists!" << std::endl;
            }
        } else if (argv[1] == flags[1]) {
            try {
                int seed = std::stoi(argv[2]);
                engageRandomMode(seed);
            }
            catch (std::exception const &e) {
                std::cout << "You entered: " << argv[2] << std::endl;
                std::cout << "Please enter an integer number " << std::endl;
            }
        } else {
            std::cout << "Wrong flag" << std::endl;
        }

    } else {
        std::cout << "Invalid number of arguments" << std::endl;
        std::cout << "Default mode : ./azul" << std::endl;
        std::cout << "Test mode    : ./azul -t <testfile>" << std::endl;
        std::cout << "Random mode  : ./azul -s <seed>" << std::endl;
        std::cout << "Advanced mode: ./azul --adv" << std::endl;
    }
    return EXIT_SUCCESS;
}

/**
 * Displays Initial Menu and Get User's Input
 * @return: user input
 */
int showMenu() {
    // Welcome message
    std::cout << "Welcome to Azul!" << std::endl;
    std::cout << "-----------------------" << std::endl;
    std::cout << std::endl;
    int result = 0;
    bool endLoop = false;

    while (!endLoop) {
        // Print Menu Contents
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
            result = choice;
            endLoop = true;
        }
    }
    return result;
}

[[noreturn]] void playAzul() {
    while (true) {
        int choice = showMenu();
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
 * This function will initialize an Azul game
 */
void playGame() {
    std::cout << std::endl;
    std::cout << "Starting a new Azul game" << std::endl;
    std::cout << std::endl;

    // Game Initialization
    auto game = new Game();
    game->addPlayers(createPlayersFromUserInput());
    game->setTileBagAutomatically();

    std::cout << "Let's Play!" << std::endl;
    std::cout << std::endl;

    // Play the game
    game->play();

    std::cout << "=== Game Over ===" << std::endl;
    std::cout << "=== Scoreboard ===" << std::endl;

    // Print Scores
    game->printFinalResults();

}

/**
 * Get file name from user input
 * @return file name
 */
std::string getFile() {
    bool valid = false;
    std::string fileName;

    // Clear input
    std::cin.clear();
    std::cin.ignore(10000, '\n');

    std::cout << "Enter the name of save file: " << std::endl;
    while (!valid) {

        std::cout << "> ";

        // Grab file name
        getline(std::cin, fileName);

        // Check EOF
        if (!std::cin) {
            quitGame();
        }
        // Check if file exists
        if (checkIfFileExists(fileName.c_str())) {
            // Break loop
            valid = true;
        } else {
            // Display error message
            std::cout << "No such file exists. Please try again!" << std::endl;
        }
    }
    return fileName;
}

/**
 * This functional will load an Azul game from a file
 */
void loadGame() {

    // Initialize New Game
    auto game = new Game();
    // Load game from file
    game->load(getFile());
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
    // Clear input
    std::cin.clear();
    std::cin.ignore(10000, '\n');
    // End loop when num of players exceeds the ceiling
    while (playerCount <= NUM_OF_PLAYERS) {
        std::string name;
        std::string savedName;
        std::cout << "Enter a name for player " << playerCount << std::endl;
        std::cout << "> ";

        getline(std::cin, name);
        std::cout << std::endl;

        // Check end of file
        if (std::cin.eof()) {
            quitGame();
        }
            // Validate input
        else if (isNameValid(name)) {
            // Increase count by one

            // Initialize and add player object to the vector
            if (playerCount == 1) {
                players.push_back(new Player(name, playerCount, true));
            } else {
                players.push_back(new Player(name, playerCount, false));
            }
            playerCount++;
        } else {
            std::cout << "Invalid name. Please try again" << std::endl;
        }
    }
    return players;
}


std::vector<AdvPlayer *> getAdvancedPlayers() {
    // A vector to store player objects
    std::vector<AdvPlayer *> players;

    // Player counter
    int playerCount = 1;
    // Clear input
    std::cin.clear();
    std::cin.ignore(10000, '\n');
    // End loop when num of players exceeds the ceiling
    while (playerCount <= NUM_OF_PLAYERS) {
        std::string name;
        std::string savedName;
        std::cout << "Enter a name for player " << playerCount << std::endl;
        std::cout << "> ";

        getline(std::cin, name);
        std::cout << std::endl;

        // Check end of file
        if (std::cin.eof()) {
            quitGame();
        }
            // Validate input
        else if (isNameValid(name)) {
            // Increase count by one

            // Initialize and add player object to the vector
            if (playerCount == 1) {
                players.push_back(new AdvPlayer(name, playerCount, true));
            } else {
                players.push_back(new AdvPlayer(name, playerCount, false));
            }
            playerCount++;
        } else {
            std::cout << "Invalid name. Please try again" << std::endl;
        }
    }
    return players;
}

void engageTestMode(char *fileName) {
    // Initialize New Game
    auto game = new Game();
    auto advGame = new AdvGame();
    // Load game from file
    std::string type = detectSaveGameType(fileName);
    if (type == "default") {
        std::cout << "Loading A Default Game" << std::endl;
        game->testLoadGame(fileName);
    } else if (type == "random") {
        std::cout << "Loading A 'Random/Boxlid' Game" << std::endl;
        game->testLoadRandomGame(fileName);
    } else if (type == "adv"){
        std::cout << "Loading An Advanced Game" << std::endl;
        advGame->testLoadGame(fileName);
    }
}


[[noreturn]] void engageRandomMode(int seed) {
    std::cout << "Random Mode Engaged " << std::endl;
    std::cout << "Seed: " << seed << std::endl;
    auto game = new Game();

    while (true) {
        int choice = showMenu();
        game->setRandomGameMode(true);
        game->setSeed(seed);
        if (choice == 1) {
            game->addPlayers(createPlayersFromUserInput());
            game->setTileBagAutomatically();
            game->playWithBoxLidAndRandomness();
        } else if (choice == 2) {
            std::string fileName = getFile();
            std::string type = detectSaveGameType(fileName);
            if (type == "default") {
                game->load(fileName);
            } else if (type == "random") {
                game->loadWithBoxLidAndRandomness(fileName);
            }
        } else if (choice == 3) {
            showCredits();
        } else if (choice == 4) {
            quitGame();
        }
    }
}


[[noreturn]] void engageAdvancedMode() {
    std::cout << "Advanced Mode Engaged " << std::endl;
    auto game = new Game();
    auto advGame = new AdvGame();

    while (true) {
        int choice = showMenu();
        if (choice == 1) {
            advGame->setSeed(getSeedFromUserInput());
            advGame->addPlayers(getAdvancedPlayers());
            advGame->setTileBagAutomatically();
            advGame->play();
        } else if (choice == 2) {
            std::string fileName = getFile();
            std::string type = detectSaveGameType(fileName);
            if (type == "default") {
                game->load(fileName);
            } else if (type == "random") {
                game->loadWithBoxLidAndRandomness(fileName);
            } else if (type == "adv") {
                advGame->load(fileName);
            }
        } else if (choice == 3) {
            showCredits();
        } else if (choice == 4) {
            quitGame();
        }
    }
}

int getSeedFromUserInput(){
    int seed = 1;
    bool validInput = false;
    while(!validInput){
        std::cout << "Enter a number to generate a unique game" << std::endl;
        std::cout << "> ";
        std::cin >> seed;
        if (std::cin.eof()) {
            quitGame();
        }

        if (std::cin.fail()){
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "The seed must be an integer number!" << std::endl;
            std::cout << std::endl;
        }
        else {
            validInput = true;
        }
    }

    return seed;
}

std::string detectSaveGameType(const std::string &fileName) {
    std::ifstream file;
    file.open(fileName, std::ifstream::in);
    std::string line;
    std::string result = "default";

    getline(file, line);
    if (line == RANDOM_MODE_HEADER) {
        result = "random";
    } else if (line == ADVANCED_MODE_HEADER) {
        result = "adv";
    }
    file.close();
    return result;
}