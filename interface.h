#ifndef _DISPLAY_HEADER_
#define _DISPLAY_HEADER_

#include <game.h>


void Clean();

void StdinClear();

char MenuInput();

bool GamemodeInput();

int ChessBoardSizeInput();

void MoveInput(int* coordsarray, int size);

char ActionInput();

void PrintPiece(square piece);

void BoardPrint(square** board, int size);

void SaveNameInput(char* string);

bool QuitConfirmation();

int PrintSaves();

void EasterEgg();



//ALT+219 to get a full character (ASCII 256)
//https://www.codeproject.com/Articles/1214018/Chess-Console-Game-in-Cplusplus  board example



#endif