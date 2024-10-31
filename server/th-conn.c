#include <stdio.h>

#include "server.h"
#include "th-conn.h"


void *th_conn_handler(void *arg) {
    int         thix = ((th_conn_arg *)arg)->ix;
    int         listenfd = ((th_conn_arg *)arg)->listenfd;
    thflags_t   *pflags = ((th_conn_arg *)arg)->pflags;

    while((*pflags & F_LISTENFD_CLOSED) == 0) {

    }

    return NULL;
}
