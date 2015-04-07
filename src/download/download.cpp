#include "download.hpp"

/* Flags */
string md5,filename;

/* Callback for file exists */
static int fileCallback(void *data, int argc, char **argv, char **azColName){
	filename = argv[0];
	md5 = argv[1];
	return 0;
}

/* Get file from id */
vector<string> getFileFromId(sqlite3* db, int fileId) {
	string sql = "SELECT filename,hash FROM user_files WHERE id='" + to_string(fileId) + "'";
	char *zErrMsg = 0;

	vector<string> ret;

	// Exec query
	int rc = sqlite3_exec(db, sql.c_str(), fileCallback, 0, &zErrMsg);
	
	if (rc != SQLITE_OK){
	    fprintf(stderr, "SQL error: %s\n", zErrMsg);
	    sqlite3_free(zErrMsg);
	} else {
		#ifdef DEBUG
	    fprintf(stdout, "File checked successfully\n");
	    #endif

	    ret.push_back(filename);
	    ret.push_back(md5);
	}

	return ret;
}