#include <board.h>


/**
 * @brief Create Board object (square matrix)
 * 
 * @param size size of the board (nxn)
 * @return square** the board created
 */
square** CreateBoard(int size) {
    square** board = (square**)malloc(sizeof(square*)*size);
    for (int i=0; i<size; i++) {
        board[i] = (square*)malloc(sizeof(square)*size);
    }

    if (board == NULL) {    //handling potential memory errors
        fprintf(stderr,"ERROR CREATING THE BOARD : not enough memory\n"); 
    }
    
    return board;
}



/**
 * @brief Place the chess pieces randomly (only one king, following the classic rules)
 * 
 * @param board Board to modify
 * @param size Size of the board
 */
void InitializeBoardRandom(square** board, int size){

    //Setting up pieces colors
    for (int x=0; x<size; x++) {
        for (int y=0; y<2;y++) {
            board[x][y].color = black;
        }
        for (int y=size-2; y<size;y++) {
            board[x][y].color = white;
        }
    }

    //Placing white and black kings
    board[rand()%size][size-1].type = king;
    board[rand()%size][0].type = king;

    for(int i=0; i<size; i++) {
        for (int j=0; j<size; j++) {
            if ((j<2 || j>size-3) && board[i][j].type!=king) {
                board[i][j].type = rand()%5+1; //Placing a random piece (can't be a king)
            }
        }
    }

}


/**
 * @brief Place the pieces on the specified following the classic chess rules
 * 
 * @param board Board to modify (has to be a 8x8 board)
 */
void InitializeBoardClassic(square** board){

}


/**
 * @brief Generic print of the chessboard (first number = color of the piece and second number = type of the piece)
 * 
 * @param board Board to print
 * @param size Size of the board
 */
void SimplePrint(square** board, int size) {
    for (int y=0; y<size; y++) {
        for (int x=0; x<size; x++) {
            printf("%d%d  ",board[x][y].color,board[x][y].type);
        }
        printf("\n");
    }
}


/**
 * @brief Free the specified board
 * 
 * @param board Board to free
 * @param size Size of the board
 */
void FreeBoard(square** board, int size){

}