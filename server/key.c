#include <stdio.h>
#include <unistd.h>
#include <termios.h>

#include "server.h"
#include "key.h"
#include "errnum.h"
#include "debug.h"


void *th_key_handler(void *arg) {
    int         listenfd = ((th_key_arg_t *)arg)->listenfd;
    sckflags_t  *pflags = ((th_key_arg_t *)arg)->pflags;

    DBASSERT((*pflags & F_CH_EXIT) == 0);


    unsetcanon();

    while((*pflags & (F_LISTENFD_CLOSED | F_CH_EXIT)) == 0)
        if(getchar() == SERV_EXIT) *pflags |= F_CH_EXIT;

    setcanon();


    if((*pflags & F_LISTENFD_CLOSED) == 0 && close(listenfd)) {
        errnum(ERR_CLOSE_SCK);
        *pflags |= F_TH_ERR;
    }

    return NULL;
}


void unsetcanon(void) {
    struct termios tm;

    tcgetattr(STDIN_FILENO, &tm);
    tm.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &tm);
}


void setcanon(void) {
    struct termios tm;

    tcgetattr(STDIN_FILENO, &tm);
    tm.c_lflag |= ICANON | ECHO;
    tcsetattr(STDIN_FILENO, TCSANOW, &tm);
}
