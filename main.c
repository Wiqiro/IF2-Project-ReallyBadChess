#include <game.h>
#include <interface.h>

int main(int argc, char* argv[]) {

    InitializeOutputOptions();

    srand(time(NULL));
    InitializeSavesIndex();
    Clean();

    color turn = white;
    bool check = false;
    bool checkmate = false;

    bool initialized = false;

    coords startcoords;
    coords targcoords;

    square** board = NULL;
    coords kingposwhite;
    coords kingposblack;
    
    bool gamemode;
    int size = 0;

    bool fancyprint = true;
    bool quit = false;

    WelcomeScreen();

    char menuchoice;
    do {
        if (initialized == false) {
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
                            kingposblack.x = x;
                        } else if (board[x][size-1].type == king) {
                            kingposwhite.x = x;
                        }
                    }
                    kingposblack.y = 0;
                    kingposwhite.y = size-1;
                }
                GetKingPos(board, size, &kingposwhite, &kingposblack);
                initialized = true;
            }
            checkmate = false;
            while (checkmate == false) {
                Clean();
                BoardPrint(board, size, fancyprint);
                if (turn == black) {
                    printf("C'est au tour des noirs de jouer !\n");
                } else {
                    printf("C'est au tour des blancs de jouer !\n");
                }
                if (check == true) {
                    printf("Votre roi est en échec !\n");
                }

                switch (ActionInput()) {
                case 'J':
                    
                    if (turn == black) {
                        MoveInput(board, size, turn, &startcoords, &targcoords, &kingposblack);
                    } else {
                        MoveInput(board, size, turn, &startcoords, &targcoords, &kingposwhite);
                    }
                    
                    MoveExecute(board, size, startcoords, targcoords);
                    UpdateKingPos(board, size ,targcoords, &kingposwhite, &kingposblack);

                    if (CheckTest(board, size, kingposblack, black) == true) {
                        checkmate = CheckMateTest(board, size, kingposblack);
                        check = true;
                    } else if (CheckTest(board, size, kingposwhite, white) == true) {
                        checkmate = CheckMateTest(board, size, kingposwhite);
                        check = true;
                    } else {
                        check = false;
                    }
                    if (checkmate) {
                        printf("CHECKMATE");
                    }
                    turn = !turn;
                    break;
                
                case 'S': ;
                    char savename[20];
                    SaveNameInput(savename);
                    ExportBoard(board, size, savename, turn);
                    break;

                case 'X': ;
                    if (QuitConfirmation() == true) {
                        FreeBoard(&board, size);
                        initialized = false;
                        checkmate = true;
                    }
                    break;

                case 'O':
                    fancyprint = FancyModeInput();
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
                size = save.size;
                board = CreateBoard(size);
                ImportBoard(board, size, save.name);
                GetKingPos(board, size, &kingposwhite, &kingposblack);
                initialized = true;
                turn = save.turn;
            }
            break;
        
        case 'Q':
            if (QuitConfirmation() == true) {
                QuitScreen();
                quit = true;
            }
            break;

        case 'O':
            fancyprint = FancyModeInput();
            break;

        default:
            break;
        }
    } while (quit == false);
 
    return EXIT_SUCCESS;
}