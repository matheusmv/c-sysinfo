#include "meminfo.h"

#define BUFFERSIZE 128

#define MEMINFOPATH  "/proc/meminfo"

#define MEMTOTAL     "MemTotal:"        /* 1 */
#define MEMFREE      "MemFree:"         /* 2 */
#define MEMAVAILABLE "MemAvailable:"    /* 3 */
#define BUFFERS      "Buffers:"         /* 4 */
#define CACHED       "Cached:"          /* 5 */
#define SWAPTOTAL    "SwapTotal:"       /* 6 */
#define SWAPFREE     "SwapFree:"        /* 7 */
#define SWAPCACHED   "SwapCached:"      /* 8 */
#define SHMEM        "Shmem:"           /* 9 */
#define SRECLAIMABLE "SReclaimable:"    /* 10 */

static uint TOTAL_PROPERTIES = 10;

static void
compare_key_and_extract_ul(const char *key, const char *src, size_t src_size, uint64_t *dest)
{
        if (strncmp(src, key, strlen(key)) == 0) {
                char temp[src_size];
                extract_value(": ", " kB", src, temp, src_size);
                *dest = atol(temp);
                TOTAL_PROPERTIES -= 1;
        }
}

int
meminfo(struct MemInfo *info)
{
        memset(info, 0, sizeof(struct MemInfo));

        FILE *proc_meminfo = NULL;
        proc_meminfo = fopen(MEMINFOPATH, "r");
        if (proc_meminfo == NULL) {
                char err[BUFFERSIZE];
                strerror_r(errno, err, BUFFERSIZE);
                LOG_ERROR("%s", err);
                exit(EXIT_FAILURE);
        }

        char temp[BUFFERSIZE];
        while (fgets(temp, BUFFERSIZE, proc_meminfo) != NULL) {
                if (TOTAL_PROPERTIES == 0)
                        break;

                compare_key_and_extract_ul(MEMTOTAL, temp, BUFFERSIZE, &info->MemTotal);
                compare_key_and_extract_ul(MEMFREE, temp, BUFFERSIZE, &info->MemFree);
                compare_key_and_extract_ul(MEMAVAILABLE, temp, BUFFERSIZE, &info->MemAvailable);
                compare_key_and_extract_ul(BUFFERS, temp, BUFFERSIZE, &info->Buffers);
                compare_key_and_extract_ul(CACHED, temp, BUFFERSIZE, &info->Cached);
                compare_key_and_extract_ul(SWAPCACHED, temp, BUFFERSIZE, &info->SwapCached);
                compare_key_and_extract_ul(SWAPTOTAL, temp, BUFFERSIZE, &info->SwapTotal);
                compare_key_and_extract_ul(SWAPFREE, temp, BUFFERSIZE, &info->SwapFree);
                compare_key_and_extract_ul(SHMEM, temp, BUFFERSIZE, &info->Shmem);
                compare_key_and_extract_ul(SRECLAIMABLE, temp, BUFFERSIZE, &info->SReclaimable);
        }

        fclose(proc_meminfo);

        info->Cached += info->SReclaimable;
        info->MemUsed = info->MemTotal - info->MemFree - info->Buffers - info->Cached;

        return 0;
}
