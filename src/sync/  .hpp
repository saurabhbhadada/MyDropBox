#ifndef SYNC_HEADER
#define SYNC_HEADER

#include <iostream>
#include <string>
#include <sys/stat.h>
#include <sqlite3.h> 
#include <vector>
#include "../ClientDBManager/ClientDBManager.hpp"

#define SYNC_MESSAGE_CODE 6
#define SYNC_REQUEST 1
#define SYNC_FILES_REQUEST 2
#define SYNC_SHARES_REQUEST 3
#define SYNC_PROCEED 4
#define SYNC_SUCCESS 5
#define SYNC_DATA 6
#define SYNC_FATAL_ERROR 7

using namespace std;

#endif 