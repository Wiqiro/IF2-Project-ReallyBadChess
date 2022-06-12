#ifndef _DISPLAY_HEADER_
#define _DISPLAY_HEADER_

#include <game.h>

/**
 * @brief Clear the console (OS-dependant command)
 * 
 */
void clear();

/**
 * @brief Enable UTF-8 for windows
 * 
 */
void initializeOutputOptions();

/**
 * @brief Clean the Stdin stream
 * 
 */
void stdinClean();

/**
 * @brief Main menu choice secure input
 * 
 * @return char the user input
 */
char menuInput();

/**
 * @brief Gamemode choice secure input
 * 
 * @return true for Really Bad Chess mode
 * @return false for Classic mode
 */
bool gamemodeInput();

/**
 * @brief Secured input for the size of the board
 * 
 * @return int the size of the board
 */
int chessBoardSizeInput();

/**
 * @brief Secure input for a piece move (will check)
 * 
 * @param board Board where the move has to be checked
 * @param size Size of the board
 * @param turn Player turn
 * @param start_coords Start position of the move (modified by adress passing)
 * @param targ_coords Target position of the move (modified by adress passing)
 * @param king_pos Position of the king (has to have the same color as the turn)
 */
void moveInput(Square** board, int size, bool turn, Coords* start_coords, Coords* targ_coords, Coords* king_pos);

/**
 * @brief Secure input for action input before a turn
 * 
 * @return char the user input
 */
char actionInput();

/**
 * @brief Print the specified piece
 * 
 * @param piece The piece to print
 * @param fancy_print The print mode (true for UTF-8 characters or false for letters)
 */
void printPiece(Square piece, bool fancy_print);

/**
 * @brief Print the specified board
 * 
 * @param board Board to print
 * @param size Size of the board
 * @param fancy_print The print mode (true for UTF-8 characters or false for letters)
 */
void boardPrint(Square** board, int size, bool fancy_print);

/**
 * @brief Secured input for the name of the save
 * 
 * @param string The name of the save (modified by adress passing)
 */
void saveNameInput(char* string);

/**
 * @brief Secured input for the display mode
 * 
 * @return true for Fancy mode
 * @return false for Letters mode
 */
bool fancyModeInput();

/**
 * @brief Secured input for quit confirmation
 * 
 * @return true if the user want to quit
 * @return false if the user want to stay
 */
bool quitConfirmation();

/**
 * @brief Print the saves and collect secure unput for the save number
 * 
 * @return int the save number
 */
int printSaves();

/**
 * @brief Secure input for action when selecting a save
 * 
 * @return char the user input
 */
char saveActionInput();

/**
 * @brief Print the welcome screen
 * 
 */
void welcomeScreen();

/**
 * @brief Print quit screen
 * 
 */
void quitScreen();

#endif