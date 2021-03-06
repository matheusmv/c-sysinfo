#include "osinfo.h"

#define COMMAND "echo \"User: $(whoami)\n\
$(hostnamectl | awk '{gsub(/^ +| +$/,\"\")} {print $0}')\n\
Uptime: $(uptime -p | cut -b 4-)\""

#define USER            "User:"              /* 1 */
#define HOSTNAME        "Static hostname:"   /* 2 */
#define OSNAME          "Operating System:"  /* 3 */
#define KERNEL          "Kernel:"            /* 4 */
#define ARCHITECTURE    "Architecture:"      /* 5 */
#define HARDWAREVENDOR  "Hardware Vendor:"   /* 6 */
#define HARDWAREMODEL   "Hardware Model:"    /* 7 */
#define UPTIME          "Uptime:"            /* 8 */

static uint8_t TOTAL_PROPERTIES = 8;

static void
find_key_and_extract_str(const char *key, const char *src, size_t src_size, char *dest)
{
        if (strncmp(src, key, strlen(key)) == 0) {
                extract_value(": ", "\n", src, dest, src_size);
                TOTAL_PROPERTIES -= 1;
        }
}

int osinfo(struct OsInfo *info)
{
        memset(info, 0, sizeof(struct OsInfo));

        FILE *result = popen(COMMAND, "r");
        if (result == NULL) {
                return -1;
        }

        char temp[BUFFERSIZE];
        while (fgets(temp, BUFFERSIZE, result) != NULL) {
                if (TOTAL_PROPERTIES == 0) {
                        break;
                }

                find_key_and_extract_str(USER, temp, BUFFERSIZE, info->User);
                find_key_and_extract_str(HOSTNAME, temp, BUFFERSIZE, info->Hostname);
                find_key_and_extract_str(OSNAME, temp, BUFFERSIZE, info->OSName);
                find_key_and_extract_str(KERNEL, temp, BUFFERSIZE, info->Kernel);
                find_key_and_extract_str(ARCHITECTURE, temp, BUFFERSIZE, info->Architecture);
                find_key_and_extract_str(HARDWAREVENDOR, temp, BUFFERSIZE, info->HardwareVendor);
                find_key_and_extract_str(HARDWAREMODEL, temp, BUFFERSIZE, info->HardwareModel);
                find_key_and_extract_str(UPTIME, temp, BUFFERSIZE, info->Uptime);
        }

        pclose(result);

        return 0;
}
