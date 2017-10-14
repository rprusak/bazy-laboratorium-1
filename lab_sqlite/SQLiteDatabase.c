#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "SQLiteDatabase.h"

sqlite3* createDatabase(bool useMemory) {
    sqlite3* db;
    const char* location = (useMemory) ? ":memory:" : "data.db";

    if (sqlite3_open(location, &db) != SQLITE_OK) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return NULL;
    }

    return db;
}

Record* createRecord(int id, const char* name, const char* description) {
    Record* result = (Record*)malloc(sizeof(Record));
    if (result == NULL) {
        fprintf(stderr, "malloc failed!");
        return NULL;
    }

    result->id = id;
    strcpy(result->name, name);
    strcpy(result->desc, description);

    return result;
}

void closeDatabase(sqlite3* database) {
    sqlite3_close(database);
}

int createTable(sqlite3* database) {
    const char* query = "CREATE TABLE IF NOT EXISTS records (id integer PRIMARY KEY, name varchar(%d), desc varchar(%d));";
    char buffer[256];
    sprintf(buffer, query, NAME_SIZE, DESCRIPTION_SIZE);
    return sqlite3_exec(database, buffer, NULL, NULL, NULL);
}

void insertRecordsIntoDatabase(sqlite3 *database, Record **data, unsigned int size, bool useTransaction) {
    if (createTable(database) != SQLITE_OK) {
        fprintf(stderr, "Creating table failed!\n");
        return;
    }

    if (useTransaction && sqlite3_exec(database, "BEGIN TRANSACTION", NULL, NULL, NULL) != SQLITE_OK) {
        fprintf(stderr, "Begin transaction failed!\n");
        return;
    }

    sqlite3_stmt *stmt;
    const char* query="INSERT INTO records VALUES (?1, ?2, ?3)";
    if (sqlite3_prepare_v2(database, query, (int) strlen(query), &stmt, NULL) != SQLITE_OK) {
        fprintf(stderr, "Database prepare statement error: %s\n", sqlite3_errmsg(database));
        return;
    }

    for (int i=0; i<size; i++) {
        sqlite3_bind_int(stmt, 1, data[i]->id);
        sqlite3_bind_text(stmt, 2, data[i]->name, NAME_SIZE, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 3, data[i]->desc, DESCRIPTION_SIZE, SQLITE_STATIC);

        if (sqlite3_step(stmt) != SQLITE_DONE)
            fprintf(stderr,"Database insert error\n");

        sqlite3_reset(stmt);
        printf("Row %d inserted.\n", i);
    }

    sqlite3_finalize(stmt);

    if (useTransaction && sqlite3_exec(database, "COMMIT TRANSACTION", NULL, NULL, NULL) != SQLITE_OK) {
        fprintf(stderr, "Commit transaction failed!\n");
        return;
    }
}

Record* findRecordInDatabase(sqlite3* database, int id) {
    sqlite3_stmt *stmt;
    const char* query="SELECT * FROM records WHERE id=?";
    if (sqlite3_prepare_v2(database, query, (int) strlen(query), &stmt, NULL) != SQLITE_OK) {
        fprintf(stderr, "Database prepare statement error: %s\n", sqlite3_errmsg(database));
        return NULL;
    }

    sqlite3_bind_int(stmt, 1, id);

    while(sqlite3_step(stmt) == SQLITE_ROW) {
        Record* result = createRecord(sqlite3_column_int(stmt,0), (const char *)sqlite3_column_text(stmt,1),
                                      (const char *)sqlite3_column_text(stmt,2));

        sqlite3_finalize(stmt);
        return result;
    }

    sqlite3_finalize(stmt);
    return NULL;
}