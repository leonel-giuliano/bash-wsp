#ifndef __BASH_WSP_SERVER_H__
#define __BASH_WSP_SERVER_H__


#include <stdint.h>


#define SERV_PORT       18000
#define SERV_BACKLOG    20

#define SERV_EXIT 'q'


// FLAGS

typedef volatile uint8_t thflags_t;

#define F_LISTENFD_CLOSED   0x01
#define F_CH_EXIT           0x02
#define F_TH_ERR            0x04



#endif
