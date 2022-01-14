#include "osinfo.h"

#define COMMAND "echo \"User: $(whoami)\n\
Hostname: $(uname -n)\n\
KernelName: $(uname -s)\n\
KernelRelease: $(uname -r)\n\
KernelVersion: $(uname -v)\n\
OperatingSystem: $(uname -o)\n\
Uptime: $(uptime -p | cut -b 4-)\""

#define USER            "User:"                 /* 1 */
#define HOSTNAME        "Hostname:"             /* 2 */
#define KERNELNAME      "KernelName:"           /* 3 */
#define KERNELRELEASE   "KernelRelease:"        /* 4 */
#define KERNELVERSION   "KernelVersion:"        /* 5 */
#define OSNAME          "OperatingSystem:"      /* 6 */
#define UPTIME          "Uptime:"               /* 7 */

static uint TOTAL_PROPERTIES = 7;

static void
compare_key_and_extract_str(const char *key, const char *src, size_t src_size, char *dest)
{
        if (strncmp(src, key, strlen(key)) == 0) {
                extract_value(": ", "\0", src, dest, BUFFERSIZE);
                TOTAL_PROPERTIES -= 1;
        }
}

int osinfo(struct OsInfo *info)
{
        memset(info, 0, sizeof(struct OsInfo));

        FILE *result = NULL;

        result = popen(COMMAND, "r");
        if (result == NULL) {
                LOG_ERROR("%s", strerror(errno));
                exit(EXIT_FAILURE);
        }

        char temp[BUFFERSIZE];
        while (fgets(temp, BUFFERSIZE, result) != NULL) {
                if (TOTAL_PROPERTIES == 0)
                        break;

                compare_key_and_extract_str(USER, temp, BUFFERSIZE, info->User);
                compare_key_and_extract_str(HOSTNAME, temp, BUFFERSIZE, info->Hostname);
                compare_key_and_extract_str(KERNELNAME, temp, BUFFERSIZE, info->KernelName);
                compare_key_and_extract_str(KERNELRELEASE, temp, BUFFERSIZE, info->KernelRelease);
                compare_key_and_extract_str(KERNELVERSION, temp, BUFFERSIZE, info->KernelVersion);
                compare_key_and_extract_str(OSNAME, temp, BUFFERSIZE, info->OSName);
                compare_key_and_extract_str(UPTIME, temp, BUFFERSIZE, info->Uptime);
        }

        pclose(result);

        return 0;
}
