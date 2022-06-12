#include <game.h>

/**
 * @brief Initialize the "saves.txt" index by creating it if inexistant
 * 
 */
 void initializeSavesIndex() {
    FILE* index = fopen("saves.txt","a+");
    fclose(index);
}

/**
 * @brief Export the specified board in a ".save" file and add it to the "saves.txt" index
 * 
 * @param board Board that has to be exported
 * @param size Size of the board
 * @param save_name Name of the save
 * @param turn 
 * @return true if the board was correctly exported
 * @return false if there was an error was exporting the board
 */
bool exportBoard(Square** board, int size, char* save_name, Color turn) {
    
    FILE* index = fopen("saves.txt","r+");
    if (index != NULL) {
        char buffer[25];
        while (fscanf(index, "%25s",buffer) != EOF) {
            if (strcmp(buffer, save_name) == 0) {
                fclose(index);
                return false;
            }
        }
        long long int raw_time = time(NULL);
        fprintf(index,"\n%s\t%d\t%lld\t%d",save_name, size, raw_time, turn);

        char file_name[25];
        strcpy(file_name, save_name);
        strcat(file_name,".save");
        FILE* save = fopen(file_name, "w");
        if (save != NULL) {
            for (int y=0; y<size; y++) {
                for (int x=0; x<size; x++) {
                    fprintf(save,"%d%d ",board[x][y].color,board[x][y].type);
                }
                fprintf(save,"\n");
            } 
        } else {
            return false;
        }
        fclose(save);
    } else {
        return false;
    }
    fclose(index);
    return true;
}

/**
 * @brief Get the informations relative to a save in the "save.txt" index
 * 
 * @param line_number Line that has to be parsed
 * @return SaveInfo the informations relatives to the save
 */
SaveInfo getSaveInfo(int line_number) {
    SaveInfo save;

    FILE* index = fopen("saves.txt","r");
    char buffer[50];
    if (index != NULL) {
        for (int i = 1; i < line_number; i++) {
            fscanf(index, "\n%50[^\n]", buffer);
        }
        fscanf(index, "%s\t%d\t%lld\t%d", save.name, &save.size, &save.time, &save.turn);
    }
    fclose(index);
    return save;
}

/**
 * @brief Import the specified save in a board (the board has to be created before with the right size)
 * 
 * @param board The board where the save will be imported
 * @param size The size of the board
 * @param save_name The name of the save that is going to be imported
 */
void importBoard(Square** board, int size, char* save_name) {

    char file_name[1024];
    strcpy(file_name, save_name);
    strcat(file_name,".save");

    FILE* save = fopen(file_name,"r");
    if (save != NULL) {
        for (int y=0; y<size; y++) {
            for (int x=0; x<size; x++) {
                fscanf(save, "%1u%1u ",&(board[x][y].color),&(board[x][y].type));
            }
        fscanf(save, "\n");
        }
    }
}

/**
 * @brief Delete the specified save ".save" file and delete its corresponding line in the "saves.txt" index (DOES NOT WORK ON WINDOWS)
 * 
 * @param save_name The name of the save that has to be deleted
 */
void ripSave(char* save_name) {

    char file_name[1024];
    strcpy(file_name, save_name);
    strcat(file_name,".save");
    remove(file_name);

    FILE* index = fopen("saves.txt","r");
    char new_string[5000] = "";
    if (index != NULL) {
        char buffer[1024];
        while (fscanf(index, "%s",buffer) != EOF) {
            if (strcmp(buffer,save_name) == 0) {
                fscanf(index, "%[^\n]\n", buffer); 
            } else {
                strcat(new_string, buffer);
                fgets(buffer, 1024, index);
                strcat(new_string, buffer);
            }
        }
    }

    fclose(index);
    index = fopen("saves.txt","w");
    if (index != NULL) {
        fprintf(index, "%s", new_string);
    }
    fclose(index);
}