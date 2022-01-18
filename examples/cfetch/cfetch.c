// gcc -O2 -pedantic-errors -Wall -Werror ../../src/*.c example2.c -o sysinfo -lpthread
// make
// make debug

#include <pthread.h>

#include "buffer.h"

#include "../../src/clog.h"
#include "../../src/cpuinfo.h"
#include "../../src/meminfo.h"
#include "../../src/osinfo.h"

static void *memthrd_fn(void *);
static void *cputhrd_fn(void *);
static void *osthrd_fn(void *);

#define CWHT "\x1b[97m"
#define CEND "\033[0m"

static const char *format[] = {
        "%s%s%s@%s%s%s              \n",      /* 0 CWHTosinfo.UserCEND@CWHTosinfo.HostnameCEND                          */
        "---------------------------\n",      /* 1 -----------------------                                              */
        "%sOS%s: %s %s              \n",      /* 2 CWHOSCENDT: osinfo.OSName osinfo.Architecture                        */
        "%sHost%s: %s               \n",      /* 3 CWHTHostCEND: osinfo.HardwareModel                                   */
        "%sKernel%s: %s             \n",      /* 4 CWHTKernelCEND: osinfo.Kernel                                        */
        "%sUptime%s: %s             \n",      /* 5 CWHTUptimeCEND: osinfo.Uptime                                        */
        "%sCPU%s: %s (%s) @ %.1fGHz \n",      /* 6 CWHTCPUCEND: cpuinfo.ModelName (cpuinfo.Threads) @ cpuinfo.CPUMaxMHz */
        "%sMemory%s: %ldMiB / %ldMiB\n"       /* 7 CWHTMemoryCEND: meminfo.MemUsed / meminfo.MemTotal                   */
};

int main(void)
{
        struct MemInfo meminfo;
        struct CpuInfo cpuinfo;
        struct OsInfo   osinfo;

        pthread_t memthrd, cputhrd, osthrd;

        pthread_create(&osthrd, NULL, osthrd_fn, &osinfo);
        pthread_create(&cputhrd, NULL, cputhrd_fn, &cpuinfo);
        pthread_create(&memthrd, NULL, memthrd_fn, &meminfo);

        buffer *template = new_buffer(512);

        pthread_join(osthrd, NULL);

        buffer_appendf(template, format[0], CWHT, osinfo.User, CEND, CWHT, osinfo.Hostname, CEND);
        buffer_appendf(template, format[1]);
        buffer_appendf(template, format[2], CWHT, CEND, osinfo.OSName, osinfo.Architecture);
        buffer_appendf(template, format[3], CWHT, CEND, osinfo.HardwareModel);
        buffer_appendf(template, format[4], CWHT, CEND, osinfo.Kernel);
        buffer_appendf(template, format[5], CWHT, CEND, osinfo.Uptime);

        pthread_join(cputhrd, NULL);

        buffer_appendf(template, format[6], CWHT, CEND, cpuinfo.ModelName, cpuinfo.Threads, (atof(cpuinfo.CPUMaxMHz) / 1000));

        pthread_join(memthrd, NULL);

        buffer_appendf(template, format[7], CWHT, CEND, meminfo.MemUsed / (1 << 10), meminfo.MemTotal / (1 << 10));

        char *result = buffer_to_string(template);
        buffer_free(template);

        fprintf(stdout, result);
        free(result);

        return EXIT_SUCCESS;
}

static void *
memthrd_fn(void *arg)
{
        struct MemInfo *info = arg;

        int status = 0;
        if ((status = meminfo(info)) < 0)
                LOG_ERROR("Could not load memory information.");

        return NULL;
}

static void *
cputhrd_fn(void *arg)
{
        struct CpuInfo *info = arg;

        int status = 0;
        if ((status = cpuinfo(info)) < 0)
                LOG_ERROR("Could not load cpu information.");

        return NULL;
}

static void *
osthrd_fn(void *arg)
{
        struct OsInfo *info = arg;

        int status = 0;
        if ((status = osinfo(info)) < 0)
                LOG_ERROR("Could not load OS information.");

        return NULL;
}
