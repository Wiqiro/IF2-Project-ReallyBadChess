#include <save.h>

void InitializeSavesIndex() {
    FILE* index = fopen("saves.txt","a+");
    fclose(index);
}


//useless
saveinfo* SaveParser(char* rawstring) {
    int size = 0;
    for (int i=0; i<strlen(rawstring);i++) {
        if (rawstring[i] == '\n') {
            size++;
        }
    }
    rawstring = strchr(rawstring,'\n');
    rawstring++;

    saveinfo* savelist = (saveinfo*) malloc(sizeof(saveinfo) * size);

    if (savelist != NULL) {
        for (int i=0; i<size; i++) {
        sscanf(rawstring,"%[^\t]\t%d\t%ld",savelist[i].name,&(savelist[i]).size,&(savelist[i]).time);
        rawstring = strchr(rawstring,'\n');
        rawstring++;
        }   
    }
    return savelist;
}
 


void ExportBoard(square** board, int size, char* savename) {
    

    


    FILE* index = fopen("saves.txt","r+");
    if (index != NULL) {
        char buffer[1024];
        while (fscanf(index, "%s",buffer) != EOF) {
            if (strcmp(buffer, savename) == 0) {
                printf("A save already has this name !\n");
                fclose(index);
                return;
            }
        }
        fprintf(index,"\n%s\t%d\t%ld",savename, size, time(NULL));

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

    }
    fclose(index);
}

void ImportBoard(square** board, int size, char* filename) {

}