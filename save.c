#include <board.h>

void InitializeSavesIndex() {
    FILE* index = fopen("saves.txt","a+");
    fclose(index);
}


bool ExportBoard(square** board, int size, char* savename) {
    
    FILE* index = fopen("saves.txt","r+");
    if (index != NULL) {
        char buffer[25];
        while (fscanf(index, "%25s",buffer) != EOF) {
            if (strcmp(buffer, savename) == 0) {
                printf("A save already has this name !\n");
                fclose(index);
                return false;
            }
        }
        long long int rawtime = time(NULL);
        fprintf(index,"\n%s\t%d\t%lld",savename, size, rawtime);

        char filename[25];
        strcpy(filename, savename);
        strcat(filename,".save");
        FILE* save = fopen(filename, "w");
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


void ImportBoard(square** board, int size, char* savename) {

    char filename[1024];
    strcpy(filename, savename);
    strcat(filename,".save");

    FILE* save = fopen(filename,"r");
    if (save != NULL) {
        for (int y=0; y<size; y++) {
            for (int x=0; x<size; x++) {
                fscanf(save, "%1u%1u ",&(board[x][y].color),&(board[x][y].type));
            }
        fscanf(save, "\n");
        }
    }
}


void RipSave(char* savename) {

    char filename[1024];
    strcpy(filename, savename);
    strcat(filename,".save");
    remove(filename);

    FILE* index = fopen("saves.txt","r");
    char newstring[5000];
    if (index != NULL) {
        char buffer[1024];
        while (fscanf(index, "%s",buffer) != EOF) {
            if (strcmp(buffer,savename) == 0) {
                fscanf(index, "%[^\n]\n", buffer); 
            } else {
                strcat(newstring, buffer);
                fgets(buffer, 1024, index);
                strcat(newstring, buffer);
            }
        }
    }
    fclose(index);
    index = fopen("saves.txt","w");
    if (index != NULL) {
        fprintf(index, "%s", newstring);
    }
    fclose(index);
}