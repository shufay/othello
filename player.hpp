#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <iostream>
#include "common.hpp"
#include "board.hpp"


using namespace std;

struct minimax_data {
    Move move;
    int score;
};

class Player {
private:
    minimax_data getMinimaxMove(Board *board, Side side, int depth);

public:
    Player(Side side);
    ~Player();

    Move *doMove(Move *opponentsMove, int msLeft);

    // Flag to tell if the player is running within the test_minimax context
    bool testingMinimax;
    Side playerside;
    Board *board;
};

#endif
