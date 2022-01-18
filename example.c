// gcc -O2 -pedantic-errors -Wall -Werror src/*.c example.c -o sysinfo
// make ARGS="example.c"
// make debug ARGS="example.c"

#include "c-sysinfo.h"

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

void get_osinfo(void)
{
        struct OsInfo info;
        int status = 0;

        status = osinfo(&info);
        if (status < 0) {
                LOG_ERROR("Could not load OS information.");
                exit(EXIT_FAILURE);
        }

        fprintf(stdout, "User: %s", info.User);
        fprintf(stdout, "Hostname: %s", info.Hostname);
        fprintf(stdout, "OS: %s", info.OSName);
        fprintf(stdout, "Kernel: %s", info.Kernel);
        fprintf(stdout, "Architecture: %s", info.Architecture);
        fprintf(stdout, "Hardware Vendor: %s", info.HardwareVendor);
        fprintf(stdout, "Hardware Model: %s", info.HardwareModel);
        fprintf(stdout, "Uptime: %s", info.Uptime);
}

int main(int argc, char *argv[])
{
        get_meminfo();
        get_cpuinfo();
        get_osinfo();

        return EXIT_SUCCESS;
}
