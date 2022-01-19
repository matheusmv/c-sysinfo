#include "cpuinfo.h"

#define COMMAND         "lscpu | head --lines 17"

#define ARCHITECTURE    "Architecture:"         /* 1 */
#define THREADS         "CPU(s):"               /* 2 */
#define VENDORID        "Vendor ID:"            /* 3 */
#define MODELNAME       "Model name:"           /* 4 */
#define CORES           "Core(s) per socket:"   /* 5 */
#define CPUMHZ          "CPU MHz:"              /* 6 */
#define CPUMAXMHZ       "CPU max MHz:"          /* 6 */

static uint TOTAL_PROPERTIES = 6;

static void
find_key_and_extract_str(const char *key, const char *src, size_t src_size, char *dest)
{
        if (strncmp(src, key, strlen(key)) == 0) {
                extract_value(": ", "\n", src, dest, BUFFERSIZE);
                TOTAL_PROPERTIES -= 1;
        }
}

int
cpuinfo(struct CpuInfo *info)
{
        memset(info, 0, sizeof(struct CpuInfo));

        FILE *result = NULL;
        if ((result = popen(COMMAND, "r")) == NULL)
                return -1;

        char temp[BUFFERSIZE];
        while (fgets(temp, BUFFERSIZE, result) != NULL) {
                if (TOTAL_PROPERTIES == 0)
                        break;

                find_key_and_extract_str(ARCHITECTURE, temp, BUFFERSIZE, info->Architecture);
                find_key_and_extract_str(THREADS, temp, BUFFERSIZE, info->Threads);
                find_key_and_extract_str(VENDORID, temp, BUFFERSIZE, info->VendorID);
                find_key_and_extract_str(MODELNAME, temp, BUFFERSIZE, info->ModelName);
                find_key_and_extract_str(CORES, temp, BUFFERSIZE, info->Cores);
                find_key_and_extract_str(CPUMHZ, temp, BUFFERSIZE, info->CPUMHz);
                find_key_and_extract_str(CPUMAXMHZ, temp, BUFFERSIZE, info->CPUMHz);
        }

        pclose(result);

        return 0;
}
