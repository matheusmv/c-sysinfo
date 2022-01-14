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
        char User[BUFFERSIZE];                  /* Username of the current user */
        char Hostname[BUFFERSIZE];              /* Static hostname */
        char OSName[BUFFERSIZE];                /* Operating System */
        char Kernel[BUFFERSIZE];                /* Kernel details */
        char Architecture[BUFFERSIZE];          /* Architecture */
        char HardwareVendor[BUFFERSIZE];        /* Hardware Vendor */
        char HardwareModel[BUFFERSIZE];         /* Hardware Model*/
        char Uptime[BUFFERSIZE];                /* Time since boot */
};

int osinfo(struct OsInfo *info);

#endif
