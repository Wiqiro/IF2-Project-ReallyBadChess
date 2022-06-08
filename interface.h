#ifndef _DISPLAY_HEADER_
#define _DISPLAY_HEADER_

#include <game.h>


void clean();

void initializeOutputOptions();

void stdinClear();

char menuInput();

bool gamemodeInput();

int chessBoardSizeInput();

void moveInput(Square** board, int size, bool turn, Coords* start_coords, Coords* targ_coords, Coords* king_pos);

char actionInput();

void printPiece(Square Piece, bool fancy_print);

void boardPrint(Square** board, int size, bool fancy_print);

void saveNameInput(char* string);

bool fancyModeInput();

bool quitConfirmation();

int printSaves();

void welcomeScreen();

void quitScreen();

#endif