#include "extractors.h"

int
extract_value(const char *stkn, const char *etkn, const char *src, char *dest, size_t dest_size)
{
        char *start = strstr(src, stkn);
        if (start == NULL)
                return -1;

        char *end = etkn == NULL || strncmp(etkn, "\n", strlen("\n")) == 0 ?
                &start[strlen(start)] : strstr(src, etkn);
        if (end == NULL)
                return -1;

        start++;
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
