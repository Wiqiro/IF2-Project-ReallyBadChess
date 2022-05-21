#ifndef _DISPLAY_HEADER_
#define _DISPLAY_HEADER_

#include <board.h>
#include <save.h>



void Clean();

void StdinClear();

bool GamemodeInput();

int ChessBoardSizeInput();

void MoveInput(int* coordsarray, int size);

char ActionInput();

void SaveNameInput(char* string);



//ALT+219 to get a full character (ASCII 256)
//https://www.codeproject.com/Articles/1214018/Chess-Console-Game-in-Cplusplus  board example



#endif