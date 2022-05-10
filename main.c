#include <stdio.h>
#include <stdlib.h>

#include <board.h>
#include <display.h>
#include <moves.h>
#include <save.h>


int main(int argc, char* argv[]) {

    //on va implémenter des fonctions qui dépendent du système d'exploitation plus tard
    srand(time(NULL));


    char gamemode;
    printf("Bienvenue dans notre jeu d'échec !");
    do {
        printf("\nQuel mode de jeu choisissez-vous ? (B: Really bad chest, C: classic)\n");
        scanf("%c",&gamemode);
        gamemode = toupper(gamemode);
    } while (gamemode != 'B' && gamemode != 'C');


    square** board;
    int size=0;
    if (gamemode == 'C') {
        size = 8;
        board = CreateBoard(size);
        InitializeBoardClassic(board);

    } else {
        char input[100];
        do {
            printf("\nChoisissez à présent la taille de l'échiquer (de 6x6 à 12x12)\n");
            fflush(stdin);
            scanf("%s",input);
            size = strtol(input, NULL, 10);
            
        } while (size > 12 || size < 6);
        board = CreateBoard(size);
        InitializeBoardRandom(board, size);
    }


    
    
    
    SimplePrint(board, size);





    return EXIT_SUCCESS;
}