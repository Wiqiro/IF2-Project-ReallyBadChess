#include <stdio.h>
#include <stdlib.h>

#include <game.h>
#include <interface.h>

int main(int argc, char* argv[]) {

    InitializeOutputOptions();

    srand(time(NULL));
    InitializeSavesIndex();
    Clean();

    color turn = white;
    bool whitecheck = false;
    bool blackcheck = false;
    bool checkmate = false;

    bool initialized = false;

    int startcoords[2];
    int targcoords[2];

    square** board = NULL;
    int kingposwhite[2];
    int kingposblack[2];
    
    bool gamemode;
    int size = 0;
    //bool gameend = false;
    bool fancyprint = true;

    printf("Bienvenue dans notre jeu d'echec !\nAppuiez sur entrer pour commencer ");

    char menuchoice;
    do {
        if (!initialized) {
            menuchoice = MenuInput();
        } else {
            menuchoice = 'N';
        }
        
        switch (menuchoice) {
        case 'N':
            if (!initialized) {
                gamemode = GamemodeInput();
                if (gamemode == 0) {
                    size = 8;
                    board = CreateBoard(size);
                    InitializeBoardClassic(board);
                } else {
                    size = ChessBoardSizeInput();
                    board = CreateBoard(size);
                    InitializeBoardRandom(board, size);

                    for (int x=0; x<size; x++) {
                        if (board[x][0].type == king) {
                            kingposblack[0] = x;
                        } else if (board[x][size-1].type == king) {
                            kingposwhite[0] = x;
                        }
                    }
                }
                GetKingPos(board, size, kingposwhite, kingposblack);
            }
            while (checkmate == false) {
                Clean();
                BoardPrint(board, size, fancyprint);
                if (blackcheck == true) printf("\nLe roi noir est en échec !");
                if (whitecheck == true) printf("\nLe roi blanc est en échec !");

                switch (ActionInput()) {
                case 'J':
                                        
                    if (turn == black) {
                        printf("\nC'est au tour des noirs de jouer !");
                        MoveInput(board, startcoords, targcoords, size, turn, kingposblack[0], kingposblack[1]);
                    } else {
                        printf("\nC'est au tour des blancs de jouer !");
                        MoveInput(board, startcoords, targcoords, size, turn, kingposwhite[0], kingposwhite[1]);
                    }

                    MoveExecute(board, size, startcoords[0], startcoords[1], targcoords[0], targcoords[1]);
                    GetKingPos(board, size, kingposwhite, kingposblack);

                    blackcheck = CheckTest(board, size, kingposblack[0], kingposblack[1], black);

                    if (blackcheck == true) checkmate = CheckMateTest(board, size, kingposblack[0], kingposblack[1]);

                    whitecheck = CheckTest(board, size, kingposwhite[0], kingposwhite[1], white);
                    if (whitecheck == true) checkmate = CheckMateTest(board, size, kingposwhite[0], kingposwhite[1]);
                    if (checkmate) {
                        printf("CHECKMATE");
                    } 
                    else {
                        StdinClear();
                        printf("\nAppuiez sur entrer pour passer au tour suivant !");
                        getchar();
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
            initialized = false;
            break;
        
        case 'I': ;
            int linenumber = PrintSaves();

            if (linenumber >= 0) {
                saveinfo save = GetSaveInfo(linenumber);
                printf("%s  %d   %lld\n", save.name, save.size, save.time);
                size = save.size;
                board = CreateBoard(size);
                ImportBoard(board, size, save.name);
                GetKingPos(board, size, kingposwhite, kingposblack);
                initialized = true;
                turn = black;
            }
            break;
        
        case 'Q':
            if (QuitConfirmation() == true) {
                EasterEgg();
            }

        case 'O':
        StdinClear();
        printf("\nQuel mode d'affichage choisissze-vous ? (F: fancy  L: lettres) ");

        if (toupper(getchar()) == 'F') fancyprint = true;
        else fancyprint = false;
        

        default:
            break;
        }
    } while (menuchoice != 'Q');
 
    return EXIT_SUCCESS;
}