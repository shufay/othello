#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <iostream>
#include <time.h>
#include "common.hpp"
#include "board.hpp"

//using namespace std;

struct minimax_data {
    Move move;
    int score, alpha, beta, mobility;
};

class Player {
private:
    minimax_data getMinimaxMove(Board *board, Side side, int depth,
        int alpha, int beta);
    Side start_side;
    Side opp_side;
    Board *board;

public:
    Player(Side side);
    ~Player();
    Move *doMove(Move *opponentsMove, int msLeft);
    void setBoard(Board *board);

    // Flag to tell if the player is running within the test_minimax context
    bool testingMinimax;
};

#endif
