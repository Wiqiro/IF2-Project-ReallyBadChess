#include <game.h>
#include <interface.h>

int main(int argc, char* argv[]) {

    initializeOutputOptions();

    srand(time(NULL));
    initializeSavesIndex();
    clean();

    Color turn = white;
    bool check = false;
    bool checkmate = false;

    bool initialized = false;

    Coords start_coords;
    Coords targ_coords;

    Square** board = NULL;
    Coords king_pos_white;
    Coords king_pos_black;
    
    bool game_mode;
    int size = 0;

    bool fancy_print = true;
    bool quit = false;

    welcomeScreen();

    char menu_choice;
    do {
        if (initialized == false) {
            menu_choice = menuInput();
        } else {
            menu_choice = 'N';
        }
        
        switch (menu_choice) {
        case 'N':
            if (!initialized) {
                game_mode = gamemodeInput();
                if (game_mode == 0) {
                    size = 8;
                    board = createBoard(size);
                    initializeBoardClassic(board);
                } else {
                    size = chessBoardSizeInput();
                    board = createBoard(size);
                    initializeBoardRandom(board, size);

                    for (int x=0; x<size; x++) {
                        if (board[x][0].type == king) {
                            king_pos_black.x = x;
                        } else if (board[x][size-1].type == king) {
                            king_pos_white.x = x;
                        }
                    }
                    king_pos_black.y = 0;
                    king_pos_white.y = size-1;
                }
                getKingPos(board, size, &king_pos_white, &king_pos_black);
                initialized = true;
            }
            checkmate = false;
            while (checkmate == false) {
                clean();
                boardPrint(board, size, fancy_print);
                if (turn == black) {
                    printf("C'est au tour des noirs de jouer !\n");
                } else {
                    printf("C'est au tour des blancs de jouer !\n");
                }
                if (check == true) {
                    printf("Votre roi est en échec !\n");
                }

                switch (actionInput()) {
                case 'J':
                    
                    if (turn == black) {
                        moveInput(board, size, turn, &start_coords, &targ_coords, &king_pos_black);
                    } else {
                        moveInput(board, size, turn, &start_coords, &targ_coords, &king_pos_white);
                    }
                    
                    moveExecute(board, size, start_coords, targ_coords);
                    updateKingPos(board, size ,targ_coords, &king_pos_white, &king_pos_black);

                    if (checkTest(board, size, king_pos_black, black) == true) {
                        checkmate = checkMateTest(board, size, king_pos_black);
                        check = true;
                    } else if (checkTest(board, size, king_pos_white, white) == true) {
                        checkmate = checkMateTest(board, size, king_pos_white);
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
                    char save_name[20];
                    saveNameInput(save_name);
                    
                    if (exportBoard(board, size, save_name, turn) == true) {
                        printf("\nLa partie a été sauvegardée !\nAppuiez sur entrée pour continuer  ");
                    } else {
                        printf("\nIl y a eu un problème lors de l'exportation de la sauvagarde: il existe surement déjà une sauvegarde portant ce nom\nAppuiez sur entrée pour continuer  ");
                    }
                    stdinClear();
                    getchar();
                    
                    break;

                case 'X': ;
                    if (quitConfirmation() == true) {
                        freeBoard(&board, size);
                        initialized = false;
                        checkmate = true;
                    }
                    break;

                case 'O':
                    fancy_print = fancyModeInput();
                    break;
            
                default:
                    break;
                }
            }
            freeBoard(&board, size);
            initialized = false;
            break;
        
        case 'I': ;
            int line_number = printSaves();

            if (line_number >= 0) {
                SaveInfo save = getSaveInfo(line_number);
                size = save.size;
                board = createBoard(size);
                importBoard(board, size, save.name);
                getKingPos(board, size, &king_pos_white, &king_pos_black);
                initialized = true;
                turn = save.turn;
            }
            break;
        
        case 'Q':
            if (quitConfirmation() == true) {
                quitScreen();
                quit = true;
            }
            break;

        case 'O':
            fancy_print = fancyModeInput();
            break;

        default:
            break;
        }
    } while (quit == false);
 
    return EXIT_SUCCESS;
}