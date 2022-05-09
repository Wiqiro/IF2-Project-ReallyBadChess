#ifndef _MOVES_HEADER_
#define _MOVES_HEADER_

#include <board.h>

/**
 * @brief Test if a move is possible by appending a MoveTest function depending on the type of the piece --> execute the move if possible
 * 
 * @param board Board where the move has to be tested
 * @param size Size of the board
 * @param startx The starting column of the piece
 * @param starty The starting row of the piece
 * @param targx The targetted column of move
 * @param targy The targetted row of move
 * @return true  if a piece was captured
 * @return false if no piece were captured
 */
bool Move(square** board, int size, int startx, int starty, int targx, int targy);


/**
 * @brief Test if a move is possible by appending a MoveTest function depending on the type of the piece
 * 
 * @param board Board where the move has to be tested
 * @param size Size of the board
 * @param startx The starting column of the piece
 * @param starty The starting row of the piece
 * @param targx The targetted column of move
 * @param targy The targetted row of move
 * @return true  if the move is possible
 * @return false if the move is not possible
 */
bool MoveTest(square** board, int size, int startx, int starty, int targx, int targy);

/**
 * @brief Test if the move of a specified pawn is possible
 * 
 * @param board Board where the move has to be tested
 * @param size Size of the board
 * @param startx The starting column of the piece
 * @param starty The starting row of the piece
 * @param targx The targetted column of move
 * @param targy The targetted row of move
 * @return true  if the move is allowed
 * @return false if the move is not allowed
 */
bool PawnMoveTest(square** board, int size, int startx, int starty, int targx, int targy);


/**
 * @brief Test if the move of a specified bishop is possible
 * 
 * @param board Board where the move has to be tested
 * @param size Size of the board
 * @param startx The starting column of the piece
 * @param starty The starting row of the piece
 * @param targx The targetted column of move
 * @param targy The targetted row of move
 * @return true  if the move is allowed
 * @return false if the move is not allowed
 */
bool BishopMoveTest(square** board, int size, int startx, int starty, int targx, int targy);


/**
 * @brief Test if the move of a specified knight is possible
 * 
 * @param board Board where the move has to be tested
 * @param size Size of the board
 * @param startx The starting column of the piece
 * @param starty The starting row of the piece
 * @param targx The targetted column of move
 * @param targy The targetted row of move
 * @return true  if the move is allowed
 * @return false if the move is not allowed
 */
bool KnightMoveTest(square** board, int size, int startx, int starty, int targx, int targy);


/**
 * @brief Test if the move of a specified rook is possible
 * 
 * @param board Board where the move has to be tested
 * @param size Size of the board
 * @param startx The starting column of the piece
 * @param starty The starting row of the piece
 * @param targx The targetted column of move
 * @param targy The targetted row of move
 * @return true  if the move is allowed
 * @return false if the move is not allowed
 */
bool RookMoveTest(square** board, int size, int startx, int starty, int targx, int targy);


/**
 * @brief Test if the move of a specified queen is possible
 * 
 * @param board Board where the move has to be tested
 * @param size Size of the board
 * @param startx The starting column of the piece
 * @param starty The starting row of the piece
 * @param targx The targetted column of move
 * @param targy The targetted row of move
 * @return true  if the move is allowed
 * @return false if the move is not allowed
 */
bool QueenMoveTest(square** board, int size, int startx, int starty, int targx, int targy);


/**
 * @brief Test if the king move is possible --> has to check if the targetted move would result in a Check
 * 
 * @param board Board where the move has to be tested
 * @param size Size of the board
 * @param startx The starting column of the piece
 * @param starty The starting row of the piece
 * @param targx The targetted column of move
 * @param targy The targetted row of move
 * @return true if the move is possible
 * @return false if the move is not possible
 */
bool KingMoveTest(square** board, int size, int startx, int starty, int targx, int targy); 


/**
 * @brief Test if the king is in a Check position --> has to scan the entire board to determine if a piece can capture the king
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