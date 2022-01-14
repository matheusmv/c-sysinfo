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
                memmove(dest, buffer, dest_size);
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

int osinfo(struct OsInfo *info)
{
        memset(info, 0, sizeof(struct OsInfo));

        FILE *result = NULL;

        result = popen(COMMAND, "r");
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

                compare_string_and_extract_value(USER, temp, BUFFERSIZE, info->User);
                compare_string_and_extract_value(HOSTNAME, temp, BUFFERSIZE, info->Hostname);
                compare_string_and_extract_value(KERNELNAME, temp, BUFFERSIZE, info->KernelName);
                compare_string_and_extract_value(KERNELRELEASE, temp, BUFFERSIZE, info->KernelRelease);
                compare_string_and_extract_value(KERNELVERSION, temp, BUFFERSIZE, info->KernelVersion);
                compare_string_and_extract_value(OSNAME, temp, BUFFERSIZE, info->OSName);
                compare_string_and_extract_value(UPTIME, temp, BUFFERSIZE, info->Uptime);
        }

        pclose(result);

        return 0;
}
