#include "meminfo.h"

#define BUFFERSIZE 512

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

static int
extract_value(const char *stkn, const char *etkn, const char *src, char *dest, size_t dest_size)
{
        char *start = strstr(src, stkn);
        char *end = strstr(src, etkn);
        if (start == NULL || end == NULL)
                return -1;

        const char *withe_space = " ";
        while (strncmp(start, withe_space, strlen(withe_space)) == 0)
                start++;

        char buffer[dest_size];
        memset(buffer, 0, dest_size);
        memmove(buffer, start, (strlen(start) - strlen(end)));

        if (dest != NULL) {
                memset(dest, 0, dest_size);
                memmove(dest, buffer, dest_size);
        }

        return 0;
}

static void
compare_string_and_extract_value(const char *key, const char *src, size_t src_size, uint64_t *dest)
{
        if (strncmp(src, key, strlen(key)) == 0) {
                char temp[BUFFERSIZE];
                extract_value(" ", " kB", src, temp, BUFFERSIZE);
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

                compare_string_and_extract_value(MEMTOTAL, temp, BUFFERSIZE, &info->MemTotal);
                compare_string_and_extract_value(MEMFREE, temp, BUFFERSIZE, &info->MemFree);
                compare_string_and_extract_value(MEMAVAILABLE, temp, BUFFERSIZE, &info->MemAvailable);
                compare_string_and_extract_value(BUFFERS, temp, BUFFERSIZE, &info->Buffers);
                compare_string_and_extract_value(CACHED, temp, BUFFERSIZE, &info->Cached);
                compare_string_and_extract_value(SWAPCACHED, temp, BUFFERSIZE, &info->SwapCached);
                compare_string_and_extract_value(SWAPTOTAL, temp, BUFFERSIZE, &info->SwapTotal);
                compare_string_and_extract_value(SWAPFREE, temp, BUFFERSIZE, &info->SwapFree);
                compare_string_and_extract_value(SHMEM, temp, BUFFERSIZE, &info->Shmem);
                compare_string_and_extract_value(SRECLAIMABLE, temp, BUFFERSIZE, &info->SReclaimable);
        }

        fclose(proc_meminfo);

        info->Cached += info->SReclaimable;
        info->MemUsed = info->MemTotal - info->MemFree - info->Buffers - info->Cached;

        return 0;
}
