#include <stdio.h>
#include <stdlib.h>

#include <board.h>
#include <display.h>
#include <moves.h>
#include <save.h>


int main(int argc, char* argv[]) {

    //juste pour test
    bool a_supprimer = true;

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

    bool turn = false;
    int* startcoords = (int*) malloc(sizeof(int) * 2);
    int* targcoords = (int*) malloc(sizeof(int) * 2);


    while (a_supprimer == true) {
        Clean();

        SimplePrint(board, size);

        do {
        printf("Entrez les coordonnées de la pièce que vous souhaitez bouger: ");
        startcoords = MoveInput(size);

        printf("\nEntrez les coordonnées de la case où vous souhaitez bouger la pièce: ");
        targcoords = MoveInput(size);

        } while (board[startcoords[0]][startcoords[1]].color != turn || MoveTest(board, size, startcoords[0], startcoords[1], targcoords[0], targcoords[1]) != true );
        
        MoveExecute(board, size, startcoords[0], startcoords[1], targcoords[0], targcoords[1]);

        turn = (turn + 1) % 2;


    }
    SimplePrint(board, size);

    printf("%d %d    %d %d",startcoords[0],startcoords[1],targcoords[0],targcoords[1]);




    return EXIT_SUCCESS;
}