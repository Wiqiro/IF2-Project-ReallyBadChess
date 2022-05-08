#ifndef _BOARD_HEADER_
#define _BOARD_HEADER_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>



typedef enum {
    empty = 0,
    pawn = 1,
    bishop = 2,
    knight = 3,
    rook = 4,
    queen = 5,
    king = 6,
} piece;

typedef enum {
    white = 0,
    black = 1,
} color;

//definition of the structure of a board square : type (0=nothing, 1=pawn, 2=bishop, 3=knight, 4=rook, 5=queen, 6=king) and color (0=white, 1=black)
typedef struct square {
    piece type;
    color color;
} square;


/**
 * @brief Create a And Initialize Board object (square matrix)
 * 
 * @param size size of the board (nxn)
 * @return square** the board created
 */
square** CreateBoard(int size);


/**
 * @brief Place the chess pieces randomly (only one king, following the classic rules)
 * 
 * @param board Board to modify
 * @param size Size of the board
 */
void InitializeBoardRandom(square** board, int size);


/**
 * @brief Place the pieces on the specified following the classic chess rules
 * 
 * @param board Board to modify (has to be a 8x8 board)
 */
void InitializeBoardClassic(square** board);


/**
 * @brief Setup the colors of a specified board (black on the two first rows and white on the rest : color does not matter on empty squares)
 * 
 * @param board Board to modify
 * @param size Size of the board
 */
void InitializeBoardColor(square** board, int size);


/**
 * @brief Generic print of the chessboard
 * 
 * @param board Board to print
 * @param size Size of the board
 */
void SimplePrint(square** board, int size);


/**
 * @brief Free the specified board
 * 
 * @param board Board to free
 * @param size Size of the board
 */
void FreeBoard(square*** board, int size);


#endif