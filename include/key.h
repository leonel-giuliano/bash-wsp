#ifndef __BASH_WSP_KEY_H__
#define __BASH_WSP_KEY_H__


#include "server.h"


typedef struct {
    int         listenfd;
    sckflags_t  *pflags;
} th_key_arg_t;


// Recieves a 'th_key_arg_t' and closes the
// listenfd if the SERV_EXIT key was pressed
void *th_key_handler(void *arg);

// Sets non canon mode for the terminal
void unsetcanon(void);

// Sets canon mode for the terminal
void setcanon(void);


#endif
