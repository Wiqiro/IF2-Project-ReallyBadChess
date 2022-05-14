#include <board.h>




/**
 * @brief Create a 2x1 array
 * 
 * @return int* array generated
 */
int* CoordsArray() {
    int* array = (int*) malloc(sizeof(int) * 2);
    array[0] = 0;
    array[1] = 0;
    return array;
}


/**
 * @brief Create Board object (square matrix)
 * 
 * @param size size of the board (nxn)
 * @return square** the board created
 */
square** CreateBoard(int size) {
    square** board = (square**)malloc(sizeof(square*)*size);
    if (board != NULL) {    //handling potential memory errors
        for (int i=0; i<size; i++) {
            if (board != NULL) {
                board[i] = (square*)malloc(sizeof(square)*size);
                //board[i][j].type
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
 * @brief Place the chess pieces randomly (only one king, following the classic rules)
 * 
 * @param board Board to modify
 * @param size Size of the board
 */
void InitializeBoardRandom(square** board, int size){

    InitializeBoardColor(board, size);


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
    
    InitializeBoardColor(board, 8);

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

void InitializeBoardColor(square** board, int size) {
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
    printf("\n");
}


/**
 * @brief Free the specified board
 * 
 * @param board Board to free
 * @param size Size of the board
 */
void FreeBoard(square*** board, int size){
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