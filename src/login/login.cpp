#include "login.hpp"

/* Flags for global use */
bool login_flag;
int uid;

/* Callback for user exists */
static int userExistsCallback(void *data, int argc, char **argv, char **azColName){
	login_flag = (argc > 0);
	uid = stoi(argv[0]);
	return 0;
}


/* Checking user exists */
int verifyPass(sqlite3* db, string user, string pass) {
	string sql = "SELECT * FROM users WHERE user='" + user + "' AND pass='" + pass + "'";
	char *zErrMsg = 0;
	login_flag = false;

	// Exec query
	int rc = sqlite3_exec(db, sql.c_str(), userExistsCallback, 0, &zErrMsg);
	
	if (rc != SQLITE_OK){
	    fprintf(stderr, "SQL error: %s\n", zErrMsg);
	    sqlite3_free(zErrMsg);
	} else {
		#ifdef DEBUG
	    fprintf(stdout, "Operation done successfully\n");
	    #endif

	    return (login_flag) ? uid : -1;
	}

	return -1;
}


/* Login user into sessions */
int loginUser(sqlite3* db, int uid) {
	string sql = "INSERT INTO user_sessions VALUES(NULL,'" + to_string(uid) + "',CURRENT_TIMESTAMP)";
	char *zErrMsg = 0;

	// Exec query
	int rc = sqlite3_exec(db, sql.c_str(), userExistsCallback, 0, &zErrMsg);
	
	if (rc != SQLITE_OK){
	    fprintf(stderr, "SQL error: %s\n", zErrMsg);
	    sqlite3_free(zErrMsg);
	} else {
		#ifdef DEBUG
	    fprintf(stdout, "User logged in\n");
	    #endif
	}

	return sqlite3_last_insert_rowid(db);
}