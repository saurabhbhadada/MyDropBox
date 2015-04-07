#ifndef LOGIN_HEADER
#define LOGIN_HEADER

#include <iostream>
#include <string>
#include <sys/stat.h>
#include <sqlite3.h> 

#define LOGIN_MESSAGE_CODE 2
#define LOGIN_REQUEST 1
#define LOGIN_SUCCESS 2
#define LOGIN_INCORRECT 3
#define LOGIN_FATAL_ERROR 4

using namespace std;

/* Check if user-pass combo is correct */
int verifyPass(sqlite3* db, string user, string pass);

/* Login with uid */
int loginUser(sqlite3* db, int uid);

#endif