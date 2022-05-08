#include <moves.h>


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
bool Move(square** board, int size, int startx, int starty, int targx, int targy) {
    if (board[startx][starty].type == queen) {
            QueenMoveTest(board, size, startx, starty, targx, targy);
    }

    bool captured=false;
    return captured;
}


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
bool PawnMoveTest(square** board, int size, int startx, int starty, int targx, int targy) {
/* 
    if ((board[startx][starty].color == white && targy-starty >= 0) || (board[startx][starty].color == black && targy-starty <= 0)) {
        printf("Can't move on this direction !\n");
        return false;
    } else if (targx < 0 || targy < 0 || targx > size-1 || targy > size-1) {
        printf("Cannot travel out of the board !\n");
        return false;
    } else if (abs(targy-starty) == 2 && targx-startx == 0 && board[targx][targy].type == empty) {
        return true;
    } else if (abs(targy-starty) == 1 && targx-startx == 0 && board[targx][targy].type == empty) {
        return true;
    }
    
    putain
 */
    return 0;
}


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
bool BishopMoveTest(square** board, int size, int startx, int starty, int targx, int targy) {
    bool okMove=false;

    return okMove;
}


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
bool KnightMoveTest(square** board, int size, int startx, int starty, int targx, int targy) {
    bool okMove=false;

    return okMove;
}


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
bool RookMoveTest(square** board, int size, int startx, int starty, int targx, int targy) {

    return false;

}


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
bool QueenMoveTest(square** board, int size, int startx, int starty, int targx, int targy) {

    int movex = targx-startx;
    int movey = targy-starty;

    int i=0;
    
    while (i+1 < fmax(movex,movey) && board[startx+(movex/abs(movex))*i][starty+(movey/abs(movey))*i].type == empty) {
        //printf("%d",board[startx+(movex/abs(movex))*i][starty+(movey/abs(movey))*i].type);
        i++;
    }

    //printf("\n%d",i);
    if (i == fmax(movex,movey)-1) {
        return true;
    }
    
    return false;
}


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
bool KingMoveTest(square** board, int size, int startx, int starty, int targx, int targy) {
    bool okMove=false;

    return okMove;
}


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
bool CheckTest(square** board, int size, int kingposx, int kingposy) {
    bool check=false;

    return check;
}


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
bool CheckMateTest(square** board, int size, int kingposx, int kingposy) {
    bool checkMate=false;

    return checkMate;
}

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
bool MoveExecute(square** board, int size, int startx, int starty, int targx, int targy) {
    bool captured=false;

    return captured;
}