/* Functions for registering a user */

#include "register.hpp"

/* Flags for global use */
bool flag;


/* Callback for user exists */
static int userExistsCallback(void *data, int argc, char **argv, char **azColName){
	flag = (argc > 0);
	return 0;
}


/* Checking file existence -- for DB */
inline bool exists_test3 (const string& name) {
	struct stat buffer;   
  	return (stat (name.c_str(), &buffer) == 0); 
}


/* Checking user exists */
bool userExists(sqlite3* db, string user) {
	string sql = "SELECT * FROM users WHERE user='" + user + "'";
	char *zErrMsg = 0;
	flag = false;

	// Exec query
	int rc = sqlite3_exec(db, sql.c_str(), userExistsCallback, 0, &zErrMsg);
	
	if (rc != SQLITE_OK){
	    fprintf(stderr, "SQL error: %s\n", zErrMsg);
	    sqlite3_free(zErrMsg);
	} else {
		#ifdef DEBUG
	    fprintf(stdout, "Operation done successfully\n");
	    #endif

	    return flag;
	}

	return true;
}


/* Register with name, email, user and pass */
int registerUser(sqlite3* db, string name, string email, string user, string pass) {
	string sql = "INSERT INTO users VALUES(NULL, '" + name + "','" + email + "','" + user + "','" + pass + "')";
	char *zErrMsg = 0;

	// Exec query
	int rc = sqlite3_exec(db, sql.c_str(), userExistsCallback, 0, &zErrMsg);
	
	if (rc != SQLITE_OK){
	    fprintf(stderr, "SQL error: %s\n", zErrMsg);
	    sqlite3_free(zErrMsg);
	} else {
		#ifdef DEBUG
	    fprintf(stdout, "User registered\n");
	    #endif
	}

	return sqlite3_last_insert_rowid(db);
}