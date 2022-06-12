#include <interface.h>



#ifdef _WIN32
    #define OS 0
    #include <windows.h>
#else
    #define OS 1  //assuming that the non-windows systems are linux-based
#endif

/**
 * @brief Clear the console (OS-dependant command)
 * 
 */
void clear() {
    if(OS == 0) {
        system("cls");
    } else {
        system("clear");
    }
}

/**
 * @brief Enable UTF-8 for windows
 * 
 */
void initializeOutputOptions() {
    #ifdef _WIN32
        SetConsoleOutputCP(65001);
    #endif
}

/**
 * @brief Clean the Stdin stream
 * 
 */
void stdinClean() {
    char buffer;
    while ((buffer = getchar()) != '\n');
}

/**
 * @brief Main menu choice secure input
 * 
 * @return char the user input
 */
char menuInput() {

    char buffer;
    do {
        if (buffer != '\n') {
            stdinClean();
        }
        printf("\nChoisissez une option ! (N: nouvelle partie  I: importer une sauvegarde  O: options  Q: quitter)  ");
        buffer = toupper(getchar());
    } while (buffer != 'N' && buffer != 'I' && buffer != 'Q' && buffer != 'O');
    return buffer;
}

/**
 * @brief Gamemode choice secure input
 * 
 * @return true for Really Bad Chess mode
 * @return false for Classic mode
 */
bool gamemodeInput() {
    char game_mode;
    do {
        if (game_mode != '\n') {
            stdinClean();
        }
        printf("\nQuel mode de jeu choisissez-vous ? (B: Really bad chest, C: classic)  ");
        scanf("%c",&game_mode);
        game_mode = toupper(game_mode);

    } while (game_mode != 'B' && game_mode != 'C');

    if (game_mode == 'B') {
        return true;
    } else {
        return false;
    }
}

/**
 * @brief Secured input for the size of the board
 * 
 * @return int the size of the board
 */
int chessBoardSizeInput() {
    char input[2];
    int size=0;
    do {
        printf("\nChoisissez à présent la taille de l'échiquer (de 6x6 à 12x12)  ");

        stdinClean();
        scanf("%2[^\n]",input);
        size = strtol(input, NULL, 10);
        
    } while (size > 12 || size < 6);
    return size;
}

/**
 * @brief Secure input for a piece move (will check)
 * 
 * @param board Board where the move has to be checked
 * @param size Size of the board
 * @param turn Player turn
 * @param start_coords Start position of the move (modified by adress passing)
 * @param targ_coords Target position of the move (modified by adress passing)
 * @param king_pos Position of the king (has to have the same color as the turn)
 */
void moveInput(Square** board, int size, bool turn, Coords* start_coords, Coords* targ_coords, Coords* king_pos) {

    bool ok_move = false;
    char input[3];
    do {
        do {
            printf("\nEntrez les coordonnées de la pièce que vous souhaitez bouger: ");
            stdinClean();
            scanf("%3[^\n]", input);

            start_coords->x = toupper(input[0]) - 'A';
            if (input[2] == '\0') {
                start_coords->y = size - input[1] + '0';
            } else {
                start_coords->y = size - input[2] + '0' - 10;
            }
            if (start_coords->x < 0 || start_coords->x >= size || start_coords->y < 0 || start_coords->y >= size) {
                printf("Cette pièce ne fait pas partie de l'échiquier !\n");                            
            } else if (board[start_coords->x][start_coords->y].type == empty) {
                printf("Cette case est vide\n");
            } else if (board[start_coords->x][start_coords->y].color != turn) {
                printf("Ce n'est pas votre tour\n");
            } else {
                ok_move = true;
            }

        } while (!ok_move);

        ok_move = true;
        stdinClean();
        printf("Entrez les coordonnées de la case où vous souhaitez bouger la pièce: ");
        scanf("%3[^\n]", input);
        
        targ_coords->x = toupper(input[0]) - 'A';
        if (input[2] == '\0') {
            targ_coords->y = size - input[1] + '0';
        } else {
            targ_coords->y = size - input[2] + '0' - 10;
        }

        if (moveTest(board, size, *start_coords, *targ_coords) == false) {
            printf("Ce mouvement est interdit !\n");
            ok_move = false;
        } else if (board[targ_coords->x][targ_coords->y].color == turn && board[targ_coords->x][targ_coords->y].type != empty) {
            printf("Vous ne pouvez pas prendre vos propres pièces !\n");
            ok_move = false;
        } else if (board[start_coords->x][start_coords->y].type == king && checkTest(board, size, *targ_coords, board[king_pos->x][king_pos->y].color) == true) {
            printf("Vous ne pouvez pas mettre votre roi en échec !\n");
            ok_move = false;
        } else if (board[start_coords->x][start_coords->y].type != king && checkTestAfterMove(board, size, *start_coords, *targ_coords, *king_pos, board[king_pos->x][king_pos->y].color)) {
            printf("Vous ne pouvez pas mettre votre roi en échec\n");
            ok_move = false;
        }
    } while (!ok_move);
}

/**
 * @brief Secure input for the action to execute before a turn
 * 
 * @return char the user input
 */
char actionInput() {

    char buffer;
    do {
        if (buffer != '\n') {
            stdinClean();
        }
        printf("\nQue voulez-vous faire ? (J: jouer  S: sauvegarder  O: options  X: abandonner)  ");
        buffer = toupper(getchar());

    } while (buffer != 'J' && buffer != 'S' && buffer != 'X' && buffer != 'O');
    return buffer;
}

/**
 * @brief Print the specified piece
 * 
 * @param piece The piece to print
 * @param fancy_print The print mode (true for UTF-8 characters or false for letters)
 */
void printPiece(Square Piece, bool fancy_print) {

    if (fancy_print) {
        if (Piece.color == black) {
            switch (Piece.type) {
            case pawn:
                printf("♙");
                break;
            case bishop:
                printf("♗");
                break;
            case knight:
                printf("♘");
                break;
            case rook:
                printf("♖");
                break;
            case queen:
                printf("♕");
                break;
            case king:
                printf("♔");
                break;
            default:
                printf(" ");
                break;
            }
        } else {
            switch (Piece.type) {
            case pawn:
                printf("♟");
                break;
            case bishop:
                printf("♝");
                break;
            case knight:
                printf("♞");
                break;
            case rook:
                printf("♜");
                break;
            case queen:
                printf("♛");
                break;
            case king:
                printf("♚");
                break;
                    
            default:
                printf(" ");
                break;
            }
        }
        printf(" ");
    } else {
        if (Piece.type != empty) {
            switch (Piece.type) {
            case pawn:
                printf("P");
                break;
            case bishop:
                printf("F");
                break;
            case knight:
                printf("C");
                break;
            case rook:
                printf("T");
                break;
            case queen:
                printf("D");
                break;
            case king:
                printf("R");
                break;
            default:
                break;
            }
            if (Piece.color == white) {
                printf("B");
            } else {
                printf("N");
            }
        } else {
            printf("  ");
        }
    }
}

/**
 * @brief Print the specified board
 * 
 * @param board Board to print
 * @param size Size of the board
 * @param fancy_print The print mode (true for UTF-8 characters or false for letters)
 */
void boardPrint(Square** board, int size, bool fancy_print) {

    printf(" ╭");

    for (int x=0; x<size; x++) {
        printf("────┬");
    }
    printf("────╮\n │");

    for (int y=0; y<size-1; y++) {
        printf(" ");
        if (size < 10 || y > (size-10)) {
                printf("0");
        }
        printf("%d", size-y);
        for (int x=0; x<size; x++) {
            printf(" │ ");
            printPiece(board[x][y], fancy_print);
        }
        
        printf(" │ \n ├");
        for (int x=0; x<size; x++) {
        printf("────┼");
        }
        printf("────┤\n │");
    }

    printf(" 01");
    for (int x=0; x<size; x++) {
        printf(" │ ");
        printPiece(board[x][size-1], fancy_print);
    }

    printf(" │\n ╰");
    for (int x=0; x<size; x++) {
        printf("────┼");
    }

    printf("────┤\n      │");
    for (int x=0; x<size; x++) {
        printf(" %c  │",x+'A');
    }

    printf("  \n      ╰");
    for (int x=0; x<size-1; x++) {
        printf("────┴");
    }
    printf("────╯\n");
}

/**
 * @brief Secured input for the name of the save
 * 
 * @param string The name of the save (modified by adress passing)
 */
void saveNameInput(char* string) {

    char buffer[21];
    int buffer_size = 0;
    bool ok_lenght = false;

    do {
        stdinClean();
        printf("\nSous quel nom voulez-vous sauvegarder votre partie ?  ");
        scanf("%21[^\n]", buffer);
        buffer_size = strlen(buffer);
        if (buffer_size > 20) {
            printf("Entrez un nom de moins de 20 charactères \n");
        } else if (buffer_size < 2) {
            printf("Entrez un nom plus long\n");
        } else {

            int i = 0;
            while (i < buffer_size-1 && buffer[i] > ' ' && buffer[i] != '/' && buffer[i] != '\\' && buffer[i] != '*' && buffer[i] != ':' && buffer[i] != '|' && buffer[i] != '"' && buffer[i] != '<' && buffer[i] != '>' && buffer[i] != '?') {
                i++;
            }
            if (i == buffer_size-1) {
                ok_lenght = true;
            } else {
                printf("Votre nom contient un caractère interdit (caractère %d)\n", i+1);
            }
        }
    } while (ok_lenght == false);
    strncpy(string, buffer, 20);
    stdinClean();
}

/**
 * @brief Secured input for the display mode
 * 
 * @return true for Fancy mode
 * @return false for Letters mode
 */
bool fancyModeInput() {

    char buffer;
    do {
        if (buffer != '\n') {
            stdinClean();
        }
        printf("\nQuel mode d'affichage choisissze-vous ? (F: fancy  L: lettres) ");
        buffer = toupper(getchar());

    } while (buffer != 'F' && buffer != 'L');
    if (buffer == 'F') {
        return true;
    } else {
        return false;
    }
}


void CheckMateScreen(Square** board, Coords king_pos) {
    clear();
    if (board[king_pos.x][king_pos.y].color == white);
}

/**
 * @brief Secured input for quit confirmation
 * 
 * @return true if the user want to quit
 * @return false if the user want to stay
 */
bool quitConfirmation() {
    char buffer;
    do {
        printf("\nVoulez-vous vraiment quitter ? (O: oui N: non)  ");
        if (buffer != '\n') {
            stdinClean();
        }
        buffer = toupper(getchar());
    } while (buffer != 'O' && buffer != 'N');
    if (buffer == 'O') {
        return true;
    } else {
        return false;
    }
}

/**
 * @brief Print the saves and collect secure unput for the save number
 * 
 * @return int the save number
 */
int printSaves() {

    clear();
    printf("Gestion des sauvegardes\n\n");
    char buffer[4][50];
    
    int i = 1;
    FILE* index = fopen("saves.txt","r");
    if (index != NULL) {
        while (fscanf(index, "%50s\t%50s\t%50s\t%50s\n", buffer[0], buffer[1], buffer[2], buffer[3]) != EOF) {
            time_t raw_time = strtoll(buffer[2], NULL, 10);
            int save_name_lenght = strlen(buffer[0]);
            struct tm* save_time = localtime(&raw_time);

            printf("%d: %s", i, buffer[0]);
            for (int j = 0; j < 23 - save_name_lenght; j++) {
                printf(" ");
            }
            printf("(%sx%s)",buffer[1], buffer[1]);
            if (buffer[1][1] == '\0') {
                printf("  ");
            }
            printf("            %02d/%02d/%04d  %02d:%02d\n",save_time->tm_mday, save_time->tm_mon+1, save_time->tm_year+1900, save_time->tm_hour, save_time->tm_min);
            i++;
        }
    }
    fclose(index);

    if (i == 1) {
        clear();
        printf("Aucune sauvegarde n'a été trouvée ...\n\nAppuiez sur entrée pour retourner au menu ");
        stdinClean();
        getchar();
        return -1;
    } else {
        char input[4];
        int save_number;
        do {
            if (input[0] != '\n' && input[1] != '\n') {
                stdinClean();
            }
            printf("\nEntrez le numéro de votre sauvegarde  ");
            fgets(input, 3, stdin);
            save_number = strtol(input, NULL, 10);

            if ((save_number < 1 || save_number >= i) && input[0] != '\n') {
                printf("Cette sauvegarde n'existe pas !\n");
            }

        } while (save_number < 1 || save_number >= i);
        return save_number;
    }
}

/**
 * @brief Secure input for action when selecting a save
 * 
 * @return char the user input
 */
char saveActionInput() {

    char buffer = '\n';
    do {
        if (buffer != '\n') {
            stdinClean();
        }
        printf("\nQue voulez-vous faire ? (I: importer  S: supprimer  R: retour)  ");
        buffer = toupper(getchar());

    } while (buffer != 'I' && buffer != 'S' && buffer != 'R');
    return buffer;
}

/**
 * @brief Print the welcome screen
 * 
 */
void welcomeScreen() {
    printf(" /$$$$$$$  /$$$$$$$$  /$$$$$$  /$$       /$$       /$$     /$$       /$$$$$$$   /$$$$$$  /$$$$$$$         /$$$$$$  /$$   /$$ /$$$$$$$$  /$$$$$$   /$$$$$$ \n");
    printf("| $$__  $$| $$_____/ /$$__  $$| $$      | $$      |  $$   /$$/      | $$__  $$ /$$__  $$| $$__  $$       /$$__  $$| $$  | $$| $$_____/ /$$__  $$ /$$__  $$\n");
    printf("| $$  \\ $$| $$      | $$  \\ $$| $$      | $$       \\  $$ /$$/       | $$  \\ $$| $$  \\ $$| $$  \\ $$      | $$  \\__/| $$  | $$| $$      | $$  \\__/| $$  \\__/\n");
    printf("| $$$$$$$/| $$$$$   | $$$$$$$$| $$      | $$        \\  $$$$/        | $$$$$$$ | $$$$$$$$| $$  | $$      | $$      | $$$$$$$$| $$$$$   |  $$$$$$ |  $$$$$$ \n");
    printf("| $$__  $$| $$__/   | $$__  $$| $$      | $$         \\  $$/         | $$__  $$| $$__  $$| $$  | $$      | $$      | $$__  $$| $$__/    \\____  $$ \\____  $$\n");
    printf("| $$  \\ $$| $$      | $$  | $$| $$      | $$          | $$          | $$  \\ $$| $$  | $$| $$  | $$      | $$    $$| $$  | $$| $$       /$$  \\ $$ /$$  \\ $$\n");
    printf("| $$  | $$| $$$$$$$$| $$  | $$| $$$$$$$$| $$$$$$$$    | $$          | $$$$$$$/| $$  | $$| $$$$$$$/      |  $$$$$$/| $$  | $$| $$$$$$$$|  $$$$$$/|  $$$$$$/\n");
    printf("|__/  |__/|________/|__/  |__/|________/|________/    |__/          |_______/ |__/  |__/|_______/        \\______/ |__/  |__/|________/ \\______/  \\______/\n\n");
    printf("Appuiez sur entrée pour commencer  ");
}

/**
 * @brief Print quit screen
 * 
 */
void quitScreen() {
    clear();
    printf(" /$$$$$$$$ /$$   /$$  /$$$$$$  /$$   /$$ /$$   /$$  /$$$$$$\n");
    printf("|__  $$__/| $$  | $$ /$$__  $$| $$$ | $$| $$  /$$/ /$$__  $$\n");
    printf("   | $$   | $$  | $$| $$  \\ $$| $$$$| $$| $$ /$$/ | $$  \\__/\n");
    printf("   | $$   | $$$$$$$$| $$$$$$$$| $$ $$ $$| $$$$$/  |  $$$$$$\n");
    printf("   | $$   | $$__  $$| $$__  $$| $$  $$$$| $$  $$   \\____  $$\n");
    printf("   | $$   | $$  | $$| $$  | $$| $$\\  $$$| $$\\  $$  /$$  \\ $$\n");
    printf("   | $$   | $$  | $$| $$  | $$| $$ \\  $$| $$ \\  $$|  $$$$$$/\n");
    printf("   |__/   |__/  |__/|__/  |__/|__/  \\__/|__/  \\__/ \\______/\n\n");
    printf(" /$$$$$$$$  /$$$$$$  /$$$$$$$\n");
    printf("| $$_____/ /$$__  $$| $$__  $$\n");
    printf("| $$      | $$  \\ $$| $$  \\ $$\n");
    printf("| $$$$$   | $$  | $$| $$$$$$$/\n");
    printf("| $$__/   | $$  | $$| $$__  $$\n");
    printf("| $$      | $$  | $$| $$  \\ $$\n");
    printf("| $$      |  $$$$$$/| $$  | $$\n");
    printf("|__/       \\______/ |__/  |__/\n\n");
    printf(" /$$$$$$$  /$$        /$$$$$$  /$$     /$$ /$$$$$$ /$$   /$$  /$$$$$$ \n");
    printf("| $$__  $$| $$       /$$__  $$|  $$   /$$/|_  $$_/| $$$ | $$ /$$__  $$\n");
    printf("| $$  \\ $$| $$      | $$  \\ $$ \\  $$ /$$/   | $$  | $$$$| $$| $$  \\__/\n");
    printf("| $$$$$$$/| $$      | $$$$$$$$  \\  $$$$/    | $$  | $$ $$ $$| $$ /$$$$\n");
    printf("| $$____/ | $$      | $$__  $$   \\  $$/     | $$  | $$  $$$$| $$|_  $$\n");
    printf("| $$      | $$      | $$  | $$    | $$      | $$  | $$\\  $$$| $$  \\ $$\n");
    printf("| $$      | $$$$$$$$| $$  | $$    | $$     /$$$$$$| $$ \\  $$|  $$$$$$/\n");
    printf("|__/      |________/|__/  |__/    |__/    |______/|__/  \\__/ \\______/\n\n");
    printf("Appuiez sur entrée pour quitter  ");
    stdinClean();
    getchar();
}