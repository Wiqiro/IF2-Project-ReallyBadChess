#include <stdio.h>
#include <stdlib.h>

#include <board.h>
#include <display.h>


int main(int argc, char* argv[]) {

    

    srand(time(NULL));
    InitializeSavesIndex();
    Clean();

    color turn = white;
    bool whitecheck = false;
    bool blackcheck = false;
    bool checkmate = false;

    int startcoords[2];
    int targcoords[2];
    bool okmove = false;

    square** board = NULL;
    int kingposwhite[2];
    int kingposblack[2];
    
    bool gamemode;
    int size=0;

    printf("Bienvenue dans notre jeu d'echec !\nAppuiez sur entrer pour commencer ");
    
    char menuchoice = MenuInput();

    switch (menuchoice) {
    case 'N':
        gamemode = GamemodeInput();
        if (gamemode == 0) {
            size = 8;
            board = CreateBoard(size);
            InitializeBoardClassic(board);

            kingposwhite[0] = 4;
            kingposblack[0] = 4;

        } else {
            size = ChessBoardSizeInput();
            board = CreateBoard(size);
            InitializeBoardRandom(board, size);

            for (int x=0; x<size; x++) {
                if (board[x][0].type == king) {
                    kingposblack[0] = x;
                } else if (board[x][size].type == king) {
                    kingposwhite[0] = x;
                }
            }
        }
        kingposwhite[1] = size-1;
        kingposblack[1] = 0;

        while (checkmate == false) {
            Clean();

            BoardPrint(board, size);

            okmove = false;



            switch (ActionInput()) {
            case 'J':
                do {
                    do {
                        printf("Entrez les coordonnées de la pièce que vous souhaitez bouger: ");
                        MoveInput(startcoords, size);
                        if (board[startcoords[0]][startcoords[1]].color != turn) {
                            printf("\nCe n'est pas votre tour");
                        } else if (((turn == white && whitecheck == true) || (turn == black && blackcheck == true)) && board[startcoords[0]][startcoords[1]].type != king) {
                            printf("\nVous devez bouger votre roi !");
                        } else {
                            okmove = true;
                        }
                    } while (okmove == false);

                    printf("\nEntrez les coordonnées de la case où vous souhaitez bouger la pièce: ");
                    MoveInput(targcoords, size);

                    if ((okmove = MoveTest(board, size, startcoords[0], startcoords[1], targcoords[0], targcoords[1])) == false) {
                        printf("\nCe mouvement est interdit !");
                    }
                } while (okmove == false);
                        MoveExecute(board, size, startcoords[0], startcoords[1], targcoords[0], targcoords[1]);


                if (turn == white && board[targcoords[0]][targcoords[1]].type == king) {
                    kingposwhite[0] = targcoords[0];
                    kingposwhite[1] = targcoords[1];
                    
                } else if (turn == black && board[targcoords[0]][targcoords[1]].type == king) {
                    kingposblack[0] = targcoords[0];
                    kingposblack[1] = targcoords[1];
                    }

                blackcheck = CheckTest(board, size, kingposblack[0], kingposblack[1]);
                if (blackcheck == true) {
                    checkmate = CheckMateTest(board, size, kingposblack[0], kingposblack[1]);
                }
                whitecheck = CheckTest(board, size, kingposwhite[0], kingposwhite[1]);
                if (whitecheck == true) {
                    checkmate = CheckMateTest(board, size, kingposwhite[0], kingposwhite[1]);
                }

                turn = (turn + 1) % 2;

                break;
            
            case 'S': ;

                char savename[20];
                SaveNameInput(savename);
                ExportBoard(board, size, savename);
                break;

            case 'X': ;
                if(QuitConfirmation() == true) {
                    EasterEgg();
                    FreeBoard(&board, size);
                    return EXIT_SUCCESS;
                }
                break;

            default:
                break;
            }
        }
        FreeBoard(&board, size);
        break;
    
    case 'I':

        printf("%d",PrintSaves());

        break;
    
    case 'Q':
        if (QuitConfirmation() == true) {
            EasterEgg();
            return EXIT_SUCCESS;
        }

    default:
        break;
    }
 
    return EXIT_SUCCESS;
}