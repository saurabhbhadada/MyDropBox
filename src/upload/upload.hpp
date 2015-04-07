#ifndef UPLOAD_HEADER
#define UPLOAD_HEADER

#include <iostream>
#include <string>
#include <sys/stat.h>
#include <sqlite3.h> 

#define UPLOAD_MESSAGE_CODE 3
#define UPLOAD_REQUEST 1
#define UPLOAD_PROCEED 2
#define UPLOAD_INIT 3
#define UPLOAD_INFO 4
#define UPLOAD_SUCCESS 5
#define UPLOAD_FATAL_ERROR 6

using namespace std;

/* Check if file exists on server */
int checkFileExists(sqlite3* db, string fileHash);

#endif