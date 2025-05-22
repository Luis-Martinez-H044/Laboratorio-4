#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int** guardar_matriz(int tamaño) {
    int **matriz = (int**)malloc(tamaño * sizeof(int*));
    if (matriz == NULL) {
        printf("Error al reservar memoria para las filas\n");
        exit(1);
    }

    for (int i = 0; i < tamaño; i++) {
        *(matriz + i) = (int*)malloc(tamaño * sizeof(int));
        if (*(matriz + i) == NULL) {
            printf("Error al reservar memoria para las columnas\n");
            for (int j = 0; j < i; j++) {
                free(*(matriz + j));
            }
            free(matriz);
            exit(1);
        }
    }
    return matriz;
}

void fullear_matriz(int **matriz, int tamaño) {
    srand(time(NULL));
    for (int i = 0; i < tamaño; i++) {
        for (int j = 0; j < tamaño; j++) {
            *(*(matriz + i) + j) = rand() % 2;
        }
    }
}

void imprimir_matriz(int **matriz, int tamaño) {
    printf("Matriz %dx%d:\n", tamaño, tamaño);
    for (int i = 0; i < tamaño; i++) {
        for (int j = 0; j < tamaño; j++) {
            printf("%d ", *(*(matriz + i) + j));
        }
        printf("\n");
    }
}

void encontrar_diagonalarga(int **matriz, int tamaño, int *resultado) {
    int longitudm = 0;
    int longitudn = 0;
    for (int d = 0; d < 2 * tamaño - 1; d++) {
        longitudn = 0;
        for (int i = 0; i < tamaño; i++) {
            int j = d - i;
            if (j >= 0 && j < tamaño) {
                if (*(*(matriz + i) + j) == 1) {
                    longitudn++;
                    if (longitudn > longitudm) {
                        longitudm = longitudn;
                    }
                } else {
                    longitudn = 0;
                }
            }
        }
    }
    for (int d = 0; d < 2 * tamaño - 1; d++) {
        longitudn = 0;
        for (int i = 0; i < tamaño; i++) {
            int j = (tamaño - 1) - (d - i);
            if (j >= 0 && j < tamaño) {
                if (*(*(matriz + i) + j) == 1) {
                    longitudn++;
                    if (longitudn > longitudm) {
                        longitudm = longitudn;
                    }
                } else {
                    longitudn = 0;
                }
            }
        }
    }
    *resultado = longitudm;
}
void liberar_matriz(int **matriz, int tamaño) {
    for (int i = 0; i < tamaño; i++) {
        free(*(matriz + i));
    }
    free(matriz);
}
void copiar_matrix(int **origen, int **destino, int tamaño_origen, int tamaño_destino) {
    int tamaño_min = tamaño_origen < tamaño_destino ? tamaño_origen : tamaño_destino;
    for (int i = 0; i < tamaño_min; i++) {
        for (int j = 0; j < tamaño_min; j++) {
            *(*(destino + i) + j) = *(*(origen + i) + j);
        }
    }
    if (tamaño_destino > tamaño_origen) {
        for (int i = 0; i < tamaño_destino; i++) {
            for (int j = tamaño_origen; j < tamaño_destino; j++) {
                if (i < tamaño_origen) {
                    *(*(destino + i) + j) = 0;
                } else {
                    *(*(destino + i) + j) = 0;
                }
            }
        }
    }
}

int main() {
    int tamaño,diagonal_larga;
    int **matriz = NULL;
    char opcion;
    printf("Ingrese el tamaño de la matriz cuadrada: ");
    scanf("%d", &tamaño);
    if (tamaño <= 0) {
        printf("El tamaño debe ser un número positivo.\n");
        return 1;
    }

    matriz = guardar_matriz(tamaño);
    fullear_matriz(matriz, tamaño);
    imprimir_matriz(matriz, tamaño);
    encontrar_diagonalarga(matriz, tamaño, &diagonal_larga);
    printf("La secuencia de 1s más grande es: %d\n",diagonal_larga);

    do {
        printf("\n¿Desea cambiar el tamaño de la matriz? (s/n): ");
        scanf(" %c", &opcion);
        if (opcion == 's' || opcion == 'S') {
            int ntamaño;
            printf(" Por favor, ngrese el nuevo tamaño de la matriz: ");
            scanf("%d", &ntamaño);
            if (ntamaño <= 0) {
                printf("El tamaño debe ser un número positivo.\n");
                continue;
            }
            int **nmatriz = guardar_matriz(ntamaño);
            copiar_matrix(matriz, nmatriz, tamaño, ntamaño);
            if (ntamaño > tamaño) {
                for (int i = 0; i < ntamaño; i++) {
                    for (int j = 0; j < ntamaño; j++) {
                        if (i >= tamaño || j >= tamaño) {
                            *(*(nmatriz + i) + j) = rand() % 2;
                        }
                    }
                }
            }
        
            liberar_matriz(matriz, tamaño);
            matriz = nmatriz;
            tamaño = ntamaño;
            imprimir_matriz(matriz, tamaño);
            encontrar_diagonalarga(matriz, tamaño, &diagonal_larga);
            printf("La secuencia de 1s más grande es: %d\n",diagonal_larga);
        }
    } while (opcion == 's' || opcion == 'S');
  
    liberar_matriz(matriz, tamaño);
    
    return 0;
}