#ifndef _BOARD_HEADER_
#define _BOARD_HEADER_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>
#include <ctype.h>
#include <string.h>


typedef enum {
    empty = 0,
    pawn = 1,
    bishop = 2,
    knight = 3,
    rook = 4,
    queen = 5,
    king = 6,
} Piece;

typedef enum {
    white = 0,
    black = 1,
} Color;

//definition of the structure of a board Square : type (0=empty, 1=pawn, 2=bishop, 3=knight, 4=rook, 5=queen, 6=king) and color (0=white, 1=black)
typedef struct Square {
    Piece type;
    Color color;
} Square;

typedef struct Coords {
    int x;
    int y;
} Coords;

typedef struct SaveInfo {
    char name[32];
    int size;
    long long int time;
    int turn;
} SaveInfo;

/**
 * @brief Create a Board object (uninitialized square matrix)
 * 
 * @param size Size of the board
 * @return Return the created board
 */
Square** createBoard(int size);

/**
 * @brief Initialize the specified board with random pieces (kings will always be in the first or last row). Uses the initlalizeBoardColor function to set the colors of the squares
 * 
 * @param board The board that is going to be initialized
 * @param size The size of the board
 */
void initializeBoardRandom(Square** board, int size);

/**
 * @brief Initialize a specified board with the classic pieces layout (only for 8x8 boards). Uses the initlalizeBoardColor function to set the colors of the squares
 * 
 * @param board The board that is going to be initialized
 */
void initializeBoardClassic(Square** board);

/**
 * @brief Initialize the color of a board by setting the color of the two highest rows to black and the rest to white (color does not matter when the type of the square is empty)
 * 
 * @param board The board where the colors are going to be set up
 * @param size The size of the board
 */
void initializeBoardColor(Square** board, int size);

/**
 * @brief Get the position of both kings in a specified board
 * 
 * @param board Board where the kings have to be found
 * @param size The size of the board
 * @param king_pos_white The coordinates of the white king (modified by the function)
 * @param king_pos_black The coordinates of the black king (modified by the function)
 */
void getKingPos(Square** board, int size, Coords* king_pos_white, Coords* king_pos_black);

/**
 * @brief Update the position of both king taking in consideration the last move done 
 * 
 * @param board Board where the kings have to be found
 * @param size Size of the board
 * @param last_move Last move done in the board
 * @param king_pos_white The coordinates of the white king (modified by the function)
 * @param king_pos_black The coordinates of the black king (modified by the function)
 */
void updateKingPos(Square** board, int size, Coords last_move, Coords* king_pos_white, Coords* king_pos_black);

/**
 * @brief Free the specified board
 * 
 * @param board Board that is going to be freed
 * @param size size of the board
 */
void freeBoard(Square*** board, int size);


/**
 * @brief Test if there is a a piece between two positions in the board (only for straight or diagonal moves)
 * 
 * @param board Board where the move has to be tested
 * @param size Size of the board
 * @param start_pos Start coordinates of the piece
 * @param targ_pos Target coordinates of the piece
 * @return true if the way is free
 * @return false if there is an obstacle
 */
bool collisionTest(Square** board, int size, Coords start_pos, Coords targ_pos);

/**
 * @brief Test if a move is allowed by calling the appropriate function corresponding to the type od the piece
 * 
 * @param board Board where the move has to be tested
 * @param size Size of the board
 * @param start_pos Start coordinates of the piece
 * @param targ_pos Target coordinates of the piece
 * @return true if the move is allowed
 * @return false if the move is not allowed
 */
bool moveTest(Square** board, int size, Coords start_pos, Coords targ_pos);

/**
 * @brief Test if the specified move is allowed for a pawn
 * 
 * @param board Board where the move has to be tested
 * @param size Size of the board
 * @param start_pos Start coordinates of the piece
 * @param targ_pos Target coordinates of the piece
 * @return true if the move is allowed
 * @return false if the move is not allowed
 */
bool pawnMoveTest(Square** board, int size, Coords start_pos, Coords targ_pos);

/**
 * @brief Test if the specified move is allowed for a bishop by calling the collisionTest function
 * 
 * @param board Board where the move has to be tested
 * @param size Size of the board
 * @param start_pos Start coordinates of the piece
 * @param targ_pos Target coordinates of the piece
 * @return true if the move is allowed
 * @return false if the move is not allowed
 */
bool bishopMoveTest(Square** board, int size, Coords start_pos, Coords targ_pos);

/**
 * @brief Test if the specified move is allowed for a knight
 * 
 * @param board Board where the move has to be tested
 * @param size Size of the board
 * @param start_pos Start coordinates of the piece
 * @param targ_pos Target coordinates of the piece
 * @return true if the move is allowed
 * @return false if the move is not allowed
 */
bool knightMoveTest(Square** board, int size, Coords start_pos, Coords targ_pos);

/**
 * @brief Test if the specified move is allowed for a rook by calling the collisionTest function
 * 
 * @param board Board where the move has to be tested
 * @param size Size of the board
 * @param start_pos Start coordinates of the piece
 * @param targ_pos Target coordinates of the piece
 * @return true if the move is allowed
 * @return false if the move is not allowed
 */
bool rookMoveTest(Square** board, int size, Coords start_pos, Coords targ_pos);

/**
 * @brief Test if the specified move is allowed for a queen by calling the collisionTest function
 * 
 * @param board Board where the move has to be tested
 * @param size Size of the board
 * @param start_pos Start coordinates of the piece
 * @param targ_pos Target coordinates of the piece
 * @return true if the move is allowed
 * @return false if the move is not allowed
 */
bool queenMoveTest(Square** board, int size, Coords start_pos, Coords targ_pos);

/**
 * @brief Test if the specified move is allowed for a king
 * 
 * @param board Board where the move has to be tested
 * @param size Size of the board
 * @param start_pos Start coordinates of the piece
 * @param targ_pos Target coordinates of the piece
 * @return true if the move is allowed
 * @return false if the move is not allowed
 */
bool kingMoveTest(Square** board, int size, Coords start_pos, Coords targ_pos); 

/**
 * @brief Test if a piece is in a check position (can be else than a king)
 * 
 * @param board Board where the check has to be tested
 * @param size Size of the board
 * @param king_pos Position of the king (or another piece)
 * @param piece_color Color of the piece
 * @return true if the piece is in  a check position
 * @return false if the piece is not in a check position
 */
bool checkTest(Square** board, int size, Coords king_pos, Color piece_color);

/**
 * @brief Test if the specified king is in a checkmate position
 * 
 * @param board Board where the checkmate has to be tested
 * @param size Size of the board
 * @param king_pos Position of the king
 * @return true if the king is on a checkmate position
 * @return false if the king is not in a checkmate position
 */
bool checkMateTest(Square** board, int size, Coords king_pos);

/**
 * @brief Execute the specified move (doesn't check if a move is legal or not)
 * 
 * @param board Board where the move has to be executed
 * @param size Size of the board
 * @param start_pos Start coordinates of the move
 * @param targ_pos Target coordinates of a move
 */
void moveExecute(Square** board, int size, Coords start_pos, Coords targ_pos);

/**
 * @brief Test if the specified move would put the specified king in a checkmate position
 * 
 * @param board Board where the checkmate has to be checked
 * @param size Size of the board
 * @param start_pos Start coordinates of the move
 * @param targ_pos Target coordinates of the move
 * @param king_pos Position of the king
 * @param kingcolor Color of the king
 * @return true if the move would put the king in a checkmate position
 * @return false if the move would not put the king in a checkmate position
 */
bool checkTestAfterMove(Square** board, int size, Coords start_pos, Coords targ_pos, Coords king_pos, Color kingcolor);


/**
 * @brief Initialize the "saves.txt" index by creating it if inexistant
 * 
 */
void initializeSavesIndex();

/**
 * @brief Export the specified board in a ".save" file and add it to the "saves.txt" index
 * 
 * @param board Board that has to be exported
 * @param size Size of the board
 * @param save_name Name of the save
 * @param turn 
 * @return true if the board was correctly exported
 * @return false if there was an error was exporting the board
 */
bool exportBoard(Square** board, int size, char* save_name, Color turn);

/**
 * @brief Get the informations relative to a save in the "save.txt" index
 * 
 * @param line_number Line that has to be parsed
 * @return SaveInfo the informations relatives to the save
 */
SaveInfo getSaveInfo(int line_number);

/**
 * @brief Import the specified save in a board (the board has to be created before with the right size)
 * 
 * @param board The board where the save will be imported
 * @param size The size of the board
 * @param save_name The name of the save that is going to be imported
 */
void importBoard(Square** board, int size, char* save_name);

/**
 * @brief Delete the specified save ".save" file and delete its corresponding line in the "saves.txt" index
 * 
 * @param save_name The name of the save that has to be deleted
 */
void ripSave(char* save_name);



#endif