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
} piece;

typedef enum {
    white = 0,
    black = 1,
} color;

//definition of the structure of a board square : type (0=empty, 1=pawn, 2=bishop, 3=knight, 4=rook, 5=queen, 6=king) and color (0=white, 1=black)
typedef struct square {
    piece type;
    color color;
} square;

typedef struct coords {
    int x;
    int y;
} coords;

typedef struct saveinfo {
    char name[32];
    int size;
    long long int time;
    int turn;
} saveinfo;


square** CreateBoard(int size);

void InitializeBoardRandom(square** board, int size);

void InitializeBoardClassic(square** board);

void InitializeBoardColor(square** board, int size);

void GetKingPos(square** board, int size, coords* kingposwhite, coords* kingposblack);

void UpdateKingPos(square** board, int size, coords lastmove, coords* kingposwhite, coords* kingposblack);

void FreeBoard(square*** board, int size);



bool CollisionTest(square** board, int size, coords startpos, coords targpos);

bool MoveTest(square** board, int size, coords startpos, coords targpos);

bool PawnMoveTest(square** board, int size, coords startpos, coords targpos);

bool BishopMoveTest(square** board, int size, coords startpos, coords targpos);

bool KnightMoveTest(square** board, int size, coords startpos, coords targpos);

bool RookMoveTest(square** board, int size, coords startpos, coords targpos);

bool QueenMoveTest(square** board, int size, coords startpos, coords targpos);

bool KingMoveTest(square** board, int size, coords startpos, coords targpos); 

bool CheckTest(square** board, int size, coords kingpos, color piececolor);

bool CheckMateTest(square** board, int size, coords kingpos);

void MoveExecute(square** board, int size,coords startpos,coords targpos);

bool CheckTestAfterMove(square** board, int size, coords startpos, coords targpos, coords kingpos, color kingcolor);



void InitializeSavesIndex();

void IndexToString(char* rawstring);

bool ExportBoard(square** board, int size, char* savename, color turn);

saveinfo GetSaveInfo(int index);

void ImportBoard(square** board, int size, char* savename);

void RipSave(char* savename);



#endif