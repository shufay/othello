#include "player.hpp"

#define RECURSIVE_DEPTH 3
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
    // testingMinimax = true;
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

            int count = getHeuristicWeighting(board2, side);
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
        int score = Player::getHeuristicWeighting(hypothetical_board, side);
        minimax_data retval = {Move(-1,-1), score};
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
                    // TODO: If this is positive, we've won. Just follow this path to victory.
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

int Player::getHeuristicWeighting(Board *board, Side side) {
    int weights[8][8] = {{ 3,-2, 2, 2, 2, 2,-2, 3},
                         {-2,-3, 1, 1, 1, 1,-3, 2},
                         { 2, 1, 1, 1, 1, 1, 1, 2},
                         { 2, 1, 1, 1, 1, 1, 1, 2},
                         { 2, 1, 1, 1, 1, 1, 1, 2},
                         { 2, 1, 1, 1, 1, 1, 1, 2},
                         {-2,-3, 1, 1, 1, 1,-3, 2},
                         { 3,-2, 2, 2, 2, 2,-2, 3}};

    int count = 0;
    for(int x = 0; x < 8; x++) {
        for (int y = 0; y < 8; y++) {
            if (board->get(side, x, y)) {
                count += weights[y][x];
            }
            if (board->get(otherSide(side), x, y)) {
                count -= weights[y][x];
            }
        }
    }
    return count;
}