#include <stdio.h>

typedef struct Cell {
    int *row;
    int *col;
    int *bool;
}Cell;

typedef struct Cell Matrix[5];

void generateMatrix(Matrix matrix){

    int x, y;

    for(x=0; x < 5; x++){

        for(y=0; y<5; y++){

            matrix[x].row = x;
            matrix[x].col = y;

            if(x == y){
                matrix[x].bool = 1;
            }
            else{
                matrix[x].bool = 0;
            }
        }
    }

}

int main() {

    Matrix matrix;

    generateMatrix(matrix);

    return 0;
}