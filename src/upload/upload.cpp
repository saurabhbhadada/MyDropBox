#include "upload.hpp"

/* Flags */
bool file_flag;
int fileid;

/* Callback for file exists */
static int fileExistsCallback(void *data, int argc, char **argv, char **azColName){
	file_flag = (argc > 0);
	fileid = stoi(argv[0]);
	return 0;
}

/* Check if file exists on server */
int checkFileExists(sqlite3* db, string fileHash) {
	string sql = "SELECT * FROM user_files WHERE hash='" + fileHash + "'";
	char *zErrMsg = 0;
	file_flag = false;

	// Exec query
	int rc = sqlite3_exec(db, sql.c_str(), fileExistsCallback, 0, &zErrMsg);
	
	if (rc != SQLITE_OK){
	    fprintf(stderr, "SQL error: %s\n", zErrMsg);
	    sqlite3_free(zErrMsg);
	} else {
		#ifdef DEBUG
	    fprintf(stdout, "File existence checked successfully\n");
	    #endif

	    return (file_flag) ? fileid : -1;
	}

	return -1;
}