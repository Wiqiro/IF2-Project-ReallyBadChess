#ifndef _MOVES_HEADER_
#define _MOVES_HEADER_

#include <board.h>
#include <moves.h>

/**
 * @brief Test if a move is possible by appending a MoveTest function depending on the type of the piece --> execute the move if possible
 * 
 * @param board 
 * @param size 
 * @param startx 
 * @param starty 
 * @param targx 
 * @param targy 
 * @return true a piece was captured
 * @return false no piece were captured
 */
bool Move(square** board, int size, int startx, int starty, int targx, int targy); //route to the right MoveTest function depending on the type and append MoveExecute

bool PawnMoveTest(square** board, int size, int startx, int starty, int targx, int targy);

bool BishopMoveTest(square** board, int size, int startx, int starty, int targx, int targy);

bool KnightMoveTest(square** board, int size, int startx, int starty, int targx, int targy);

bool RookMoveTest(square** board, int size, int startx, int starty, int targx, int targy);

bool QueenMoveTest(square** board, int size, int startx, int starty, int targx, int targy);


/**
 * @brief Test if the king move is possible --> has to check if the targetted move would result in a Check
 * 
 * @param board 
 * @param size 
 * @param startx 
 * @param starty 
 * @param targx 
 * @param targy 
 * @return true if the move is possible
 * @return false if the move is not possible
 */
bool KingMoveTest(square** board, int size, int startx, int starty, int targx, int targy); 
//kingmove scan all the board


/**
 * @brief Test if the king is in a Check position --> has to scan the entire chessboard to determine if a piece can capture the king
 * 
 * @param board 
 * @param size 
 * @param kingposx 
 * @param kingposy 
 * @return true Check 
 * @return false no Check
 */
bool CheckTest(square** board, int size, int kingposx, int kingposy);


/**
 * @brief Test if the king is in a Checkmate position --> has to call the CheckTest function for every possible king move
 * 
 * @param board 
 * @param size 
 * @param kingposx 
 * @param kingposy 
 * @return true Checkmate position
 * @return false no Checkmate position
 */
bool CheckMateTest(square** board, int size, int kingposx, int kingposy);

/**
 * @brief Execute a move (no legit move verification : has to be checked before)
 * 
 * @param board 
 * @param size 
 * @param startx 
 * @param starty 
 * @param targx 
 * @param targy 
 * @return true a piece was captured
 * @return false no piece were captured
 */
bool MoveExecute(square** board, int size, int startx, int starty, int targx, int targy);


#endif