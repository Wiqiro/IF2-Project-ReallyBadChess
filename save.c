#include <game.h>


 void initializeSavesIndex() {
    FILE* index = fopen("saves.txt","a+");
    fclose(index);
}

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


void ripSave(char* save_name) {

    char file_name[1024];
    strcpy(file_name, save_name);
    strcat(file_name,".save");
    remove(file_name);

    FILE* index = fopen("saves.txt","r");
    char new_string[5000];
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