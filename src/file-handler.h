#ifndef _FILE_HANDLER
#define _FILE_HANDLER

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "log-handler.h"

FILE *read_file(const char *path);
void close_file(FILE *file);

#endif
