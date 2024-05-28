#ifndef UTILS_H
#define UTILS_H

typedef struct context {
    int current;
    int next;
    int prev;
    int size;
} context_t;

typedef enum status {
    OK,
    ERR_INVALID_STATE,
    ERR_INVALID_LOOP,
    ERR_MPI_ERROR
} status_t;

void setup(int * argc, char ** argv[], context_t * context);
void cleanup();

status_t guard_valid_state(context_t * context);
void error_master_cannot_send_message(int comm_result);
void error_puppet_cannot_send_message(context_t * context, int comm_result);
void error_puppet_cannot_receive_message(context_t * context, MPI_Status * mpi_status);
void log_puppet_send_message(context_t * context);
void log_master_send_message(context_t * context);

#endif