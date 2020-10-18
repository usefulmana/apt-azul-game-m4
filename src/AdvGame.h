//
// Created by usefulmana on 16/10/20.
//

#ifndef A2_ADVGAME_H
#define A2_ADVGAME_H
#include <vector>
#include <iostream>
#include <string>
#include "Types.h"
#include "AdvPlayer.h"
#include "LinkedList.h"
#include <random>
#include "utils.h"

class AdvGame {
private:
    std::vector<AdvPlayer*> players;

    LinkedList<Tile*> * tileBag;

    LinkedList<Tile*> * boxLid;

    // Factories
    Tile ** factories;

    std::vector<Tile*> center;

    int seed;
public:
    AdvGame();
    ~AdvGame();
    void play();
    void load(const std::string & fileName);
    void testLoadGame(char* fileName);
    void addPlayers(std::vector<AdvPlayer*> p);
    std::vector<AdvPlayer*> getPlayers();
    void setTileBagAutomatically();
    void setTileBagFromString(const std::string & line);
    void addFirstTileToCenter();
    void execute(const std::string & command, AdvPlayer * player);
    void printNewTurnInformation(AdvPlayer * player);
    bool canColorBePlacedInARow(AdvPlayer * player, int row);
    bool canColorBePlacedInAColumn(const char & color, int column, AdvPlayer * player);
    void fillFactories();
    void playTurn(AdvPlayer *player, bool &end, std::vector<std::string> &savedInputs);
    void interpretCommand(std::string & input, AdvPlayer * player, bool & valid, std::vector<std::string> & savedInputs);
    void reset();
    bool endRound();
    bool isTileAlone(int row, int col, Tile ** mosaic);
    bool isTileAdjacentHozVer(int row, int col, Tile ** mosaic);
    void score(AdvPlayer * player, int row, int col, char color);
    void engageTilePlacingPhase(std::vector<std::string> & savedInputs);
    void loadTilePlacingPhase(std::ifstream &file, std::string &line, int &lineCount, std::vector<std::string> & savedInputs);
    void readLineAndQuit(std::ifstream &file, std::string &line, AdvPlayer *player, bool &end,
                         int &lineCount);
    void testLoadTilePlacingPhase(std::ifstream &file, std::string &line, int &lineCount, std::vector<std::string> & savedInputs);
    std::string getPlaceCommand();
    std::vector<std::string> validatePlaceCommand(const std::string & command, AdvPlayer * player);
    void place(AdvPlayer * player, const std::string & command, std::vector<std::string> & savedInputs);
    void readLineAndPlayTurn(std::ifstream &file, std::string &line, AdvPlayer *player, bool &end,
                                   std::vector<std::string> &savedInputs, int &lineCount);
    std::string getRowsToBePlaced(AdvPlayer * player);
    bool checkIfSpotIsOccupied(int row, int col, AdvPlayer * player);
    bool isRowQualifiedToBePlaced(AdvPlayer * player, int row);
    void printGameState();
    void printFinalResults();
    void deductBrokenTile(AdvPlayer * player);
    void printScores();
    void shuffleTileBag();
    bool areTileBagAndBoxLidEmpty();
    void moveTilesFromBoxLidToTileBag();
    bool checkIfEndGame();
    void setSeed(const int & s);
    int getSeed();
};


#endif //A2_ADVGAME_H
