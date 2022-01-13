#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/sysinfo.h>
#include <time.h>

#include "cpuinfo.h"
#include "file-handler.h"
#include "log-handler.h"
#include "meminfo.h"

void get_meminfo(void)
{
        struct MemInfo info;
        int status = 0;

        status = meminfo(&info);
        if (status < 0) {
                LOG_ERROR("Could not load memory information.");
                exit(EXIT_FAILURE);
        }

        fprintf(stdout, "Total: %ld MiB\n", info.MemTotal / (1 << 10));
        fprintf(stdout, "Used: %ld MiB\n", info.MemUsed / (1 << 10));
        fprintf(stdout, "Free: %ld MiB\n", info.MemFree / (1 << 10));
        fprintf(stdout, "Shared: %ld MiB\n", info.Shmem / (1 << 10));
        fprintf(stdout, "Buff/Cache: %ld MiB\n", (info.Buffers + info.Cached) / (1 << 10));
        fprintf(stdout, "Available: %ld MiB\n", info.MemAvailable / (1 << 10));
}

void get_cpuinfo(void)
{
        struct CpuInfo info;
        int status = 0;

        status = cpuinfo(&info);
        if (status < 0) {
                LOG_ERROR("Could not load cpu information.");
                exit(EXIT_FAILURE);
        }

        fprintf(stdout, "Architecture: %s", info.Architecture);
        fprintf(stdout, "Vendor ID: %s", info.VendorID);
        fprintf(stdout, "Model name: %s", info.ModelName);
        fprintf(stdout, "CPU Cores: %s", info.Cores);
        fprintf(stdout, "Threads: %s", info.Threads);
        fprintf(stdout, "CPU max MHz: %s", info.CPUMaxMHz);
        fprintf(stdout, "CPU min MHz: %s", info.CPUMinMHz);
}

void get_user(void)
{
        char *user = NULL;

        user = getenv("USER");
        if (user == NULL) {
                LOG_ERROR("$USER not defined");
                exit(EXIT_FAILURE);
        }

        fprintf(stdout, "User: %s\n", user);
}

void get_hostname(void)
{
        FILE *hostname_file = NULL;
        const char *hostname_path = "/etc/hostname";

        hostname_file = read_file(hostname_path);

        char hostname[512];

        fgets(hostname, 512, hostname_file);

        close_file(hostname_file);

        fprintf(stdout, "Hostname: %s", hostname);
}

void get_sysinfo(void)
{
        struct sysinfo info;
        int status;

        status = sysinfo(&info);
        if (status < 0) {
                char err[512];
                strerror_r(errno, err, sizeof(err));
                LOG_ERROR("%s", err);
                exit(EXIT_FAILURE);
        }

        struct tm time_info;
        char buffer[512];

        /* Time since boot */
        gmtime_r(&info.uptime, &time_info);
        strftime(buffer, sizeof(buffer), "%I:%M:%S", &time_info);
        fprintf(stdout, "Uptime: %s\n", buffer);
}

int main(int argc, char *argv[])
{
        get_meminfo();
        get_cpuinfo();
        get_sysinfo();
        get_user();
        get_hostname();

        // cat /proc/version
        // cat /etc/os-release
        // cat /etc/arch-release 
        // getenv XDG_CURRENT_DESKTOP

        return EXIT_SUCCESS;
}
