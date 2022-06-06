#ifndef _DISPLAY_HEADER_
#define _DISPLAY_HEADER_

#include <game.h>


void Clean();

void InitializeOutputOptions();

void StdinClear();

char MenuInput();

bool GamemodeInput();

int ChessBoardSizeInput();

void MoveInput(square** board, int size, bool turn, coords* startcoords, coords* targcoords, coords* kingpos);

char ActionInput();

void PrintPiece(square piece, bool fancyprint);

void BoardPrint(square** board, int size, bool fancyprint);

void SaveNameInput(char* string);

bool QuitConfirmation();

int PrintSaves();

#endif