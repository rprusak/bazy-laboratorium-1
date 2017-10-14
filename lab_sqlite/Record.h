#ifndef SQLITE_LAB_RECORD_H
#define SQLITE_LAB_RECORD_H

#include "Config.h"

typedef struct Rec {
    int id;
    char name[NAME_SIZE];
    char desc[DESCRIPTION_SIZE];
} Record;

#endif