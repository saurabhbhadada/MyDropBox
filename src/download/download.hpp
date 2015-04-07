#ifndef DOWNLOAD_HEADER
#define DOWNLOAD_HEADER

#include <iostream>
#include <string>
#include <sys/stat.h>
#include <sqlite3.h> 
#include <vector>

#define DOWNLOAD_MESSAGE_CODE 4
#define DOWNLOAD_REQUEST 1
#define DOWNLOAD_SHARED_REQUEST 2
#define DOWNLOAD_PROCEED 3
#define DOWNLOAD_INIT 4
#define DOWNLOAD_INFO 5
#define DOWNLOAD_SUCCESS 6
#define DOWNLOAD_FATAL_ERROR 7

using namespace std;

/* Get file from id */
vector<string> getFileFromId(sqlite3* sql, int fileId);

#endif