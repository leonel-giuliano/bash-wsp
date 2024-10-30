#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>

#include "server.h"
#include "errnum.h"


int main(void) {
    int                 e = 0;
    sckflags_t          servflags = 0;
    int                 listenfd;
    struct sockaddr_in  servaddr;

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


    close_listenfd:
        if(close(listenfd)) e = errnum(ERR_CLOSE_SCK);

        return e;
}
