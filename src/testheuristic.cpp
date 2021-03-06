#include <iostream>
#include "common.hpp"
#include "board.hpp"
#include "heuristic.hpp"

int main(int argc, char *argv[]) {

    char firstboard[64] = {
        'b', 'w', 'w', ' ', ' ', ' ', ' ', ' ',
        'w', 'w', 'w', ' ', ' ', ' ', ' ', ' ',
        'w', 'w', 'w', ' ', ' ', ' ', ' ', ' ',
        ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
        ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
        ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
        ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
        ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '
    };
    Board *board1 = new Board();
    board1->setBoard(firstboard);

    char secondboard[64] = {
        ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
        ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
        ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
        ' ', 'w', 'w', 'b', 'w', ' ', ' ', ' ',
        ' ', 'b', 'b', 'w', 'b', ' ', ' ', ' ',
        ' ', ' ', ' ', 'b', ' ', ' ', ' ', ' ',
        ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
        ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '
    };
    Board *board2 = new Board();
    board2->setBoard(secondboard);

    std::cout << "Board 1:" << std::endl;
    board1->print_board();

    std::cout << "simpleCount white: " << simpleCount(board1, WHITE)
              << " | simpleCount black: " << simpleCount(board1, BLACK) << std::endl;

    std::cout << "Heuristic weight white: " << getHeuristicWeighting(board1, WHITE)
              << " | Heuristic weight black: " << getHeuristicWeighting(board1, BLACK) << std::endl;
    std::cout << std::endl;

    std::cout << "Board 2:" << std::endl;
    board2->print_board();

    std::cout << "simpleCount white: " << simpleCount(board2, WHITE)
              << " | simpleCount black: " << simpleCount(board2, BLACK) << std::endl;

    std::cout << "Heuristic weight white: " << getHeuristicWeighting(board2, WHITE)
              << " | Heuristic weight black: " << getHeuristicWeighting(board2, BLACK) << std::endl;
    std::cout << std::endl;

    Move move1 = Move(0,0);
    Move move2 = Move(1,0);
    Move move3 = Move(1,1);
    Move move4 = Move(7,0);

    std::cout << "(0,0) is interior: " << isInterior(&move1) << std::endl;
    std::cout << "(1,0) is interior: " << isInterior(&move2) << std::endl;
    std::cout << "(1,1) is interior: " << isInterior(&move3) << std::endl;
    std::cout << "(7,0) is interior: " << isInterior(&move4) << std::endl;

    delete board1;
    delete board2;
    return 0;
}
