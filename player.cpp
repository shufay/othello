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
    playerside = side;
    /*
     * TODO: Do any initialization you need to do here (setting up the board,
     * precalculating things, etc.) However, remember that you will only have
     * 30 seconds.
     */
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
    if(testingMinimax) {
        minimax_data minmaxedmove = getMinimaxMove(board, playerside, 0);
        Move *move = new Move(-1,-1);
        move->setX(minmaxedmove.move.getX());
        move->setY(minmaxedmove.move.getY());
        return move;
    }
    return nullptr;
}

/**
 * @brief determines the move that will leave the selected side with the most score after a
 *      specified recursive depth defined above.
 * @param board a pointer to the board. May be a hypothetical future board state
 */
minimax_data Player::getMinimaxMove(Board *board, Side side, int depth) {
    if(depth == RECURSIVE_DEPTH) {
        minimax_data retval = {Move(-1,-1), board->count(side) - board->count(otherSide(side))};
        return retval;
    }
    minimax_data retval = {Move(-1,-1), -65}; // An impossibly bad score
    for(int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            Move testmove = Move(i, j);
            if (board->checkMove(&testmove, side)) {
                Board *next_board = board->copy();
                next_board->doMove(&testmove, side);
                minimax_data opponentmove = getMinimaxMove(next_board, otherSide(side), depth+1);
                if (opponentmove.move.getX() == -1 && opponentmove.move.getY() == -1) {
                    opponentmove.score = next_board->count(side) - next_board->count(otherSide(side));
                    // If the opponent's move is -1,-1, then there are no valid moves. That means
                    // the game is over and the score after this round is the final score.
                }
                delete next_board;
                if (retval.score < -opponentmove.score) { // Negate; what's bad for opponent good for us
                    retval.score = -opponentmove.score;
                    retval.move = testmove;
                }
            }
        }
    }
    cerr << depth << " " << retval.score << " " << retval.move.getX() << " " << retval.move.getY() << " " << endl;
    return retval;
}
