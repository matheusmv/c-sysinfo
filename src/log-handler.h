#ifndef _LOG_HANDLER_H
#define _LOG_HANDLER_H

#define ULINE "\x1b[4m"

#define CRED "\x1B[31m"
#define CGRN "\x1B[32m"
#define CYEL "\x1B[33m"
#define CBLU "\x1B[34m"
#define CWHT "\x1b[97m"
#define CEND "\033[0m"

#define LOG_INFO(MSG, ...) fprintf(stdout, "%sINFO%2s%s %s%s:'%s':%d%s - %s" MSG "%s\n",\
                                CGRN, "", CEND, ULINE, __FILE__, __func__, __LINE__, CEND, CWHT, ##__VA_ARGS__, CEND)

#define LOG_DEBUG(MSG, ...) fprintf(stdout, "%sDEBUG%1s%s %s%s:'%s':%d%s - %s" MSG "%s\n",\
                                CBLU, "", CEND, ULINE, __FILE__, __func__, __LINE__, CEND, CWHT, ##__VA_ARGS__, CEND)

#define LOG_WARNING(MSG, ...) fprintf(stdout, "%sWARN%2s%s %s%s:'%s':%d%s - %s" MSG "%s\n",\
                                CYEL, "", CEND, ULINE, __FILE__, __func__, __LINE__, CEND, CWHT, ##__VA_ARGS__, CEND)

#define LOG_ERROR(MSG, ...) fprintf(stderr, "%sERROR%1s%s %s%s:'%s':%d%s - %s" MSG "%s\n",\
                                CRED, "", CEND, ULINE, __FILE__, __func__, __LINE__, CEND, CWHT, ##__VA_ARGS__, CEND)

#endif
