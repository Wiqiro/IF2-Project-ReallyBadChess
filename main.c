#include <stdio.h>
#include <stdlib.h>

#include <board.h>
#include <display.h>
#include <moves.h>
#include <save.h>


int main(int argc, char* argv[]) {

    srand(time(NULL));

    Clean();

    bool gamemode;
    printf("Bienvenue dans notre jeu d'echec !");
    gamemode = GamemodeInput();

    square** board;
    int size=0;
    if (gamemode == 0) {
        size = 8;
        board = CreateBoard(size);
        InitializeBoardClassic(board);

    } else {
        size = ChessBoardSizeInput();
        board = CreateBoard(size);
        InitializeBoardRandom(board, size);
    }

    SimplePrint(board, size);





    return EXIT_SUCCESS;
}