#include "player.hpp"

#define RECURSIVE_DEPTH 6
#define otherSide(x) (x == BLACK) ? WHITE : BLACK

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
    board->doMove(opponentsMove, opp_side);

    if(testingMinimax) {
        minimax_data minmaxedmove = getMinimaxMove(board, start_side, 0, 
            -1000, 1000);
        Move *move = new Move(-1,-1);
        move->setX(minmaxedmove.move.getX());
        move->setY(minmaxedmove.move.getY());
        board->doMove(move, start_side);
        cerr << move->getX() << " " << move->getY() << endl;
        return move;
    }

    // check if there are legal moves
    if (board->hasMoves(start_side))
    {
        Board *board2;
        Move *bestmove = new Move(0, 0);
        int best = -1000;

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

                    int count = getHeuristicWeighting(board2, start_side);

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
    // std::cerr << "new call: " << (side==BLACK) << " " << depth << std::endl;
    // hypothetical_board->print_board();
    if(depth == RECURSIVE_DEPTH) {
        int score = Player::getHeuristicWeighting(hypothetical_board, side);

        if (RECURSIVE_DEPTH % 2 != 0)
        {
            score *= -1;
        }

        minimax_data retval = {Move(-1,-1), score};
        return retval;
    }

    minimax_data retval = {Move(-1,-1), -1000, alpha, beta}; // An impossibly bad score
    
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

                if (retval.score < opponentmove.score) { // Negate; what's bad for opponent good for us
                    retval.score = opponentmove.score;
                    retval.move = testmove;
                }

                if (retval.score == -1000)
                {
                    retval.score = getHeuristicWeighting(next_board, side);
                }

                if (opponentmove.score > retval.alpha)
                {
                    retval.alpha = opponentmove.score;

                }

                if (retval.beta <= retval.score)
                {
                    cerr << "PRUNE" << endl;
                    retval.score = retval.beta;
                    return retval;
                }

                //cerr << "alpha: " << retval.alpha << endl;
                //cerr << "beta: " << retval.beta << endl;
            }
        }
    }
    // std::cerr << "-------------------" << std::endl;
    return retval;
}

void Player::setBoard(Board *board) {
    this->board = board;
}

int Player::getHeuristicWeighting(Board *board, Side side) {
    int weights[8][8] = {{ 30,-30, 20, 20, 20, 20,-30, 30},
                         {-30,-30, 1, 1, 1, 1,-30, -30},
                         { 20, 1, 1, 1, 1, 1, 1, 20},
                         { 20, 1, 1, 1, 1, 1, 1, 20},
                         { 20, 1, 1, 1, 1, 1, 1, 20},
                         { 20, 1, 1, 1, 1, 1, 1, 20},
                         {-30,-30, 1, 1, 1, 1,-30, -30},
                         { 30,-30, 20, 20, 20, 20,-30, 30}};

    int count = 0;
    for(int x = 0; x < 8; x++) {
        for (int y = 0; y < 8; y++) {
            if (((board->get(start_side, x, y)) && (start_side == BLACK)) ||
                ((board->get(opp_side, x, y)) && (start_side == WHITE))) 
            {
                count += weights[y][x];
            }

            else if (board->occupied(x, y)) 
            {
                count -= weights[y][x];
            }
        }
    }
    return count;
}