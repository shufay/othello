#ifndef __HEURISTIC_H__
#define __HEURISTIC_H__

#include "board.hpp"
#include "common.hpp"

const int weights[8][8] = {{ 30,-30, 20, 20, 20, 20,-30, 30},
                           {-30,-30, 1, 1, 1, 1,-30, -30},
                           { 20, 1, 1, 1, 1, 1, 1, 20},
                           { 20, 1, 1, 1, 1, 1, 1, 20},
                           { 20, 1, 1, 1, 1, 1, 1, 20},
                           { 20, 1, 1, 1, 1, 1, 1, 20},
                           {-30,-30, 1, 1, 1, 1,-30, -30},
                           { 30,-30, 20, 20, 20, 20,-30, 30}};

int getHeuristicWeighting(Board *board, Side side);
int simpleCount(Board *board, Side side);

#endif