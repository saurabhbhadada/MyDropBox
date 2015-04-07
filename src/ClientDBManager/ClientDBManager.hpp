#ifndef DBMANAGER_HEADER
#define DBMANAGER_HEADER

#include <iostream>
#include <cstdio>
#include <string>
#include <sqlite3.h>
#include <vector>
#include <cstring>

using namespace std;

/* Open DB */
int openDB(string dbLocation);

/* Get DB instance */
sqlite3* getDBInstance();

/* Create starting tables */
void createTables();

/* Get uid from session id */
bool isLoggedIn();

/* Get logged in user */
string getLoggedInUser();

/* Get logged in user's session id */
int getSessionID();

/* Add user to DB */
void addUserToDB(string user, string pass, int sess_id);

/* Logout user */
void logoutUser();

/* Add file to DB */
void addFileToDB(string filename, string hash);

/* Add new share */
void addNewShare(string file, string md5);

/* Add new file shared by user */
void addNewFileShare(string file, string user);

/* Get All shared files */
vector<pair<int,string> > getAllSharesWithUser();

/* Get all files */
vector<pair<int,string> > getAllFiles();

/* Get all shares for this file */
vector<string> getAllShared(int file);

/* Get Hash for a file */
string getFileHashFromDB(string file);

/* Close db */
void closeDB();

#endif