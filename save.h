#ifndef _SAVE_HEADER_
#define _SAVE_HEADER_

#include <board.h>

typedef struct saveinfo {
    char name[32];
    int size;
    long int time;
} saveinfo;

void InitializeSavesIndex();

saveinfo* SaveParser(char* rawsave);

void ExportBoard(square** board, int size, char* savename);

void ImportBoard(square** board, int size, char* filename);


#endif