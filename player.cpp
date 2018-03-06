#include "player.hpp"

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
    /*
     * TODO: Implement how moves your AI should play here. You should first
     * process the opponent's opponents move before calculating your own move
     */

    // update board according to oppoent move
    board->doMove(opponentsMove, opp_side);

    // check if there are legal moves
    if (board->hasMoves(side))
    {
        Board *board2;
        vector<Move> moves;
        Move *bestmove = new Move(0, 0);
        int best = -1000;
        
        int great[] = {0, 7};   // corners
        int bad[] = {1, 6};     // edges next to corners

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
            int x = moves[k].getX();
            int y = moves[k].getY();

            board2->doMove(&moves[k], side);
            int count = board2->count(side) - board2->count(opp_side);

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

            if (count > best)
            {
                best = count;
                bestmove->setX(moves[k].getX());
                bestmove->setY(moves[k].getY());
            }
        }

        board->doMove(bestmove, side);
        return bestmove;
    }

    return nullptr;
}
