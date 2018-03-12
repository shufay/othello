#include "heuristic.hpp"

int getHeuristicWeighting(Board *board, Side side) {
    int count = 0;
    for(int x = 0; x < 8; x++) {
        for (int y = 0; y < 8; y++) {
            if (board->get(side, x, y)) {
                count += weights[y][x];
            }
            else if (board->occupied(x, y)) {
                count -= weights[y][x];
            }
        }
    }
    return count;
}

int simpleCount(Board *board, Side side) {
    return board->count(side) - board->count(otherSide(side));
}