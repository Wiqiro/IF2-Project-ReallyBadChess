#include <interface.h>



#ifdef _WIN32
    #define OS 0
    #include <windows.h>
#else
    #define OS 1  //assuming that the non-windows systems are linux-based
#endif


void clean() {
    if(OS == 0) {
        system("cls");
    } else {
        system("clear");
    }
}

void initializeOutputOptions() {
    #ifdef _WIN32
        SetConsoleOutputCP(65001);
    #endif
}

void stdinClear() {
    char buffer;
    while ((buffer = getchar()) != '\n');
}

char menuInput() {

    char buffer;
    do {
        if (buffer != '\n') {
            stdinClear();
        }
        printf("\nChoisissez une option ! (N: nouvelle partie  I: importer une sauvegarde  O: options  Q: quitter)  ");
        buffer = toupper(getchar());
    } while (buffer != 'N' && buffer != 'I' && buffer != 'Q' && buffer != 'O');
    return buffer;
}

bool gamemodeInput() {
    char game_mode;
    do {
        if (game_mode != '\n') {
            stdinClear();
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


int chessBoardSizeInput() {
    char input[2];
    int size=0;
    do {
        printf("\nChoisissez à présent la taille de l'échiquer (de 6x6 à 12x12)  ");

        stdinClear();
        scanf("%2[^\n]",input);
        size = strtol(input, NULL, 10);
        
    } while (size > 12 || size < 6);
    return size;
}

void moveInput(Square** board, int size, bool turn, Coords* start_coords, Coords* targ_coords, Coords* king_pos) {

    bool ok_move = false;
    char input[3];
    do {
        do {
            printf("\nEntrez les coordonnées de la pièce que vous souhaitez bouger: ");
            stdinClear();
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
        stdinClear();
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

char actionInput() {

    char buffer;
    do {
        if (buffer != '\n') {
            stdinClear();
        }
        printf("\nQue voulez-vous faire ? (J: jouer  S: sauvegarder  O: options  X: abandonner)  ");
        buffer = toupper(getchar());

    } while (buffer != 'J' && buffer != 'S' && buffer != 'X' && buffer != 'O');
    return buffer;
}


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

void saveNameInput(char* string) {

    char buffer[21];
    int buffer_size = 0;
    bool ok_lenght = false;

    do {
        stdinClear();
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
}

bool fancyModeInput() {

    char buffer;
    do {
        if (buffer != '\n') {
            stdinClear();
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
    clean();
    if (board[king_pos.x][king_pos.y].color == white);
}

bool quitConfirmation() {
    char buffer;
    do {
        printf("\nVoulez-vous vraiment quitter ? (O: oui N: non)  ");
        if (buffer != '\n') {
            stdinClear();
        }
        buffer = toupper(getchar());
    } while (buffer != 'O' && buffer != 'N');
    if (buffer == 'O') {
        return true;
    } else {
        return false;
    }
}


int printSaves() {

    clean();
    printf("Gestion des sauvegardes\n\n");
    char buffer[4][50];
    int i = 1;
    long long int time;
    FILE* index = fopen("saves.txt","r");
    if (index != NULL) {
        while (fscanf(index, "%50s\t%50s\t%50s\t%50s\n", buffer[0], buffer[1], buffer[2], buffer[3]) != EOF) {
            time = strtoll(buffer[2], NULL, 10);

            printf("%d: %s\t\t(%sx%s)  \t%lld\n", i, buffer[0], buffer[1], buffer[1], time);
            i++;
        }
    }
    fclose(index);

    if (i == 1) {
        clean();
        printf("Aucune sauvegarde n'a été trouvée ...\n\nAppuiez sur entrée pour retourner au menu ");
        stdinClear();
        return -1;
    } else {
        char input[4];
        int save_number;
        do {
            if (input[0] != '\n' && input[1] != '\n') {
                stdinClear();
            }
            printf("\nEntrez le numéro de la sauvegarde que vous souhaitez importer  ");
            fgets(input, 3, stdin);
            save_number = strtol(input, NULL, 10);

            if ((save_number < 1 || save_number >= i) && input[0] != '\n') {
                printf("Cette sauvegarde n'existe pas !\n");
            }

        } while (save_number < 1 || save_number >= i);
        printf("%d", save_number);  
        return save_number;
    }
}

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

void quitScreen() {
    clean();
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
    stdinClear();
    getchar();
}