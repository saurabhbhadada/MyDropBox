#include "ClientDBManager.hpp"

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
            "user           VARCHAR(255)    NOT NULL," \
            "pass           VARCHAR(255)    NOT NULL," \
            "sess_id        INTEGER         NOT NULL);";


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
    sql = "CREATE TABLE IF NOT EXISTS user_files("  \
            "id INTEGER PRIMARY KEY  AUTOINCREMENT  NOT NULL ," \
            "filename      VARCHAR(255)    NOT NULL," \
            "md5           VARCHAR(255)    NOT NULL);";


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
            "id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL," \
            "filename VARCHAR(255) NOT NULL,"\
            "hash TEXT NOT NULL);";

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
    sql = "CREATE TABLE IF NOT EXISTS shared_by_user("  \
            "id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL," \
            "fileId INTEGER NOT NULL,"\
            "user VARCHAR(255) NOT NULL);";

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

/* Callback for logged in query */
bool login_flag = false;
static int loginCheckCallback(void *data, int argc, char **argv, char **azColName){
    login_flag = (argc > 0);
    return 0;
}

/* Callback for logged in query */
char *usr;
static int loginUserCallback(void *data, int argc, char **argv, char **azColName){
    usr = new char[strlen(argv[0])+1];
    strcpy(usr,argv[0]);
    return 0;
}

/* Callback for session id query */
int logged_in_sess;
static int sessIDCallback(void *data, int argc, char **argv, char **azColName){
    logged_in_sess = stoi(argv[0]);
    return 0;
}


/* Check logged in user */
bool isLoggedIn() {
    login_flag = false;
    string sql = "SELECT * FROM users";
    char *zErrMsg = 0;

    // Exec query
    int rc = sqlite3_exec(db, sql.c_str(), loginCheckCallback, 0, &zErrMsg);
    
    if (rc != SQLITE_OK){
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    } else {
        #ifdef DEBUG
        fprintf(stdout, "Login checked successfully\n");
        #endif

        return login_flag;
    }

    return false;    
}


/* Get logged in user */
string getLoggedInUser() {
    string sql = "SELECT user FROM users";
    char *zErrMsg = 0;

    // Exec query
    int rc = sqlite3_exec(db, sql.c_str(), loginUserCallback, 0, &zErrMsg);
    
    if (rc != SQLITE_OK){
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    } else {
        #ifdef DEBUG
        fprintf(stdout, "Login user obtained successfully\n");
        #endif
    }

    string s = "";
    for(int i=0;i<strlen(usr);i++) {
        s.push_back(usr[i]);
    }

    return s;
}


/* Get logged in user's session id */
int getSessionID() {
    string sql = "SELECT sess_id FROM users";
    char *zErrMsg = 0;

    // Exec query
    int rc = sqlite3_exec(db, sql.c_str(), sessIDCallback, 0, &zErrMsg);
    
    if (rc != SQLITE_OK){
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    } else {
        #ifdef DEBUG
        fprintf(stdout, "Session id obtained successfully\n");
        #endif
    }

    return logged_in_sess;
}


/* Add user to DB */
void addUserToDB(string user, string pass, int sess_id) {
    string sql = "INSERT INTO users VALUES(NULL,'" + user + "','" + pass + "','" + to_string(sess_id) + "')";
    char *zErrMsg = 0;

    // Exec query
    int rc = sqlite3_exec(db, sql.c_str(), NULL, 0, &zErrMsg);
    
    if (rc != SQLITE_OK){
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    } else {
        #ifdef DEBUG
        fprintf(stdout, "User added successfully\n");
        #endif
    }
}


/* Logout user */
void logoutUser() {
    string sql = "DELETE FROM users";
    char *zErrMsg = 0;

    // Exec query
    int rc = sqlite3_exec(db, sql.c_str(), NULL, 0, &zErrMsg);
    
    if (rc != SQLITE_OK){
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    } else {
        #ifdef DEBUG
        fprintf(stdout, "User deleted successfully\n");
        #endif
    }

    /* Clearing files and shares too */
    sql = "DELETE FROM user_shares";

    // Exec query
    rc = sqlite3_exec(db, sql.c_str(), NULL, 0, &zErrMsg);
    
    if (rc != SQLITE_OK){
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    } else {
        #ifdef DEBUG
        fprintf(stdout, "User deleted successfully\n");
        #endif
    }

    sql = "DELETE FROM shared_by_user";

    // Exec query
    rc = sqlite3_exec(db, sql.c_str(), NULL, 0, &zErrMsg);
    
    if (rc != SQLITE_OK){
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    } else {
        #ifdef DEBUG
        fprintf(stdout, "User deleted successfully\n");
        #endif
    }

    sql = "DELETE FROM user_files";

    // Exec query
    rc = sqlite3_exec(db, sql.c_str(), NULL, 0, &zErrMsg);
    
    if (rc != SQLITE_OK){
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    } else {
        #ifdef DEBUG
        fprintf(stdout, "User deleted successfully\n");
        #endif
    }
}

/* Callback for file check query */
bool fileCheckExists;
static int fileCheckCallback(void *data, int argc, char **argv, char **azColName){
    fileCheckExists = true;
    return 0;
}


/* Check share existence */
bool checkExistingFile(string md5) {
    string sql = "select * from user_files WHERE md5='" + md5 + "'";
    char *zErrMsg = 0;
    fileCheckExists = false;

    // Exec query
    int rc = sqlite3_exec(db, sql.c_str(), fileCheckCallback, 0, &zErrMsg);
    
    if (rc != SQLITE_OK){
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    } else {
        #ifdef DEBUG
        fprintf(stdout, "Share added successfully\n");
        #endif
    }

    return fileCheckExists;
}



/* Add file to DB */
void addFileToDB(string filename, string hash) {
    if(checkExistingFile(hash)) return;

    string sql = "INSERT INTO user_files VALUES(NULL,'" + filename + "','" + hash + "');";
    char *zErrMsg = 0;

    // Exec query
    int rc = sqlite3_exec(db, sql.c_str(), userCheckCallback, 0, &zErrMsg);
    
    if (rc != SQLITE_OK){
        fprintf(stderr, "SQL error: %s\n", &zErrMsg);
        sqlite3_free(zErrMsg);
    } else {
        #ifdef DEBUG
        fprintf(stdout, "File added successfully\n");
        #endif
    }
}

/* Callback for getting files query */
vector<pair<int,string> > files;
static int filesCallback(void *data, int argc, char **argv, char **azColName){
    string name(argv[1]);
    int fId = stoi(argv[0]);
    files.push_back(make_pair(fId,name));
    return 0;
}

/* Callback for getting shares query */
vector<pair<int,string> > myShares;
static int mySharesCallback(void *data, int argc, char **argv, char **azColName){
    string name(argv[1]);
    int fId = stoi(argv[0]);
    myShares.push_back(make_pair(fId,name));
    return 0;
}

/* Get All shared files */
vector<pair<int,string> > getAllSharesWithUser() {
    myShares.clear();
    string sql = "SELECT id,filename FROM user_shares ORDER BY filename";
    char *zErrMsg = 0;

    // Exec query
    int rc = sqlite3_exec(db, sql.c_str(), mySharesCallback, 0, &zErrMsg);
    
    if (rc != SQLITE_OK){
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    } else {
        #ifdef DEBUG
        fprintf(stdout, "Shares fetched successfully\n");
        #endif
    }

    return myShares;
}

/* Get all files */
vector<pair<int,string> > getAllFiles() {
    files.clear();
    string sql = "SELECT * FROM user_files ORDER BY filename";
    char *zErrMsg = 0;

    // Exec query
    int rc = sqlite3_exec(db, sql.c_str(), filesCallback, 0, &zErrMsg);
    
    if (rc != SQLITE_OK){
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    } else {
        #ifdef DEBUG
        fprintf(stdout, "Files fetched successfully\n");
        #endif
    }

    return files;
}

/* Callback for share check query */
bool shareExists;
static int shareCallback(void *data, int argc, char **argv, char **azColName){
    shareExists = true;
    return 0;
}


/* Check share existence */
bool checkExistingShare(string md5) {
    string sql = "select * from user_shares WHERE hash='" + md5 + "'";
    char *zErrMsg = 0;
    shareExists = false;

    // Exec query
    int rc = sqlite3_exec(db, sql.c_str(), shareCallback, 0, &zErrMsg);
    
    if (rc != SQLITE_OK){
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    } else {
        #ifdef DEBUG
        fprintf(stdout, "Share added successfully\n");
        #endif
    }

    return shareExists;
}

/* Add new share */
void addNewShare(string file, string md5) {
    if(checkExistingShare(md5)) return;

    string sql = "INSERT INTO user_shares VALUES (NULL,'" + file + "','" + md5 + "')";
    char *zErrMsg = 0;

    // Exec query
    int rc = sqlite3_exec(db, sql.c_str(), NULL, 0, &zErrMsg);
    
    if (rc != SQLITE_OK){
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    } else {
        #ifdef DEBUG
        fprintf(stdout, "Share added successfully\n");
        #endif
    }
}

/* Callback for share check query */
int file_id;
static int fileidCallback(void *data, int argc, char **argv, char **azColName){
    file_id = stoi(argv[0]);
    return 0;
}


/* Get fileid */
int getFileId(string file) {
    string sql = "SELECT id from user_files where filename='" + file + "'";
    char *zErrMsg = 0;

    // Exec query
    int rc = sqlite3_exec(db, sql.c_str(), fileidCallback, 0, &zErrMsg);
    
    if (rc != SQLITE_OK){
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    } else {
        #ifdef DEBUG
        fprintf(stdout, "Share added successfully\n");
        #endif
    }

    return file_id;
}

/* Callback for file check query */
bool userShareCheck;
static int userShareCheckCallback(void *data, int argc, char **argv, char **azColName){
    userShareCheck = true;
    return 0;
}


/* Check share existence */
bool checkExistingUserShare(string file, string user) {
    string sql = "select * from shared_by_user S, user_files F WHERE F.filename='" + file + "' AND S.fileid = F.id AND S.user = '" + user + "'";
    char *zErrMsg = 0;
    userShareCheck = false;

    // Exec query
    int rc = sqlite3_exec(db, sql.c_str(), userShareCheckCallback, 0, &zErrMsg);
    
    if (rc != SQLITE_OK){
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    } else {
        #ifdef DEBUG
        fprintf(stdout, "Share added successfully\n");
        #endif
    }

    return userShareCheck;
}


/* Add new file shared by user */
void addNewFileShare(string file, string user) {
    if(checkExistingUserShare(file,user)) return;

    string sql = "INSERT INTO shared_by_user VALUES (NULL,'" + to_string(getFileId(file)) + "','" + user + "')";
    char *zErrMsg = 0;

    // Exec query
    int rc = sqlite3_exec(db, sql.c_str(), NULL, 0, &zErrMsg);
    
    if (rc != SQLITE_OK){
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    } else {
        #ifdef DEBUG
        fprintf(stdout, "Share added successfully\n");
        #endif
    }
}


/* Callback for getting shares query */
vector<string> shares;
static int sharesCallback(void *data, int argc, char **argv, char **azColName){
    string name(argv[0]);
    shares.push_back(name);
    return 0;
}


/* Get all shares for this file */
vector<string> getAllShared(int file) {
    shares.clear();
    string sql = "SELECT user FROM shared_by_user WHERE fileId='" + to_string(file) + "'";
    char *zErrMsg = 0;

    // Exec query
    int rc = sqlite3_exec(db, sql.c_str(), sharesCallback, 0, &zErrMsg);
    
    if (rc != SQLITE_OK){
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    } else {
        #ifdef DEBUG
        fprintf(stdout, "Shares fetched successfully\n");
        #endif
    }

    return shares;
}

/* Callback for getting hash query */
string hashFile;
static int hashCallback(void *data, int argc, char **argv, char **azColName){
    string s(argv[0]);
    hashFile = s;
    return 0;
}


/* Get Hash for a file */
string getFileHashFromDB(string file) {
    string sql = "SELECT md5 FROM user_files WHERE filename='" + file + "'";
    char *zErrMsg = 0;

    // Exec query
    int rc = sqlite3_exec(db, sql.c_str(), hashCallback, 0, &zErrMsg);
    
    if (rc != SQLITE_OK){
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    } else {
        #ifdef DEBUG
        fprintf(stdout, "Hash fetched successfully\n");
        #endif
    }

    return hashFile;
}


/* Close db */
void closeDB() {
	sqlite3_close(db);
}
