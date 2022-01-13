#include "file-handler.h"

FILE *
read_file(const char *path)
{
        FILE *file = NULL;

        file = fopen(path, "r");
        if (file == NULL) {
                char err[512];
                strerror_r(errno, err, sizeof(err));
                LOG_ERROR("%s", err);
                exit(EXIT_FAILURE);
        }

        return file;
}

void
close_file(FILE *file)
{
        if (file != NULL)
                fclose(file);
}
