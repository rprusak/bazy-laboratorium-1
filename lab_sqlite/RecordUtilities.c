#include "RecordsUtilities.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

char generateRandomCharacter() {
    return (char) ((rand() % 25) + 97);
}

void fillName(Record* record) {
    for(int i=0; i<NAME_SIZE; i++)
        record->name[i] = generateRandomCharacter();

    record->name[NAME_SIZE - 1] = '\0';
}

void fillDescription(Record* record) {
    for(int i=0; i<DESCRIPTION_SIZE; i++)
        record->desc[i] = generateRandomCharacter();

    record->name[DESCRIPTION_SIZE - 1] = '\0';
}

Record* generateNewRecord(int recordId) {
    Record* result;

    result = (Record*)malloc(sizeof(Record));
    if (result == NULL) {
        fprintf(stderr, "malloc failed!\n");
        return NULL;
    }

    result->id = recordId;
    fillName(result);
    fillDescription(result);

    return result;
}

void displayRecord(Record* record) {
    if (record == NULL) {
        printf("null record!");
        return;
    }

    printf("id: %d \n", record->id);
    printf("name: %s \n", record->name);
    printf("description: %s \n", record->desc);
}

Record** generateData(unsigned int size) {
    srand(time(NULL));
    Record** buffer;
    buffer = (Record**)malloc(size * sizeof(Record*));
    if (buffer == NULL) {
        fprintf(stderr, "malloc failed");
        return NULL;
    }

    for(int i=0; i<size; i++)
        buffer[i] = generateNewRecord(i);

    return buffer;
}

void freeData(Record **buffer, unsigned int size) {
    for(int i=0; i<size; i++)
        free(buffer[i]);

    free(buffer);
}

Record* findRecord(Record **records, unsigned int size, int id) {
    for (int i=0; i<size; i++)
        if(records[i]->id == id)
            return records[i];

    return NULL;
}