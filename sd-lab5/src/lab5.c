#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char** argv) {
    int rank, size;
    int *array_local, *array;
    int soma_local, soma;
    // O tamanho do array foi alterado para 100.
    // Agora, o mpirun pode ser executado com qualquer número de processos que seja divisor de 100 (ex: 2, 4, 5, 10, 20, 25, 50).
    int tamanho = 100;
    int tamanho_local;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    tamanho_local = tamanho / size;
    array_local = (int*)malloc(tamanho_local * sizeof(int));

    if (rank == 0) {
        array = (int*)malloc(tamanho * sizeof(int));
        printf("Array: ");
        for (int i = 0; i < tamanho; i++) {
            array[i] = i + 1;
            if (i < 10) {
                printf("%d ", array[i]);
            } else if (i == 10) {
                printf("... ");
            }
        }
        printf("\n");
    }

    // MPI_Scatter distribui o array principal do processo 0 em partes menores para todos os processos.
    // Cada processo, incluindo o 0, recebe uma porção de 'tamanho_local' do array.
    MPI_Scatter(array, tamanho_local, MPI_INT, array_local, tamanho_local, MPI_INT, 0, MPI_COMM_WORLD);

    soma_local = 0;
    printf("Array recebido pelo rank %2d: ", rank);
    for (int i = 0; i < tamanho_local; i++) {
        printf("%3d ", array_local[i]);
        soma_local += array_local[i];
    }
    printf("-- soma local: %4d\n", soma_local);

    // MPI_Reduce coleta os valores de 'soma_local' de todos os processos e realiza uma operação (MPI_SUM) sobre eles.
    // O resultado final é armazenado na variável 'soma' apenas no processo de rank 0.
    MPI_Reduce(&soma_local, &soma, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        sleep(1);
        printf("\nSoma total do array: %d\n", soma);
        printf("Valor esperado: %d\n", tamanho * (tamanho + 1) / 2);
        free(array);
    }

    free(array_local);
    MPI_Finalize();
}