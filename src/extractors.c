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

        while (isspace(*start) || ispunct(*start))
                start++;

        char buffer[dest_size];
        memset(buffer, 0, dest_size);
        memmove(buffer, start, (strlen(start) - strlen(end) - 1));

        if (dest != NULL) {
                memset(dest, 0, dest_size);
                memmove(dest, buffer, dest_size);
        }

        return 0;
}
