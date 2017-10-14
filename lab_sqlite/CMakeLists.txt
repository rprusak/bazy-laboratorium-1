cmake_minimum_required(VERSION 3.8)
project(sqlite_lab)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES Record.h RecordsUtilities.h RecordUtilities.c Memory.h Memory.c)
set(SQLITE_FILES SQLiteDatabase.h SQLiteDatabase.c)

add_executable(program1 program1.c Config.h ${SOURCE_FILES})
add_executable(program2 program2.c Config.h ${SOURCE_FILES} ${SQLITE_FILES})
target_link_libraries(program2 sqlite3)
