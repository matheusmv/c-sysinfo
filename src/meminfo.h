#ifndef _MEMINFO
#define _MEMINFO

#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "log-handler.h"

/* Details about amount of free and used memory in the system */
struct MemInfo {
        uint64_t MemTotal;      /* Total memory size in kB */
        uint64_t MemFree;       /* Free memory size in kB */
        uint64_t MemAvailable;  /* Available memory size in kB */
        uint64_t MemUsed;       /* Used memory in kB */
        uint64_t Buffers;       /* Buffers memory size in kB */
        uint64_t Cached;        /* Cached memory size in kB */
        uint64_t SwapCached;    /* Cached swapp size in kB */
        uint64_t SwapTotal;     /* Swap size in kB */
        uint64_t SwapFree;      /* Free swap size in kB */
        uint64_t Shmem;         /* Shared memory size in kB */
        uint64_t SReclaimable;  /* Memory that is used by kernel in kB */
};

int meminfo(struct MemInfo *info);

#endif
