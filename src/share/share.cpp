#include "share.hpp"

/* Share with user */
void shareWithUser(sqlite3* db, int owner, string file, int uid) {
    // Get fileId
    int fileId = getFileId(owner,file);

	string sql = "INSERT INTO user_shares VALUES(NULL,'" + to_string(fileId) + "','" + to_string(uid) + "','" + to_string(SHARE_PERMISSION_WRITE) + "')";
    char *zErrMsg = 0;

    // Exec query
    int rc = sqlite3_exec(db, sql.c_str(), NULL, 0, &zErrMsg);
    
    if (rc != SQLITE_OK){
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    } else {
        #ifdef DEBUG
        fprintf(stdout, "User share added successfully\n");
        #endif
    }
}