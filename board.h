#ifndef _BOARD_HEADER_
#define _BOARD_HEADER_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct square {
    int type;
    bool color;
} square;



square** CreateAndInitializeBoard(int size);

void InitializeBoard(square** board, int size);



void FreeBoard(square** board, int size);



#endif