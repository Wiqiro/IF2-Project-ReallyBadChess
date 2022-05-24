#include <display.h>



#ifdef _WIN32
    bool OS = 0;
#else
    bool OS = 1;  //assuming that the non-windows systems are linux-based
#endif

void Clean() {

    if(OS == 0) {
        system("cls");
    } else {
        system("clear");
    }
}

void StdinClear() {
    char buffer;
    while ((buffer = getchar()) != '\n');
}

char MenuInput() {

    char buffer;
    do {
        StdinClear();
        printf("\nChoisissez une option ! (N: nouvelle partie  I: importer une sauvegarde  Q: quitter)  ");
        buffer = toupper(getchar());
    } while (buffer != 'N' && buffer != 'I' && buffer != 'Q');
    return buffer;
}

bool GamemodeInput() {
    char gamemode;
    StdinClear();
    do {
    printf("\nQuel mode de jeu choisissez-vous ? (B: Really bad chest, C: classic)\n");
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
    char input[100];
    int size=0;
    do {

        if (OS == 0) {
            printf("\nChoisissez %c pr%csent la taille de l'%cchiquer (de 6x6 %c 12x12)\n",133,130,130,133);
        } else {
            printf("\nChoisissez à présent la taille de l'échiquer (de 6x6 à 12x12)\n");
        }


        fflush(stdin);
        scanf("%s",input);
        size = strtol(input, NULL, 10);
        
    } while (size > 12 || size < 6);
    return size;
}

//to be replaced by adress passing
void MoveInput(int* coordsarray, int size) {
    char input[1024];
    StdinClear();
    scanf("%s",input);

    if (toupper(input[0])-'A' >= 0 && toupper(input[0])-'A' < size) {
        coordsarray[0] = toupper(input[0]) - 'A';
    } else {
        coordsarray[0] = -1;
    }

    if (input[2] == '\0') {
        coordsarray[1] = size - input[1] + '0';
    } else if (input[3] == '\0') {
        coordsarray[1] = size - input[2] + '0' - 10;
    } else {
        coordsarray[1] = -1;
    }

    if (coordsarray[1] < 0 || coordsarray[1] >= size) {
        printf("%d  %d\n", coordsarray[0], coordsarray[1]);
        coordsarray[1] = -1;
    }
}

char ActionInput() {

    char buffer;
    do {
        StdinClear();
        printf("Que voulez-vous faire ? (J: jouer  S: sauvegarder  X: abandonner)  ");
        buffer = toupper(getchar());


    } while (buffer != 'J' && buffer != 'S' && buffer != 'X');
    return buffer;
}

void SaveNameInput(char* string) {

    char buffer[20];

    StdinClear();
    printf("Sous quel nom voulez-vous sauvegarder votre partie ?  ");
    fgets(buffer, 20, stdin);
    strncpy(string, buffer, strlen(buffer)-1);
}

bool QuitConfirmation() {
    char buffer;
    do {
        printf("Voulez-vous vraiment quitter ? (O: oui N: non) \n");
        StdinClear();
        buffer = toupper(getchar());
    } while (buffer != 'O' && buffer != 'N');
    if (buffer == 'O') {
        return true;
    } else {
        return false;
    }
}




//rip small consoles
void EndDialogue() {
    Clean();
                                                                                                                                                                                                                                                                                                                                    
    printf("  ****           *      *****    **            **             ***** *     **         *****                    *******                                    ***** **          * ***         ***** ***                               ***** **         ***** *               **              ***** *    **           *****  *      ***** *     **          * ***           \n");
    printf(" *  *************    ******  *  **** *      *****          ******  **    **** *   ******                    *       ***                               ******  **** *     *  ****      ******  * **                            ******  ****     ******  *             *****           ******  *  *****        ******  *     ******  **    **** *     *  ****  *        \n");
    printf("*     *********     **   *  *   *****      *  ***         **   *  * **    ****   **   *  *    **           *         **                              **   *  *  ***     *  *  ***    **   *  *  **                           **   *  *  ***   **   *  *             *  ***          **   *  *     *****     **   *  *     **   *  * **    ****     *  *  ****         \n");
    printf("*     *  *         *    *  *    * *           ***        *    *  *  **    * *   *    *  *   **** *         **        *                              *    *  *    *     *  **   ***  *    *  *   **                          *    *  *    *** *    *  *                 ***         *    *  **     * **     *    *  *     *    *  *  **    * *     *  **   **          \n");
    printf(" **  *  **             *  *     *            *  **           *  *    **   *         *  *     ****           ***                                         *  *          *  ***    ***     *  *    *                               *  *      **     *  *                 *  **            *  ***     *            *  *          *  *    **   *      *  ***               \n");
    printf("    *  ***            ** **     *            *  **          ** **    **   *        ** **    * **           ** ***                                      ** **         **   **     **    ** **   *                               ** **      **    ** **                 *  **           **   **     *           ** **         ** **    **   *     **   **               \n");
    printf("   **   **            ** **     *           *    **         ** **     **  *        ** **   *                *** ***                                    ** **         **   **     **    ** **  *                                ** **      **    ** **                *    **          **   **     *           ** **         ** **     **  *     **   **   ***         \n");
    printf("   **   **            ** ********           *    **         ** **     **  *        ** *****                   *** ***                                  ** ******     **   **     **    ** ****                               **** **      *     ** **                *    **          **   **     *         **** **         ** **     **  *     **   **  ****  *      \n");
    printf("   **   **            ** **     *          *      **        ** **      ** *        ** ** ***                    *** ***                                ** *****      **   **     **    ** **  ***                           * *** **     *      ** **               *      **         **   **     *        * *** **         ** **      ** *     **   ** *  ****       \n");
    printf("   **   **            ** **     **         *********        ** **      ** *        ** **   ***                    ** ***                               ** **         **   **     **    ** **    **                             ** *******       ** **               *********         **   **     *           ** **         ** **      ** *     **   ***    **        \n");
    printf("    **  **            *  **     **        *        **       *  **       ***        *  **    ***                    ** **                               *  **          **  **     **    *  **    **                             ** ******        *  **              *        **         **  **     *      **   ** **         *  **       ***      **  **     *         \n");
    printf("     ** *      *         *       **       *        **          *        ***           *       ***                   * *                                   *            ** *      *        *     **                             ** **               *               *        **          ** *      *     ***   *  *             *        ***       ** *      *         \n");
    printf("      ***     *      ****        **      *****      **     ****          **       ****         ***        ***        *                                *****             ***     *     ****      ***                            ** **           ****           *   *****      **          ***      *      ***    *          ****          **        ***     *          \n");
    printf("       *******      *  *****      **    *   ****    ** *  *  *****               *  *****        ***  *  *  *********                                *  *****            *******     *  ****    **                             ** **          *  *************   *   ****    ** *         *********       ******          *  *****                  *******           \n");
    printf("         ***       *     **            *     **      **  *     **               *    ***           ***  *     *****                                 *    ***               ***      *    **     *                         **   ** **         *     *********    *     **      **            **** ***        ***          *     **                     ***             \n");
    printf("                   *                   *                 *                      *                       *                                           *                               *                                    ***   *  *          *                  *                                 ***                    *                                            \n");
    printf("                    **                  **                **                     **                      **                                          **                              **                                   ***    *            **                 **                   ********     ***                    **                                          \n");
    printf("                                                                                                                                                                                                                           ******                                                   *************  **                                                                 \n");
    printf("                                                                                                                                                                                                                             ***                                                   *           ****                                                                   \n");
    
    printf("\nPressez entrer pour quitter");
    StdinClear();
    getchar();

}

