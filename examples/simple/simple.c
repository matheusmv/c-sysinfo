// gcc -O2 -pedantic-errors -Wall -Werror ../../src/*.c simple.c -o sysinfo
// make
// make debug

#include "../../src/clog.h"
#include "../../src/cpuinfo.h"
#include "../../src/meminfo.h"
#include "../../src/osinfo.h"

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

        fprintf(stdout, "Architecture: %s\n", info.Architecture);
        fprintf(stdout, "Vendor ID: %s\n", info.VendorID);
        fprintf(stdout, "Model name: %s\n", info.ModelName);
        fprintf(stdout, "CPU Cores: %s\n", info.Cores);
        fprintf(stdout, "Threads: %s\n", info.Threads);
        fprintf(stdout, "CPU MHz: %s\n", info.CPUMHz);
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

        fprintf(stdout, "User: %s\n", info.User);
        fprintf(stdout, "Hostname: %s\n", info.Hostname);
        fprintf(stdout, "OS: %s\n", info.OSName);
        fprintf(stdout, "Kernel: %s\n", info.Kernel);
        fprintf(stdout, "Architecture: %s\n", info.Architecture);
        fprintf(stdout, "Hardware Vendor: %s\n", info.HardwareVendor);
        fprintf(stdout, "Hardware Model: %s\n", info.HardwareModel);
        fprintf(stdout, "Uptime: %s\n", info.Uptime);
}

int main(void)
{
        get_meminfo();
        get_cpuinfo();
        get_osinfo();

        return EXIT_SUCCESS;
}
