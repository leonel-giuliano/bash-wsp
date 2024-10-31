#ifndef __BASH_WSP_TH_CONN_H__
#define __BASH_WSP_TH_CONN_H__


#include "server.h"


#define TH_CONN_POOL 10


typedef struct {
    int         listenfd, *pfirstpid;
    thflags_t   *pflags;
} th_conn_arg;


#endif
