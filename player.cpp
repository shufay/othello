#include "player.hpp"

#define RECURSIVE_DEPTH 2
#define otherSide(x) (x == BLACK) ? WHITE : BLACK

/*
 * Constructor for the player; initialize everything here. The side your AI is
 * on (BLACK or WHITE) is passed in as "side". The constructor must finish
 * within 30 seconds.
 */
Player::Player(Side side) {
    // Will be set to true in test_minimax.cpp.
    testingMinimax = false;
    /*
     * TODO: Do any initialization you need to do here (setting up the board,
     * precalculating things, etc.) However, remember that you will only have
     * 30 seconds.
     */
    this->side = side;
    this->opp_side = (side == WHITE) ? BLACK : WHITE;
    this->board = new Board();

}

/*
 * Destructor for the player.
 */
Player::~Player() {

}

/*
 * Compute the next move given the opponent's last move. Your AI is
 * expected to keep track of the board on its own. If this is the first move,
 * or if the opponent passed on the last move, then opponentsMove will be
 * nullptr.
 *
 * msLeft represents the time your AI has left for the total game, in
 * milliseconds. doMove() must take no longer than msLeft, or your AI will
 * be disqualified! An msLeft value of -1 indicates no time limit.
 *
 * The move returned must be legal; if there are no valid moves for your side,
 * return nullptr.
 */
Move *Player::doMove(Move *opponentsMove, int msLeft) {
    testingMinimax = true;
    // update board according to oppoent move
    board->doMove(opponentsMove, opp_side);
    if(testingMinimax) {
        minimax_data minmaxedmove = getMinimaxMove(board, side, 0);
        Move *move = new Move(-1,-1);
        move->setX(minmaxedmove.move.getX());
        move->setY(minmaxedmove.move.getY());
        board->doMove(move, side);
        return move;
    }

    // check if there are legal moves
    if (board->hasMoves(side))
    {
        Board *board2;
        vector<Move> moves;
        Move *bestmove = new Move(0, 0);
        int best = -1000;

        // get valid moves
        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                Move move(i, j);

                if (board->checkMove(&move, side))
                {
                    moves.push_back(move);
                }
            }
        }

        // get best move - does this by maximizing the difference
        // between stone(side) and stone(opp_side), with some weighting.
        for (unsigned int k = 0; k < moves.size(); k++)
        {
            board2 = board->copy();
            board2->doMove(&moves[k], side);

            int count = getHeuristicWeighting(board2, &(moves[k]));
            if (count > best)
            {
                best = count;
                bestmove->setX(moves[k].getX());
                bestmove->setY(moves[k].getY());
            }
            delete board2;
        }

        board->doMove(bestmove, side);
        return bestmove;
    }

    return nullptr;
}

/**
 * @brief determines the move that will leave the selected side with the most score after a
 *      specified recursive depth defined above.
 * @param board a pointer to the board. May be a hypothetical future board state.
 * @param side the side that is currently being calculated
 * @param depth the current depth (0 to start)
 */
minimax_data Player::getMinimaxMove(Board *hypothetical_board, Side side, int depth) {
    // std::cerr << "new call: " << (side==BLACK) << " " << depth << std::endl;
    // hypothetical_board->print_board();
    if(depth == RECURSIVE_DEPTH) {
        minimax_data retval = {Move(-1,-1), hypothetical_board->count(side) - hypothetical_board->count(otherSide(side))};
        return retval;
    }
    minimax_data retval = {Move(-1,-1), -65}; // An impossibly bad score
    for(int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            Move testmove = Move(i, j);
            if (hypothetical_board->checkMove(&testmove, side)) {
                // std::cerr << "  Valid move at" << testmove.getX() << " " << testmove.getY() << std::endl;
                Board *next_board = hypothetical_board->copy();
                next_board->doMove(&testmove, side);
                minimax_data opponentmove = getMinimaxMove(next_board, otherSide(side), depth+1);

                if (opponentmove.score == -65) {
                    opponentmove.score = next_board->count(side) - next_board->count(otherSide(side));
                    // If the opponent's move is -1,-1, then there are no valid moves. That means
                    // the game is over and the score after this round is the final score.
                    // std::cerr << "  Found game end with " << opponentmove.score << std::endl;

                }

                delete next_board;
                if (retval.score < -opponentmove.score) { // Negate; what's bad for opponent good for us
                    retval.score = -opponentmove.score;
                    retval.move = testmove;
                }
            }
        }
    }
    // std::cerr << "-------------------" << std::endl;
    return retval;
}

void Player::setBoard(Board *board) {
    this->board = board;
}

int Player::getHeuristicWeighting(Board *board, Move *move) {
    int great[] = {0, 7};   // corners
    int bad[] = {1, 6};     // edges next to corners

    int x = move->getX();
    int y = move->getY();

    int count = board->count(side) - board->count(opp_side);

    // weighting:
    //      difference * 3 for corners
    //      difference * -3 for edges next to corners
    if ((find(great, great+2, x) != great+2) && (find(great, great+2, y) != great+2))
    {
        count *= 3;
    }

    else if (((find(bad, bad+2, x) != bad+2) && (find(great, great+2, y) != great+2)) ||
        ((find(bad, bad+2, y) != bad+2) && (find(great, great+2, x) != great+2)))
    {
        count *= -3;
    }
    return count;
}