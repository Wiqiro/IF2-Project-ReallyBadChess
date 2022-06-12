#include <game.h>

/**
 * @brief Create a Board object (uninitialized square matrix)
 * 
 * @param size Size of the board
 * @return Return the created board
 */
Square** createBoard(int size) {
    Square** board = (Square**)malloc(sizeof(Square*)*size);
    if (board != NULL) {    //handling potential memory errors
        for (int i=0; i<size; i++) {
            if (board != NULL) {
                board[i] = (Square*)malloc(sizeof(Square)*size);
            }
            else {
                fprintf(stderr,"ERROR CREATING THE BOARD : not enough memory\n");
            }
        }
    } else {
        fprintf(stderr,"ERROR CREATING THE BOARD : not enough memory\n"); 
    }
    return board;
}

/**
 * @brief Initialize the specified board with random pieces (kings will always be in the first or last row). Uses the initlalizeBoardColor function to set the colors of the squares
 * 
 * @param board The board that is going to be initialized
 * @param size The size of the board
 */
void initializeBoardRandom(Square** board, int size){

    initializeBoardColor(board, size);


    //Placing the two kings
    board[rand()%size][size-1].type = king;
    board[rand()%size][0].type = king;


    for (int i = 0; i < size; i++) {
       for(int j = 2; j < size-2; j++) {
        board[i][j].type = empty;
       }
    }

    for(int i=0; i<size; i++) {
        for (int j=0; j<size; j++) {
            if ((j<2 || j>size-3) && board[i][j].type!=king) {
                board[i][j].type = rand()%5+1; //Placing a random Piece (no king)
            }
        }
    }

}

/**
 * @brief Initialize a specified board with the classic pieces layout (only for 8x8 boards). Uses the initlalizeBoardColor function to set the colors of the squares
 * 
 * @param board The board that is going to be initialized
 */
void initializeBoardClassic(Square** board){
    
    initializeBoardColor(board, 8);

    //placing the empty squares
    for (int i = 0; i < 8; i++) {
       for(int j = 2; j < 6; j++) {
        board[i][j].type = empty;
       }
    }

    //placing the pawns
    for (int i = 0; i < 8; i++) {
       board[i][1].type = pawn;
       board[i][6].type = pawn; 
    }
    //placing the rooks
    board[0][0].type = rook;
    board[7][0].type = rook;
    board[0][7].type = rook;
    board[7][7].type = rook;
    //placing the knights
    board[1][0].type = knight;
    board[6][0].type = knight;
    board[1][7].type = knight;
    board[6][7].type = knight;
    //placing the bishops
    board[2][0].type = bishop;
    board[5][0].type = bishop;
    board[2][7].type = bishop;
    board[5][7].type = bishop;
    //placing the queens
    board[3][0].type =  queen;
    board[3][7].type =  queen;
    //placing the kings
    board[4][0].type =  king;
    board[4][7].type =  king;
}

/**
 * @brief Initialize the color of a board by setting the color of the two highest rows to black and the rest to white (color does not matter when the type of the square is empty)
 * 
 * @param board The board where the colors are going to be set up
 * @param size The size of the board
 */
void initializeBoardColor(Square** board, int size) {
    for (int x=0; x<size; x++) {

        for (int y=0; y<2;y++) {
            board[x][y].color = black;
        }
        for (int y=2; y<size;y++) {
            board[x][y].color = white;
        }
    }
}

/**
 * @brief Get the position of both kings in a specified board
 * 
 * @param board Board where the kings have to be found
 * @param size The size of the board
 * @param king_pos_white The coordinates of the white king (modified by the function)
 * @param king_pos_black The coordinates of the black king (modified by the function)
 */
void getKingPos(Square** board, int size, Coords* king_pos_white, Coords* king_pos_black) {
    for (int y=0; y<size; y++) {
        for (int x=0; x<size; x++) {
            if (board[x][y].type == king) {
                if (board[x][y].color == white) {
                    king_pos_white->x = x;
                    king_pos_white->y = y;
                } else {
                    king_pos_black->x = x;
                    king_pos_black->y = y;
                }
            }
        }
    }
}

/**
 * @brief Update the position of both king taking in consideration the last move done 
 * 
 * @param board Board where the kings have to be found
 * @param size Size of the board
 * @param last_move Last move done in the board
 * @param king_pos_white The coordinates of the white king (modified by the function)
 * @param king_pos_black The coordinates of the black king (modified by the function)
 */
void updateKingPos(Square** board, int size, Coords last_move, Coords* king_pos_white, Coords* king_pos_black) {
    if (board[last_move.x][last_move.y].type == king) {
        if (board[last_move.x][last_move.y].color == white) {
            *king_pos_white = last_move;
        } else {
            *king_pos_black = last_move;
        }
    }
}

/**
 * @brief Free the specified board
 * 
 * @param board Board that is going to be freed
 * @param size size of the board
 */
void freeBoard(Square*** board, int size){
    if (*board != NULL) {
        for (int x=0; x<size; x++) {
            if ((*board)[x] != NULL) {
                free ((*board)[x]);
                (*board)[x] = NULL;
            }
        }
    }
    free(*board);
    *board = NULL;
}