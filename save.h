#ifndef _SAVE_HEADER_
#define _SAVE_HEADER_

#include <board.h>


void ExportBoard(square** board, int size);

void ImportBoard(square** board, int size, char* filename);


#endif