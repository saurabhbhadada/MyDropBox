#include "DBManager.hpp"

using namespace std;

/* Control vars */
sqlite3 *db;

/* Open DB */
int openDB(string dbLocation) {
	if(sqlite3_open(dbLocation.c_str(), &db)) {
		fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
      	exit(0);
    } else {
    	createTables();
    	return 0;
    }
}

/* Get DB instance */
sqlite3* getDBInstance() {
	return db;
}

/* Create starting tables */
void createTables() {
	char *zErrMsg = 0;

	/* Create SQL statement */
    string sql = "CREATE TABLE IF NOT EXISTS users("  \
            "id INTEGER PRIMARY KEY  AUTOINCREMENT  NOT NULL ," \
            "Name           VARCHAR(255)    NOT NULL," \
            "Email          VARCHAR(255)    NOT NULL," \
            "user           VARCHAR(255)    NOT NULL," \
            "pass           VARCHAR(255)    NOT NULL);";


	/* Execute SQL statement */
   	int rc = sqlite3_exec(db, sql.c_str(), NULL, 0, &zErrMsg);
   	
   	if(rc != SQLITE_OK){
   		fprintf(stderr, "SQL error: %s\n", zErrMsg);
      	sqlite3_free(zErrMsg);
   	} else {
   		#ifdef DEBUG
    	fprintf(stdout, "Tables created successfully\n");
    	#endif
   	}

    /* Create SQL statement */
    sql = "CREATE TABLE IF NOT EXISTS user_sessions("  \
            "id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL ," \
            "uid INTEGER NOT NULL," \
            "login_time DATETIME NOT NULL);";   


    /* Execute SQL statement */
    rc = sqlite3_exec(db, sql.c_str(), NULL, 0, &zErrMsg);
    
    if(rc != SQLITE_OK){
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    } else {
        #ifdef DEBUG
        fprintf(stdout, "Tables created successfully\n");
        #endif
    }


    /* Create SQL statement */
    sql = "CREATE TABLE IF NOT EXISTS user_files("  \
            "id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL ," \
            "uid INTEGER NOT NULL," \
            "filename TEXT NOT NULL," \
            "hash TEXT NOT NULL," \
            "file_location TEXT NOT NULL, " \
            "parent INTEGER NOT NULL, " \
            "added DATETIME NOT NULL);";


    /* Execute SQL statement */
    rc = sqlite3_exec(db, sql.c_str(), NULL, 0, &zErrMsg);
    
    if(rc != SQLITE_OK){
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    } else {
        #ifdef DEBUG
        fprintf(stdout, "Tables created successfully\n");
        #endif
    }


    /* Create SQL statement */
    sql = "CREATE TABLE IF NOT EXISTS user_shares("  \
            "id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL ," \
            "fileid INTEGER NOT NULL," \
            "uid INTEGER NOT NULL," \
            "perms INTEGER NOT NULL);";

    /* Execute SQL statement */
    rc = sqlite3_exec(db, sql.c_str(), NULL, 0, &zErrMsg);
    
    if(rc != SQLITE_OK){
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    } else {
        #ifdef DEBUG
        fprintf(stdout, "Tables created successfully\n");
        #endif
    }
}

/* Callback for file exists */
int sess_uid;
static int userCheckCallback(void *data, int argc, char **argv, char **azColName){
    sess_uid = stoi(argv[0]);
    return 0;
}

/* Get uid from session id */
int getUIDFromSession(int sess_id) {
    string sql = "SELECT uid FROM user_sessions WHERE id='" + to_string(sess_id) + "'";
    char *zErrMsg = 0;
    sess_uid = -1;

    // Exec query
    int rc = sqlite3_exec(db, sql.c_str(), userCheckCallback, 0, &zErrMsg);
    
    if (rc != SQLITE_OK){
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    } else {
        #ifdef DEBUG
        fprintf(stdout, "User obtained successfully\n");
        #endif

        return sess_uid;
    }

    return -1;
}

/* Callback for file exists */
int user_uid;
static int uidCheckCallback(void *data, int argc, char **argv, char **azColName){
    user_uid = stoi(argv[0]);
    return 0;
}

/* Get user from username */
int getUID(string user) {
    string sql = "SELECT id FROM users WHERE user='" + user + "'";
    char *zErrMsg = 0;
    user_uid = -1;

    // Exec query
    int rc = sqlite3_exec(db, sql.c_str(), uidCheckCallback, 0, &zErrMsg);
    
    if (rc != SQLITE_OK){
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    } else {
        #ifdef DEBUG
        fprintf(stdout, "User obtained successfully\n");
        #endif

        return user_uid;
    }

    return -1;
}

/* Add file to DB */
void addFileToDB(int uid, string filename, string hash) {
    string sql = "INSERT INTO user_files VALUES(NULL," + to_string(uid) + ",'" + filename + "','" + hash + "','" + filename + "',-1,CURRENT_TIMESTAMP)";
    char *zErrMsg = 0;
    sess_uid = -1;

    // Exec query
    int rc = sqlite3_exec(db, sql.c_str(), userCheckCallback, 0, &zErrMsg);
    
    if (rc != SQLITE_OK){
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    } else {
        #ifdef DEBUG
        fprintf(stdout, "File added successfully\n");
        #endif
    }
}

/* Callback for file id */
int file_id;
static int fileidCheckCallback(void *data, int argc, char **argv, char **azColName){
    file_id = stoi(argv[0]);
    return 0;
}

/* Get file id */
int getFileId(int owner, string filename) {
    string sql = "SELECT id FROM user_files WHERE uid='" + to_string(owner) + "' AND filename='" + filename + "'";
    char *zErrMsg = 0;
    file_id = -1;

    // Exec query
    int rc = sqlite3_exec(db, sql.c_str(), fileidCheckCallback, 0, &zErrMsg);
    
    if (rc != SQLITE_OK){
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    } else {
        #ifdef DEBUG
        fprintf(stdout, "fileid obtained successfully\n");
        #endif

        return file_id;
    }

    return -1;
}

/* Get file shared id */
int getFileShareId(int sharedUser, string filename) {
    string sql = "SELECT F.id FROM user_files F, user_shares S WHERE F.filename = '" + filename + "' AND S.uid=" + to_string(sharedUser) + " AND F.id=S.fileid";
    cout << sql << "\n";
    char *zErrMsg = 0;
    file_id = -1;

    // Exec query
    int rc = sqlite3_exec(db, sql.c_str(), fileidCheckCallback, 0, &zErrMsg);
    
    if (rc != SQLITE_OK){
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    } else {
        #ifdef DEBUG
        fprintf(stdout, "fileid obtained successfully\n");
        #endif

        return file_id;
    }

    return -1;
}

/* Callback for file owner */
vector<pair<string,string> > files_shared;
static int sharedCheckCallback(void *data, int argc, char **argv, char **azColName){
    string s(argv[0]);
    string hash(argv[1]);
    files_shared.push_back(make_pair(s,hash));
    return 0;
}

/* Get file shared */
vector<pair<string,string> > getFilesShared(int uid) {
    string sql = "SELECT filename,hash FROM user_files F, user_shares S WHERE F.id = S.fileid AND S.uid='" + to_string(uid) + "'";
    char *zErrMsg = 0;
    files_shared.clear();

    // Exec query
    int rc = sqlite3_exec(db, sql.c_str(), sharedCheckCallback, 0, &zErrMsg);
    
    if (rc != SQLITE_OK){
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    } else {
        #ifdef DEBUG
        fprintf(stdout, "Shares obtained successfully\n");
        #endif
    }

    return files_shared;
}

/* Get file shared */
vector<pair<string,string> > getFilesUploaded(int uid) {
    string sql = "SELECT filename,hash FROM user_files WHERE uid = '" + to_string(uid) + "'";
    char *zErrMsg = 0;
    files_shared.clear();

    // Exec query
    int rc = sqlite3_exec(db, sql.c_str(), sharedCheckCallback, 0, &zErrMsg);
    
    if (rc != SQLITE_OK){
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    } else {
        #ifdef DEBUG
        fprintf(stdout, "Files obtained successfully\n");
        #endif
    }

    return files_shared;
}


/* Shares by a user */
vector<pair<string,string> > getUserShares(int uid) {
    string sql = "SELECT filename,user FROM user_shares S, user_files F, users U WHERE F.uid = '" + to_string(uid) + "' AND S.fileid = F.id AND U.id=" + to_string(uid);
    char *zErrMsg = 0;
    files_shared.clear();

    // Exec query
    int rc = sqlite3_exec(db, sql.c_str(), sharedCheckCallback, 0, &zErrMsg);
    
    if (rc != SQLITE_OK){
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    } else {
        #ifdef DEBUG
        fprintf(stdout, "Files obtained successfully\n");
        #endif
    }

    return files_shared;
}


/* Close db */
void closeDB() {
	sqlite3_close(db);
}