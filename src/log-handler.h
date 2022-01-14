#ifndef _LOG_HANDLER_H
#define _LOG_HANDLER_H

#define ULINE "\x1b[4m"

#define CRED "\x1B[31m"
#define CGRN "\x1B[32m"
#define CYEL "\x1B[33m"
#define CBLU "\x1B[34m"
#define CWHT "\x1b[97m"
#define CEND "\033[0m"

#define LOG_INFO(MSG, ...) fprintf(stdout, "%s %sINFO%2s%s %s%s:'%s':%d%s - %s" MSG "%s\n",\
                                __TIME__, CGRN, "", CEND, ULINE, __FILE__, __func__, __LINE__, CEND, CWHT, ##__VA_ARGS__, CEND)

#define FLOG_INFO(STREAM, MSG, ...) fprintf(STREAM, "%s INFO%2s %s:'%s':%d - " MSG "\n",\
                                        __TIME__, "", __FILE__, __func__, __LINE__, ##__VA_ARGS__)

#define LOG_DEBUG(MSG, ...) fprintf(stdout, "%s %sDEBUG%1s%s %s%s:'%s':%d%s - %s" MSG "%s\n",\
                                __TIME__, CBLU, "", CEND, ULINE, __FILE__, __func__, __LINE__, CEND, CWHT, ##__VA_ARGS__, CEND)

#define FLOG_DEBUG(STREAM, MSG, ...) fprintf(STREAM, "%s DEBUG%1s %s:'%s':%d - " MSG "\n",\
                                        __TIME__, "", __FILE__, __func__, __LINE__, ##__VA_ARGS__)

#define LOG_WARNING(MSG, ...) fprintf(stdout, "%s %sWARN%2s%s %s%s:'%s':%d%s - %s" MSG "%s\n",\
                                __TIME__, CYEL, "", CEND, ULINE, __FILE__, __func__, __LINE__, CEND, CWHT, ##__VA_ARGS__, CEND)

#define FLOG_WARNING(STREAM, MSG, ...) fprintf(STREAM, "%s WARN%2s %s:'%s':%d - " MSG "\n",\
                                        __TIME__, "", __FILE__, __func__, __LINE__, ##__VA_ARGS__)

#define LOG_ERROR(MSG, ...) fprintf(stderr, "%s %sERROR%1s%s %s%s:'%s':%d%s - %s" MSG "%s\n",\
                                __TIME__, CRED, "", CEND, ULINE, __FILE__, __func__, __LINE__, CEND, CWHT, ##__VA_ARGS__, CEND)

#define FLOG_ERROR(STREAM, MSG, ...) fprintf(STREAM, "%s ERROR%1s %s:'%s':%d - " MSG "\n",\
                                        __TIME__, "", __FILE__, __func__, __LINE__, ##__VA_ARGS__)

#endif
