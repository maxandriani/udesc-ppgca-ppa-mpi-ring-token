#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include "utils.h"

int main(int argc, char* argv[]) {
    context_t context = { .current = 0, .next = 1, .prev = -1, .size = 0 };
    MPI_Status mpi_status;
    int comm_result;
    int msg_buffer;

    setup(&argc, &argv, &context);

    // Guards
    if (guard_valid_state(&context) != OK) {
        cleanup();
        return ERR_INVALID_STATE;
    }
    
    if (context.current == 0) {
        printf("I`m the master of puppets.\n");
        comm_result = MPI_Send(&context.next, 1, MPI_INT, context.next, 0, MPI_COMM_WORLD);
        if (comm_result != MPI_SUCCESS) {
            error_master_cannot_send_message(comm_result);
            cleanup();
            return ERR_MPI_ERROR;
        }
        log_master_send_message(&context);
    }

    comm_result = MPI_Recv(&msg_buffer, 1, MPI_INT, context.prev, 0, MPI_COMM_WORLD, &mpi_status);
    if (comm_result != MPI_SUCCESS) {
        error_puppet_cannot_receive_message(&context, &mpi_status);
        cleanup();
        return ERR_MPI_ERROR;
    }

    if (msg_buffer == context.current && msg_buffer > 0) {
        log_puppet_send_message(&context);
        comm_result = MPI_Send(&context.next, 1, MPI_INT, context.next, 0, MPI_COMM_WORLD);
        if (comm_result != MPI_SUCCESS) {
            error_puppet_cannot_send_message(&context, comm_result);
            cleanup();
            return ERR_MPI_ERROR;
        }
    }

    cleanup();
    return 0;
}