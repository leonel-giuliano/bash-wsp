#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <string.h>

#include "server.h"
#include "key.h"
#include "errnum.h"


int main(void) {
    int                 e = 0;
    thflags_t           thflags = 0;
    int                 listenfd, connfd;
    struct sockaddr_in  servaddr;
    th_key_arg_t        th_key_arg;
    pthread_t           th_key;

    errnum_program_name = "bash-wsp";


    puts("Creating socket...");
    if((listenfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
        return errnum(ERR_NEW_SCK);

    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(SERV_PORT);

    puts("Binding socket...");
    if(bind(listenfd, (struct sockaddr *)&servaddr, sizeof(servaddr))) {
        e = errnum(ERR_BIND);
        goto close_listenfd;
    }

    puts("Opening socket to listen...");
    if(listen(listenfd, SERV_BACKLOG)) {
        e = errnum(ERR_LISTEN);
        goto close_listenfd;
    }


    puts("Initializing threads...");
    th_key_arg.listenfd = listenfd;
    th_key_arg.pflags = &thflags;
    e = pthread_create(&th_key, NULL, th_key_handler, (void *)&th_key_arg);

    if(e) {
        errnum(ERR_NEW_TH);
        goto close_listenfd;
    }


    puts("SETUP SUCCEEDED: accepting incoming connections");
    while((thflags & F_CH_EXIT) == 0) {
        if((connfd = accept(listenfd, NULL, NULL)) == -1) {
            e = errnum(ERR_ACCEPT_CONN);
            goto close_listenfd;
        }
    }


    close_listenfd:
        if((thflags & F_LISTENFD_CLOSED) == 0 && close(listenfd))
            e = errnum(ERR_CLOSE_SCK);

        return e;
}
