#ifndef COMMON_HEADER
#define COMMON_HEADER

#include <cstdio>
#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <sstream>
#include <openssl/md5.h>
#include <string>
#include <vector>
#include <unistd.h>
#include <cstdlib>

using namespace std;

/* Get the size of the file by its file descriptor */
unsigned long get_size_by_fd(int fd);

/* Get MD5 Hash of file */
string getMD5Hash(string file);

/* Split string using a delimiter */
vector<string> splitString(string s, char delim);

#endif