#ifndef _LOG_HANDLER
#define _LOG_HANDLER

#define CRED "\x1B[31m"
#define CGRN "\x1B[32m"
#define CYEL "\x1B[33m"
#define CBLU "\x1B[34m"
#define CEND "\033[0m"

#define LOG_ERROR(MSG, ...) fprintf(stderr, "%sERROR: %s (in function: '%s' line: %d) - " MSG "%s\n",\
                                CRED, __FILE__, __func__, __LINE__, ##__VA_ARGS__, CEND)

#endif
