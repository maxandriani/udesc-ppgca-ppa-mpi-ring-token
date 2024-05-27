#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define INVALID_STATE 1;

int main(int argc, char* argv[]) {
    int proc_id,
        proc_size,
        prev        = -1,
        next        = -1,
        tag         = 0;

    MPI_Status status;
    status.MPI_SOURCE = MPI_ANY_SOURCE;

    // Setup
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &proc_size);
    MPI_Comm_rank(MPI_COMM_WORLD, &proc_id);

    // Guards
    if (proc_size <= 1) {
        printf("FATAL: Um sistema de anel precisa de mais de 1 nó para executar. %d processos encontrados.\n", proc_size);
        MPI_Finalize();
        return INVALID_STATE;
    }

    next = proc_id + 1;

    if (proc_id == 0) {
        // I`m the master of puppets
        MPI_Send(&proc_id, 1, MPI_INT, next, tag, MPI_COMM_WORLD);
        printf("INFO: Master call puppet %d.\n", next);
        // await for feedback
        MPI_Recv(&prev, 1, MPI_INT, (proc_size - 1), tag, MPI_COMM_WORLD, &status);

        // if (status.MPI_SOURCE != MPI_ANY_SOURCE) {
        //     printf("TRACE: MPI Comm recv status from %d/%d:%d\n", status.MPI_SOURCE, status.MPI_TAG, status.MPI_ERROR);
        //     MPI_Finalize();
        //     return status.MPI_ERROR;
        // }

        printf("INFO: Master receved from %d.\n", prev);

        if (prev != (proc_size - 1)) {
            printf("Deu ruim no ring... alguém se perdeu feio. prev: %d. next: %d. size: %d", prev, next, proc_size);
            MPI_Finalize();
            return INVALID_STATE;
        }
    } else {
        // I`m a puppet
        MPI_Recv(&prev, 1, MPI_INT, (proc_id - 1), tag, MPI_COMM_WORLD, &status);

        // if (status.MPI_SOURCE != MPI_ANY_SOURCE) {
        //     printf("TRACE: MPI Comm recv status from %d/%d:%d\n", status.MPI_SOURCE, status.MPI_TAG, status.MPI_ERROR);
        //     MPI_Finalize();
        //     return status.MPI_ERROR;
        // }

        if (next == proc_size) {
            next = 0;
        }

        MPI_Send(&proc_id, 1, MPI_INT, next, tag, MPI_COMM_WORLD);
        printf("INFO: Puppet jump from %d to %d.\n", proc_id, next);
    }

    MPI_Finalize();

    return 0;
}