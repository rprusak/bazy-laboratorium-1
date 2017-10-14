#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "Config.h"
#include "Record.h"
#include "RecordsUtilities.h"
#include "Memory.h"

int main() {
    Record** data;

    clock_t c1 = clock();
    data = generateData(RECORDS_COUNT);
    clock_t c2 = clock();

    if (data == NULL)
     exit(EXIT_FAILURE);

    printf("Generating data take %f seconds \n", ((float)c2-(float)c1)/CLOCKS_PER_SEC);

    c1 = clock();
    Record* foundRecord = findRecord(data, RECORDS_COUNT, REQUESTED_ID);
    c2 = clock();

    if (foundRecord == NULL)
        fprintf(stderr, "Record with id %d not found!", REQUESTED_ID);
    else
        printf("Searching data take %f seconds \n", ((float)c2-(float)c1)/CLOCKS_PER_SEC);

    displayMemoryUsage();
    freeData(data, RECORDS_COUNT);

    return 0;
}