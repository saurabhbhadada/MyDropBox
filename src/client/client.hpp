#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <malloc.h>
#include <string.h>
#include <sys/socket.h>
#include <resolv.h>
#include <netdb.h>
#include <openssl/ssl.h>
#include <openssl/err.h>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#include "../common/common.hpp"
#include "../register/register.hpp"
#include "../login/login.hpp"
#include "../upload/upload.hpp"
#include "../download/download.hpp"
#include "../ClientDBManager/ClientDBManager.hpp"
#include "../share/share.hpp"
#include "../sync/sync.hpp"

#define FAIL    -1
#define DEBUG TRUE
#define FILES_PREFIX "local/"
#define DB_FILE "users.db"

using namespace std;

// Send register request - Returns session id
int sendRegisterRequest(char* hostname, char* portnum, string user, string pass, string name, string email);

// Send login request - Returns session id
int sendLoginRequest(char* hostname, char* portnum, string user, string pass);

// Upload file
int beginUpload(char* hostname, char* portnum, int sess_id, string fileName);

// Download file from server
int beginDownload(char* hostname, char* portnum, int sess_id, string fileName);

// Download file from server
int beginSharedDownload(char* hostname, char* portnum, int sess_id, string fileName);

// Share file with a user
int shareFile(char *hostname, char *portnum, string user, int sess_id, string filename);

// Sync files shared with user
void syncFilesSharedForUser(char *hostname, char *portnum, int sess_id);

// Sync files
void syncFiles(char *hostname, char *portnum, int sess_id);

// Sync user shares
void syncUserShares(char *hostname, char *portnum, int sess_id);

// Check if file exists locally
bool fileExistsLocally(string file, string hash);