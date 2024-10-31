#ifndef __BASH_WSP_DEBUG_H__
#define __BASH_WSP_DEBUG_H__


#include <assert.h>


// Comment to get rid of the debugs
// #define _DEBUG_ON


#ifdef _DEBUG_ON
    #define DBASSERT(cond) assert(cond);
#else
    #define DBASSERT(cond) ((void)0);
#endif


#endif
