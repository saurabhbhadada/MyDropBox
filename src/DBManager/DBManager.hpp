#ifndef DBMANAGER_HEADER
#define DBMANAGER_HEADER

#include <iostream>
#include <cstdio>
#include <string>
#include <sqlite3.h>
#include <vector>

using namespace std;

/* Open DB */
int openDB(string dbLocation);

/* Get DB instance */
sqlite3* getDBInstance();

/* Create starting tables */
void createTables();

/* Get uid from session id */
int getUIDFromSession(int sess_id);

/* Get user from username */
int getUID(string user);

/* Add file to DB */
void addFileToDB(int uid, string filename, string hash);

/* Get file id */
int getFileId(int owner, string filename);

/* Get file shared id */
int getFileShareId(int sharedUser, string filename);

/* Get file shared */
vector<pair<string,string> > getFilesShared(int uid);

/* Get files uploaded by a user */
vector<pair<string,string> > getFilesUploaded(int uid);

/* Get shares by a user */
vector<pair<string,string> > getUserShares(int uid);

/* Close db */
void closeDB();

#endif