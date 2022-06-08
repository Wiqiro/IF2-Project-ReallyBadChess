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


Square** createBoard(int size);

void initializeBoardRandom(Square** board, int size);

void initializeBoardClassic(Square** board);

void initializeBoardColor(Square** board, int size);

void getKingPos(Square** board, int size, Coords* king_pos_white, Coords* king_pos_black);

void updateKingPos(Square** board, int size, Coords last_move, Coords* king_pos_white, Coords* king_pos_black);

void freeBoard(Square*** board, int size);



bool collisionTest(Square** board, int size, Coords start_pos, Coords targ_pos);

bool moveTest(Square** board, int size, Coords start_pos, Coords targ_pos);

bool pawnMoveTest(Square** board, int size, Coords start_pos, Coords targ_pos);

bool bishopMoveTest(Square** board, int size, Coords start_pos, Coords targ_pos);

bool knightMoveTest(Square** board, int size, Coords start_pos, Coords targ_pos);

bool rookMoveTest(Square** board, int size, Coords start_pos, Coords targ_pos);

bool queenMoveTest(Square** board, int size, Coords start_pos, Coords targ_pos);

bool kingMoveTest(Square** board, int size, Coords start_pos, Coords targ_pos); 

bool checkTest(Square** board, int size, Coords kingpos, Color piece_color);

bool checkMateTest(Square** board, int size, Coords kingpos);

void moveExecute(Square** board, int size,Coords start_pos,Coords targ_pos);

bool checkTestAfterMove(Square** board, int size, Coords start_pos, Coords targ_pos, Coords kingpos, Color kingcolor);



void initializeSavesIndex();



bool exportBoard(Square** board, int size, char* save_name, Color turn);

SaveInfo getSaveInfo(int line_number);

void importBoard(Square** board, int size, char* save_name);

void ripSave(char* save_name);



#endif