#ifndef SHARE_HEADER
#define SHARE_HEADER

#include <iostream>
#include <string>
#include <sys/stat.h>
#include <sqlite3.h> 
#include <vector>
#include "../DBManager/DBManager.hpp"

#define SHARE_MESSAGE_CODE 5
#define SHARE_REQUEST 1
#define SHARE_NO_USER 2
#define SHARE_SUCCESS 3
#define SHARE_FATAL_ERROR 4

#define SHARE_PERMISSION_READ 10
#define SHARE_PERMISSION_WRITE 11

using namespace std;

/* Share with user */
void shareWithUser(sqlite3* sql, int owner, string file, int uid);

#endif 