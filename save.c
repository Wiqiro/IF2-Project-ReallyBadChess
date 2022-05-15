#include <save.h>

void InitializeSavesIndex() {
    FILE* index = fopen("saves.txt","a");
    fclose(index);
}

saveinfo* SaveParser(char* rawstring) {
    int size = 0;
    for (int i=0; i<sizeof(rawstring);i++) {
        if (rawstring[i] == ';') {
            size++;
        }
    }
    saveinfo* savelist = (saveinfo*) malloc(sizeof(savelist) * size);
    if (savelist != NULL) {

    }
    return savelist;
}

void ExportBoard(square** board, int size, char* savename) {
    InitializeSavesIndex();

    char filename[1024];
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
    }
    fclose(save);

    FILE* index = fopen("saves.txt","r+");
    fclose(index);
}

void ImportBoard(square** board, int size, char* filename) {

}

