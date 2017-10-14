#ifndef SQLITE_LAB_RECORDSUTILITIES_H
#define SQLITE_LAB_RECORDSUTILITIES_H

#include "Record.h"

Record **generateData(unsigned int size);
void freeData(Record **buffer, unsigned int size);
void displayRecord(Record* record);
Record *findRecord(Record **records, unsigned int size, int id);

#endif