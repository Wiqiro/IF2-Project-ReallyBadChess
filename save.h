#ifndef _SAVE_HEADER_
#define _SAVE_HEADER_

#include <board.h>

typedef struct saveinfo {
    char name[32];
    int size;
    long long int time;
} saveinfo;

void InitializeSavesIndex();

saveinfo SaveFinder(char* savename);

void ExportBoard(square** board, int size, char* savename);

void ImportBoard(square** board, int size, char* savename);

void RipSave(char* savename);


#endif