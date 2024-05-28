#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include "utils.h"

status_t guard_valid_state(context_t * context) {
    if (context->size <= 1) {
        printf("FATAL: A closed ring system shall have more then one node to run. %d processes found.\n", context->size);
        return ERR_INVALID_STATE;
    }

    return OK;
}

void error_master_cannot_send_message(int comm_result) {
    printf("ERROR: Master couldn`t sent a message to its puppets. MPI_Error: %d\n", comm_result);
}

void error_puppet_cannot_send_message(context_t * context, int comm_result) {
    printf("ERROR: Puppet %d couldn`t sent a message to %d. MPI_Error: %d\n", context->current, context->next, comm_result);
}

void error_puppet_cannot_receive_message(context_t * context, MPI_Status * mpi_status) {
    printf("ERROR: Puppet %d couldn`t receive message from %d. MPI_Error: %d, Tag: %d.\n",
        context->current,
        mpi_status->MPI_SOURCE,
        mpi_status->MPI_TAG,
        mpi_status->MPI_ERROR);
}

void log_puppet_send_message(context_t * context) {
    printf("INFO: Puppet %d passed the hot potato to %d.\n", context->current, context->next);
}

void log_master_send_message(context_t * context) {
    printf("INFO: Master passed the hot potato to %d.\n", context->next);
}

void setup(int * argc, char ** argv[], context_t * context) {
    MPI_Init(argc, argv);
    MPI_Comm_size(MPI_COMM_WORLD, &context->size);
    MPI_Comm_rank(MPI_COMM_WORLD, &context->current);

    context->next = context->current + 1;
    context->prev = context->current - 1;

    if (context->next == context->size) {
        context->next = 0;
    }

    if (context->prev == -1) {
        context->prev = context->size - 1;
    }
}

void cleanup() {
    MPI_Finalize();
}