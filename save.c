#include <save.h>



void ExportBoard(square** board, int size) {


    FILE* save = fopen("save", "w");
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

void ImportBoard(square** board, int size, char* filename) {

}