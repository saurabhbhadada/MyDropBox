#ifndef REGISTER_HEADER
#define REGISTER_HEADER

#include <iostream>
#include <string>
#include <sys/stat.h>
#include <sqlite3.h> 

#define REGISTER_MESSAGE_CODE 1
#define REGISTER_REQUEST 1
#define USER_EXISTS 2
#define REGISTRATION_SUCCESS 3
#define REGISTRATION_FATAL_ERROR 4

using namespace std;


/* Check if user exists */
bool userExists(sqlite3* db, string user);


/* Register with name, email, user and pass */
/* Returns User id */
int registerUser(sqlite3* db, string name, string email, string user, string pass);

#endif