#ifndef __HEURISTIC_H__
#define __HEURISTIC_H__

#include "board.hpp"
#include "common.hpp"

const int mobility_mult = 5;
const int weights[8][8] = {{ 300,-30, 5, 5, 5, 5,-30, 300},
                           {-30,-30, 1, 1, 1, 1,-30, -30},
                           { 5, 1, 1, 1, 1, 1, 1, 5},
                           { 5, 1, 1, 1, 1, 1, 1, 5},
                           { 5, 1, 1, 1, 1, 1, 1, 5},
                           { 5, 1, 1, 1, 1, 1, 1, 5},
                           {-30,-30, 1, 1, 1, 1,-30, -30},
                           { 300,-30, 5, 5, 5, 5,-30, 300}};

int heuristicWithMobility(Board *board, Side side);
int getHeuristicWeighting(Board *board, Side side);
int simpleCount(Board *board, Side side);

#endif