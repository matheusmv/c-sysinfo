#ifndef _CPUINFO_H
#define _CPUINFO_H

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "extractors.h"

#define BUFFERSIZE 128

/* Details about the CPU architecture */
struct CpuInfo {
        char Architecture[BUFFERSIZE];  /* Architecture */
        char Threads[BUFFERSIZE];       /* Threads */
        char VendorID[BUFFERSIZE];      /* Vendor ID */
        char ModelName[BUFFERSIZE];     /* Model name */
        char Cores[BUFFERSIZE];         /* CPU Cores */
        char CPUMHz[BUFFERSIZE];     /* CPU MHz */
};

int cpuinfo(struct CpuInfo *info);

#endif
