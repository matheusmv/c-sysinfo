#include "cpuinfo.h"

#define ARCHITECTURE    "Architecture:"         /* 1 */
#define THREADS         "CPU(s):"               /* 2 */
#define VENDORID        "Vendor ID:"            /* 3 */
#define MODELNAME       "Model name:"           /* 4 */
#define CORES           "Core(s) per socket:"   /* 5 */
#define CPUMAXMHZ       "CPU max MHz:"          /* 6 */
#define CPUMIMMHZ       "CPU min MHz:"          /* 7 */

static uint TOTAL_PROPERTIES = 7;

static int
extract_value(const char *stkn, const char *src, char *dest, size_t dest_size)
{
        char *start = strstr(src, stkn);
        if (start == NULL)
                return -1;

        start++;
        const char *withe_space = " ";
        while (strncmp(start, withe_space, strlen(withe_space)) == 0)
                start++;

        char buffer[dest_size];
        memset(buffer, 0, dest_size);
        memmove(buffer, start, strlen(start));

        if (dest != NULL) {
                memset(dest, 0, dest_size);
                memcpy(dest, buffer, dest_size);
        }

        return 0;
}

static void
compare_string_and_extract_value(const char *key, const char *src, size_t src_size, char *dest)
{
        if (strncmp(src, key, strlen(key)) == 0) {
                extract_value(": ", src, dest, BUFFERSIZE);
                TOTAL_PROPERTIES -= 1;
        }
}

int
cpuinfo(struct CpuInfo *info)
{
        memset(info, 0, sizeof(struct CpuInfo));

        FILE *result = NULL;

        result = popen("lscpu | head --lines 17", "r");
        if (result == NULL) {
                char err[512];
                strerror_r(errno, err, sizeof(err));
                LOG_ERROR("%s", err);
                exit(EXIT_FAILURE);
        }

        char temp[BUFFERSIZE];
        while (fgets(temp, BUFFERSIZE, result) != NULL) {
                if (TOTAL_PROPERTIES == 0)
                        break;

                compare_string_and_extract_value(ARCHITECTURE, temp, BUFFERSIZE, info->Architecture);
                compare_string_and_extract_value(THREADS, temp, BUFFERSIZE, info->Threads);
                compare_string_and_extract_value(VENDORID, temp, BUFFERSIZE, info->VendorID);
                compare_string_and_extract_value(MODELNAME, temp, BUFFERSIZE, info->ModelName);
                compare_string_and_extract_value(CORES, temp, BUFFERSIZE, info->Cores);
                compare_string_and_extract_value(CPUMAXMHZ, temp, BUFFERSIZE, info->CPUMaxMHz);
                compare_string_and_extract_value(CPUMIMMHZ, temp, BUFFERSIZE, info->CPUMinMHz);
        }

        pclose(result);

        return 0;
}
