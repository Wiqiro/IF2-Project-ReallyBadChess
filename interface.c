#include <interface.h>



#ifdef _WIN32
    #define OS 0
    #include <windows.h>
#else
    #define OS 1  //assuming that the non-windows systems are linux-based
#endif

void Clean() {
    if(OS == 0) {
        system("cls");
    } else {
        system("clear");
    }
}

void InitializeOutputOptions() {
    #ifdef _WIN32
        SetConsoleOutputCP(65001);
    #endif
}

void StdinClear() {
    char buffer;
    while ((buffer = getchar()) != '\n');
}

char MenuInput() {

    char buffer;
    do {
        if (buffer != '\n') {
            StdinClear();
        }
        printf("\nChoisissez une option ! (N: nouvelle partie  I: importer une sauvegarde  O: options  Q: quitter)  ");
        buffer = toupper(getchar());
    } while (buffer != 'N' && buffer != 'I' && buffer != 'Q' && buffer != 'O');
    return buffer;
}

bool GamemodeInput() {
    char gamemode;
    do {
        if (gamemode != '\n') {
            StdinClear();
        }
        printf("\nQuel mode de jeu choisissez-vous ? (B: Really bad chest, C: classic)  ");
        scanf("%c",&gamemode);
        gamemode = toupper(gamemode);

    } while (gamemode != 'B' && gamemode != 'C');

    if (gamemode == 'B') {
        return true;
    } else {
        return false;
    }
}


int ChessBoardSizeInput() {
    char input[2];
    int size=0;
    do {
        printf("\nChoisissez à présent la taille de l'échiquer (de 6x6 à 12x12)  ");

        StdinClear();
        scanf("%2[^\n]",input);
        size = strtol(input, NULL, 10);
        
    } while (size > 12 || size < 6);
    return size;
}

void MoveInput(square** board, int size, bool turn, coords* startcoords, coords* targcoords, coords* kingpos) {

    bool okmove = false;
    char input[3];
    do {
        do {
            printf("\nEntrez les coordonnées de la pièce que vous souhaitez bouger: ");
            StdinClear();
            scanf("%3[^\n]", input);

            startcoords->x = toupper(input[0]) - 'A';
            if (input[2] == '\0') {
                startcoords->y = size - input[1] + '0';
            } else {
                startcoords->y = size - input[2] + '0' - 10;
            }
            if (startcoords->x < 0 || startcoords->x >= size || startcoords->y < 0 || startcoords->y >= size) {
                printf("Cette pièce ne fait pas partie de l'échiquier !\n");                            
            } else if (board[startcoords->x][startcoords->y].type == empty) {
                printf("Cette case est vide\n");
            } else if (board[startcoords->x][startcoords->y].color != turn) {
                printf("Ce n'est pas votre tour\n");
            } else {
                okmove = true;
            }

        } while (!okmove);

        okmove = true;
        StdinClear();
        printf("Entrez les coordonnées de la case où vous souhaitez bouger la pièce: ");
        scanf("%3[^\n]", input);
        
        targcoords->x = toupper(input[0]) - 'A';
        if (input[2] == '\0') {
            targcoords->y = size - input[1] + '0';
        } else {
            targcoords->y = size - input[2] + '0' - 10;
        }
        //printf("%d %d   %d %d\n", kingpos->x, kingpos->y, targcoords->x, targcoords->y);
        
        if (MoveTest(board, size, *startcoords, *targcoords) == false) {
            printf("Ce mouvement est interdit !\n");
            okmove = false;
        } else if (board[targcoords->x][targcoords->y].color == turn && board[targcoords->x][targcoords->y].type != empty) {
            printf("Vous ne pouvez pas prendre vos propres pièces !\n");
            okmove = false;
        } else if (board[startcoords->x][startcoords->y].type == king && CheckTest(board, size, *targcoords, board[kingpos->x][kingpos->y].color) == true) {
            printf("Vous ne pouvez pas mettre votre roi en échec !\n");
            okmove = false;
        } else if (board[startcoords->x][startcoords->y].type != king && CheckTestAfterMove(board, size, *startcoords, *targcoords, *kingpos, board[kingpos->x][kingpos->y].color)) {
            printf("Vous ne pouvez pas mettre votre roi en échec\n");
            okmove = false;
        }
    } while (!okmove);
}

char ActionInput() {

    char buffer;
    do {
        if (buffer != '\n') {
            StdinClear();
        }
        printf("\nQue voulez-vous faire ? (J: jouer  S: sauvegarder  O: options  X: abandonner)  ");
        buffer = toupper(getchar());

    } while (buffer != 'J' && buffer != 'S' && buffer != 'X' && buffer != 'O');
    return buffer;
}


void PrintPiece(square piece, bool fancyprint) {

    if (fancyprint) {
        if (piece.color == black) {
            switch (piece.type) {
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
            switch (piece.type) {
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
        if (piece.type != empty) {
            switch (piece.type) {
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
            if (piece.color == white) {
                printf("B");
            } else {
                printf("N");
            }
        } else {
            printf("  ");
        }
    }
}

void BoardPrint(square** board, int size, bool fancyprint) {

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
            PrintPiece(board[x][y], fancyprint);
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
        PrintPiece(board[x][size-1], fancyprint);
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

void SaveNameInput(char* string) {

    char buffer[21];
    int buffersize = 0;
    bool oklenght = false;

    do {
        StdinClear();
        printf("\nSous quel nom voulez-vous sauvegarder votre partie ?  ");
        scanf("%21[^\n]", buffer);
        buffersize = strlen(buffer);
        if (buffersize > 20) {
            printf("Entrez un nom de moins de 20 charactères \n");
        } else if (buffersize < 2) {
            printf("Entrez un nom plus long\n");
        } else {

            int i = 0;
            while (i < buffersize-1 && buffer[i] > ' ' && buffer[i] != '/' && buffer[i] != '\\' && buffer[i] != '*' && buffer[i] != ':' && buffer[i] != '|' && buffer[i] != '"' && buffer[i] != '<' && buffer[i] != '>' && buffer[i] != '?') {
                i++;
            }
            if (i == buffersize-1) {
                oklenght = true;
            } else {
                printf("Votre nom contient un caractère interdit (caractère %d)\n", i+1);
            } 
        }

    } while (oklenght == false);
    strncpy(string, buffer, 20);
}

bool FancyModeInput() {

    char buffer;
    do {
        if (buffer != '\n') {
            StdinClear();
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

bool QuitConfirmation() {
    char buffer;
    do {
        printf("\nVoulez-vous vraiment quitter ? (O: oui N: non)  ");
        if (buffer != '\n') {
            StdinClear();
        }
        buffer = toupper(getchar());
    } while (buffer != 'O' && buffer != 'N');
    if (buffer == 'O') {
        return true;
    } else {
        return false;
    }
}


int PrintSaves() {

    Clean();
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
        Clean();
        printf("Aucune sauvegarde n'a été trouvée ...\n\nAppuiez sur entrée pour retourner au menu ");
        StdinClear();
        return -1;
    } else {
        char input[4];
        int savenumber;
        do {
            if (input[0] != '\n' && input[1] != '\n') {
                StdinClear();
            }
            printf("\nEntrez le numéro de la sauvegarde que vous souhaitez importer  ");
            fgets(input, 3, stdin);
            savenumber = strtol(input, NULL, 10);

            if ((savenumber < 1 || savenumber >= i) && input[0] != '\n') {
                printf("Cette sauvegarde n'existe pas !\n");
            }

        } while (savenumber < 1 || savenumber >= i);
        printf("%d", savenumber);  
        return savenumber;
    }
}

void WelcomeScreen() {
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

void QuitScreen() {
    Clean();
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
    StdinClear();
    getchar();
}