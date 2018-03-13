#include "player.hpp"
#include "heuristic.hpp"

#define RECURSIVE_DEPTH 20
#define TIME 4

/*
 * Constructor for the player; initialize everything here. The side your AI is
 * on (BLACK or WHITE) is passed in as "side". The constructor must finish
 * within 30 seconds.
 */
Player::Player(Side side) {
    // Will be set to true in test_minimax.cpp.
    testingMinimax = true;
    /*
     * TODO: Do any initialization you need to do here (setting up the board,
     * precalculating things, etc.) However, remember that you will only have
     * 30 seconds.
     */
    this->start_side = side;
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
    // testingMinimax = true;
    // update board according to oppoent move
    // iterative deepening
    time_t begin;
    time_t end;
    double left;
    time(&begin);

    board->doMove(opponentsMove, opp_side);
    Move *move = new Move(-1, -1);
    int iter = RECURSIVE_DEPTH - 1;

    if(testingMinimax) {
        while (left < TIME) {    
            //cerr << "time left: " << TIME - left << endl;
            minimax_data minmaxedmove = getMinimaxMove(board, start_side, iter,
                -10000, 10000);
            move->setX(minmaxedmove.move.getX());
            move->setY(minmaxedmove.move.getY());

            //cerr << move->getX() << " " << move->getY() << endl;
            //cerr << "ITER: " << RECURSIVE_DEPTH - iter << endl;
            iter --;

            if (iter < 0)
            {
                break;
            }

            time(&end);
            left = difftime(end, begin);
        }

        board->doMove(move, start_side);
        return move;
    }

    // check if there are legal moves
    if (board->hasMoves(start_side))
    {
        Board *board2;
        Move *bestmove = new Move(0, 0);
        int best = -100000;

        // get best move
        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                Move move(i, j);

                if (board->checkMove(&move, start_side))
                {
                    board2 = board->copy();
                    board2->doMove(&move, start_side);

                    int count = heuristicWithMobility(board2, start_side);

                    if (count > best)
                    {
                        best = count;
                        bestmove->setX(move.getX());
                        bestmove->setY(move.getY());
                    }

                    delete board2;
                }
            }
        }

        board->doMove(bestmove, start_side);
        return bestmove;
    }

    return nullptr;
    time(&end);
}

/**
 * @brief determines the move that will leave the selected side with the most score after a
 *      specified recursive depth defined above.
 * @param board a pointer to the board. May be a hypothetical future board state.
 * @param side the side that is currently being calculated
 * @param depth the current depth (0 to start)
 */
minimax_data Player::getMinimaxMove(Board *hypothetical_board, Side side, int depth,
        int alpha, int beta) {
    if(depth == RECURSIVE_DEPTH) {
        int score = heuristicWithMobility(hypothetical_board, side);
/*
        // endgame 
        if (64 - (hypothetical_board->count(side) + hypothetical_board->count(opp_side) < 14)) {
            score = simpleCount(hypothetical_board, side);
        }
*/
        if (RECURSIVE_DEPTH % 2 != 0)
        {
            score *= -1;
        }

        minimax_data retval = {Move(-1,-1), score};
        return retval;
    }


    minimax_data retval = {Move(-1,-1), -1000000000, alpha, beta}; //


    for(int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            Move testmove = Move(i, j);
            if (hypothetical_board->checkMove(&testmove, side)) {
                //std::cerr << "  Valid move at" << testmove.getX() << " " << testmove.getY() << std::endl;
                Board *next_board = hypothetical_board->copy();
                next_board->doMove(&testmove, side);
                minimax_data opponentmove = getMinimaxMove(next_board, otherSide(side), depth+1,
                    -retval.beta, -retval.alpha);
                opponentmove.score *= -1;

                delete next_board;

                if (retval.score < opponentmove.score) {
                    retval.score = opponentmove.score;
                    retval.move = testmove;
                }

                if (retval.score == -1000000000)
                {
                    retval.score = heuristicWithMobility(next_board, side);
                }

                if (opponentmove.score > retval.alpha)
                {
                    retval.alpha = opponentmove.score;
                }
                if (retval.beta <= retval.score)
                {
                    retval.score = retval.beta;
                    return retval;
                }
            }
        }
    }
    if(retval.move.getX() == -1) {
        //There are no available moves; This is a victory or a loss.
        int finalScore = heuristicWithMobility(hypothetical_board, side);
        if(finalScore > 0) { // TODO: Prefer draws over losses
            retval.score = 100000000 + finalScore;
            // Wins are always better than any other board state, but win with style if we can.
            // (adding finalScore still makes us prefer winning with as many stones as possible)
        } else {
            retval.score = -100000000 + finalScore;
            // Lose with grace if we can.
        }
    }
    return retval;
}

void Player::setBoard(Board *board) {
    this->board = board;
}
