#ifndef _EXTRACTORS_H
#define _EXTRACTORS_H

#include <ctype.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

int extract_value(const char *stkn, const char *etkn, const char *src, char *dest, size_t dest_size);

#endif
