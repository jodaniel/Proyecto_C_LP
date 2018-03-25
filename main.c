#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Cell {
    int row;
    int col;
    int bool;
}Cell;


//Estructura con un vector dinámico
typedef struct {
    char *matrixSize;
    int tokensGameLocation;

}matrixStruct;

matrixStruct *matStr;

void vaciar(char temp[]);
void copiar(char temp[], int i);

//vaciar arreglo temporal
void vaciar(char temp[]) {

    for (int i = 0; i < 300 ; i++)
    {
        temp[i] = '\0';
    }

}

void copiar(char temp[], int i){

    int N = strlen(temp) + 1;
    matStr[i].matrixSize = (char*)malloc(N* sizeof(char));
    if (matStr[i].matrixSize == NULL)
    {
        printf("Error al reservar la memoria.\n");
        exit(1);
    }
    strcpy(matStr[i].matrixSize,temp);
}

// funcion para leer el archivo con las entradas del programa y almacenarlo en arreglos temporales
void manageFile(char direction[]) {

    char aux;
    char temp[300];
    int cont = 0;

    FILE *f;
    f = fopen(direction,"r");  //leer el archivo

    if (f == NULL){
        printf("Problema al abrir el archivo con los datos de entrada.\n");
        exit(1);
    }


    while (!feof(f))
    {
        //leer toda la línea y almacenarlo en el string temporal
        fgets(temp,300,f);
        cont++;
    }
    //pasar el cursor al inicio del archivo por cada iteración
    rewind(f);

    //asignar el espacio de memoria al archivo
    matStr = (matrixStruct*)malloc(cont* sizeof(matrixStruct));
    if (matStr == NULL)
    {
        printf("Error al reservar la memoria.\n");
        exit(1);
    }
    //bucle para recorrer los valores del archivo según su ubicación
    for (int i = 0; !feof(f); i++)
    {
        vaciar(temp);
        aux = '0';

        for (int j = 0; aux != '\n'; j++)
        {
            aux = fgetc(f);
            if (aux == '0')
            {
                exit(1);
            }
            if (aux != '\n')
            {
                temp[j] = aux;

            }

        }

        copiar(temp,i);
        char* ptr;
        fgets(temp,300,f);
        matStr[i].tokensGameLocation = atoi(temp);
        int copiaNumeros = matStr[i].tokensGameLocation;

        //printf(" MatrixSize: %sX%s TokensGameLocation: %i\n",matStr[i].matrixSize,matStr[i].matrixSize,matStr[i].tokensGameLocation);

        int valoresInversos[strlen(temp)-2];
        int valoresCorrectos[strlen(temp)-2];

        int m,size;
        m=0;
        size=0;

        do {
            valoresInversos[m] =  copiaNumeros % 10;
            copiaNumeros /= 10;
            m++;
        } while (copiaNumeros != 0);

        int e,f;

        for(e=0, f=(strlen(temp)-2)-1; f>=0; f--, e++){
            valoresCorrectos[e] = valoresInversos[f];
            size++;
        }

        int y,z;
        Cell matriz[(int)strtol(matStr[i].matrixSize, &ptr, 10)+1][15];

        for(y = 1; y<(int)strtol(matStr[i].matrixSize, &ptr, 10)+1; y++ ) {

            for (z = 1; z < (int)strtol(matStr[i].matrixSize, &ptr, 10)+1; z++) {
                matriz[y][z].bool = 0;
                matriz[y][z].row = y;
                matriz[y][z].col = z;
            }
        }

        int w =0;

        while(w < size){
            matriz[valoresCorrectos[w]][valoresCorrectos[w+1]].bool = 1;
            //printf("x:%i y:%i bool:%i\n", valoresCorrectos[w], valoresCorrectos[w+1], matriz[valoresCorrectos[w]][valoresCorrectos[w+1]].bool);
            w +=2;
        }

        int p,q;

        for(q = 1; q<(int)strtol(matStr[i].matrixSize, &ptr, 10)+1; q++){
            for(p=1; p<(int)strtol(matStr[i].matrixSize, &ptr, 10)+1; p++)
                printf("Valor[%i][%i] es %i\n", q, p, matriz[q][p].bool);
        }

        //retorno en la consola


        //generateMatrix(matriz, (int)strtol(matStr[i].matrixSize, &ptr, 10), valoresCorrectos, size);
        //showSpots(matriz, (int)strtol(matStr[i].matrixSize, &ptr, 10));

    }


}



int main() {

    manageFile("PruebasGrupo5.txt");
    system("pause");
    return EXIT_SUCCESS;
}