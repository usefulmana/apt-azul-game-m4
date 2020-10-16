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
    void fillFactories();
    void reset();
    void printFactories();
    bool isCenterEmpty();
    bool areFactoriesEmpty();
    std::vector<std::string> checkInput(std::string input, AdvPlayer * player);
    bool tileExistsInAFactory(const char & tile, int factory);
    char getColorOfaRow(int row, AdvPlayer * player);
    std::string getGridColor(int row, AdvPlayer * player);
    bool isRowFull(int row, AdvPlayer * player);
    bool endRound();
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
