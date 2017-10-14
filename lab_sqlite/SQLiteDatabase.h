#ifndef SQLITE_LAB_SQLITEDATABASE_H
#define SQLITE_LAB_SQLITEDATABASE_H

#include <sqlite3.h>
#include <stdbool.h>
#include "Record.h"

sqlite3* createDatabase(bool useMemory);
void closeDatabase(sqlite3* database);

void insertRecordsIntoDatabase(sqlite3 *database, Record **data, unsigned int size, bool useTransaction);
Record* findRecordInDatabase(sqlite3* database, int id);

#endif