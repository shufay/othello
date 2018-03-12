#include "heuristic.hpp"

/**
 * @brief code for calculating how "good" a board is. Each function should take a Board* and a side,
 * and return an int. For a good heuristic function, the property:
 * heuristic(board, BLACK) == -heuristic(board, WHITE) should generally hold.
 */

/**
 * @brief a smarter heuristic that prioritizes taking corners and not taking almost-corners.
 * Corners are weighted 30, adjacent to them is -30, edges are 20, everything else is 1. Simply adds
 * all the points up, subtracting opponent's pieces and adding ours.
 * @param board a pointer to a board state.
 * @param side the side to count for.
 */
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

int mobility()

/**
 * @brief Counts the number we own minus the ones our opponent owns.
 * TODO: This can be optimized but since it's already so fast idk if it's needed.
 * @param board a pointer to a board state.
 * @param the side to count for.
 */
int simpleCount(Board *board, Side side) {
    return board->count(side) - board->count(otherSide(side));
}