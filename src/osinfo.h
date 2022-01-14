#ifndef _OSINFO_H
#define _OSINFO_H

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "extractors.h"
#include "log-handler.h"

#define BUFFERSIZE 128

/* System and Hardware Details  */
struct OsInfo {
        char User[BUFFERSIZE];          /* Username of the current user */
        char Hostname[BUFFERSIZE];      /* Network hostname */
        char KernelName[BUFFERSIZE];    /* Kernel name */
        char KernelRelease[BUFFERSIZE]; /* Kernel release */
        char KernelVersion[BUFFERSIZE]; /* Kernel version */
        char OSName[BUFFERSIZE];        /* Name of the operating system */
        char Uptime[BUFFERSIZE];        /* Time since boot */
};

int osinfo(struct OsInfo *info);

#endif
