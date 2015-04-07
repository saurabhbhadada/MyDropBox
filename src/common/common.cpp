#include "common.hpp"
#define DEBUG TRUE

/* Get the size of the file by its file descriptor */
unsigned long get_size_by_fd(int fd) {
    struct stat statbuf;
    if(fstat(fd, &statbuf) < 0) exit(-1);
    return statbuf.st_size;
}

/* Get the MD5 sum as hex-digits */
string get_md5_sum(unsigned char* md) {
	string s = "";

	for(int i=0; i<MD5_DIGEST_LENGTH; i++) {
        char c[20];
        sprintf(c,"%02x",md[i]);
        s += c;
    }

    return s;
}

/* Get MD5 Hash of file */
string getMD5Hash(string file) {
	int file_descript;
    unsigned long file_size;
    char* file_buffer;
    unsigned char result[MD5_DIGEST_LENGTH];

	file_descript = open(file.c_str(), O_RDONLY);
    if(file_descript < 0) exit(-1);

    file_size = get_size_by_fd(file_descript);
    file_buffer = (char*) mmap(0, file_size, PROT_READ, MAP_SHARED, file_descript, 0);

    MD5((unsigned char*) file_buffer, file_size, result);
    munmap(file_buffer, file_size); 

    close(file_descript);

    return get_md5_sum(result);
}


// Split string using a delimiter
vector<string> splitString(string s, char delim) {
    vector<string> ret;

    string tmp = "";
    for(int i=0;i<s.size();i++) {
        if(s[i] == delim) {
            ret.push_back(tmp);
            tmp = "";
        } else {
            tmp += s[i];
        }

        if(i == s.size()-1) ret.push_back(tmp);
    }

    return ret;
}