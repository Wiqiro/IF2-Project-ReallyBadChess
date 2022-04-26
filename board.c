#include <board.h>


/**
 * @brief Create Board object (square matrix)
 * 
 * @param size size of the board (nxn)
 * @return square** the board created
 */
square** CreateBoard(int size){
    square** board = (square**)malloc(sizeof(square*)*size);
    for (int i=0; i<size; i++) {
        board[i] = (square*)malloc(sizeof(square)*size);
    }
    if (board == NULL) {
        fprintf("ERROR CREATING THE BOARD : not enough memory\n");
    }
    return board;
}



/**
 * @brief Place the chess pieces randomly (only one king, following the classic rules)
 * 
 * @param board Board to modify
 * @param size Size of the board
 */
void InitializeBoardRandom(square** board, int size){

}


/**
 * @brief Place the pieces on the specified following the classic chess rules
 * 
 * @param board Board to modify (has to be a 8x8 board)
 */
void InitializeBoardClassic(square** board){

}


/**
 * @brief Generic print of the chessboard
 * 
 * @param board Board to print
 * @param size Size of the board
 */
void SimplePrint(square** board, int size) {

}


/**
 * @brief Free the specified board
 * 
 * @param board Board to free
 * @param size Size of the board
 */
void FreeBoard(square** board, int size){

}
