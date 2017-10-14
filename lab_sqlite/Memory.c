#include <sys/resource.h>
#include <stdio.h>

void displayMemoryUsage() {
    struct rusage mem;
    getrusage(RUSAGE_SELF, &mem);
    printf("Max memory usage[kB]: %ld\n", mem.ru_maxrss);
}