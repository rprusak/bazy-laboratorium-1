#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Config.h"
#include "SQLiteDatabase.h"
#include "RecordsUtilities.h"
#include "Memory.h"

int main(int argc, char* argv[]) {
    Record** data;
    data = generateData(RECORDS_COUNT);

    if (data == NULL)
        exit(EXIT_FAILURE);

    sqlite3* database = createDatabase(USE_MEMORY);

    clock_t c1 = clock();
    insertRecordsIntoDatabase(database, data, RECORDS_COUNT, USE_TRANSACTIONS);
    clock_t c2 = clock();
    printf("Inserting data take %f seconds \n", ((float)c2-(float)c1)/CLOCKS_PER_SEC);

    freeData(data, RECORDS_COUNT);

    c1 = clock();
    Record* record = findRecordInDatabase(database, REQUESTED_ID);
    c2 = clock();
    if (record == NULL) {
        fprintf(stderr, "Record with id %d not found!", REQUESTED_ID);
    } else {
        printf("Searching data take %f seconds \n", ((float)c2-(float)c1)/CLOCKS_PER_SEC);
        free(record);
    }

    displayMemoryUsage();
    closeDatabase(database);
}