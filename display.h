#ifndef _DISPLAY_HEADER_
#define _DISPLAY_HEADER_

#include <board.h>
//#include <wchar.h>
//#include <locale.h>



void Clean();

void StdinClear();

char MenuInput();

bool GamemodeInput();

int ChessBoardSizeInput();

void MoveInput(int* coordsarray, int size);

char ActionInput();

/**
 * @brief Generic print of the chessboard
 * 
 * @param board Board to print
 * @param size Size of the board
 */
void SimplePrint(square** board, int size);

wchar_t ConvertPiece(square piece);

void BoardPrint(square** board, int size);

void SaveNameInput(char* string);

bool QuitConfirmation();

int PrintSaves();

void EasterEgg();



//ALT+219 to get a full character (ASCII 256)
//https://www.codeproject.com/Articles/1214018/Chess-Console-Game-in-Cplusplus  board example



#endif