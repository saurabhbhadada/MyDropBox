#include "client.hpp"

// Create socket and server connect
int OpenConnection(const char *hostname, int port)
{   int sd;
    struct hostent *host;
    struct sockaddr_in addr;

    if ( (host = gethostbyname(hostname)) == NULL )
    {
        perror(hostname);
        abort();
    }
    sd = socket(PF_INET, SOCK_STREAM, 0);
    bzero(&addr, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = *(long*)(host->h_addr);
    if ( connect(sd, (struct sockaddr*)&addr, sizeof(addr)) != 0 )
    {
        close(sd);
        perror(hostname);
        abort();
    }
    return sd;
}

// Init SSL Engine
SSL_CTX* InitCTX(void)
{   const SSL_METHOD *method;
    SSL_CTX *ctx;

    OpenSSL_add_all_algorithms();       /* Load cryptos, et.al. */
    SSL_load_error_strings();           /* Bring in and register error messages */
    method = SSLv3_client_method();     /* Create new client-method instance */
    ctx = SSL_CTX_new(method);          /* Create new context */
    if ( ctx == NULL )
    {
        ERR_print_errors_fp(stderr);
        abort();
    }
    return ctx;
}

// Print out certificates
void ShowCerts(SSL* ssl)
{   
    X509 *cert;
    char *line;

    cert = SSL_get_peer_certificate(ssl);   /* get the server's certificate */
    if ( cert != NULL )
    {
        printf("Server certificates:\n");
        line = X509_NAME_oneline(X509_get_subject_name(cert), 0, 0);
        printf("Subject: %s\n", line);
        free(line);                         /* free the malloc'ed string */
        line = X509_NAME_oneline(X509_get_issuer_name(cert), 0, 0);
        printf("Issuer: %s\n", line);
        free(line);                         /* free the malloc'ed string */
        X509_free(cert);                    /* free the malloc'ed certificate copy */
    }
    else
        printf("No certificates.\n");
}

// Send message to server and receive the reply
char* sendMessage(char* hostname, char* portnum, string msgStr) {
    SSL_CTX* ctx = InitCTX();
    int sock_id = OpenConnection(hostname, atoi(portnum));

    char *buf = new char[4096];

    char *msg = new char[msgStr.length()];
    for(int i=0;i<msgStr.length();i++) msg[i] = msgStr[i];

    /* create new SSL connection state */
    SSL *ssl = SSL_new(ctx);                     
    
    /* attach the socket descriptor */
    SSL_set_fd(ssl, sock_id);

    /* perform the connection */
    if (SSL_connect(ssl) == FAIL)         
        ERR_print_errors_fp(stderr);
    else
    {  
        #ifdef DEBUG_VERBOSE

        cout << msgStr << "\n";
        cout << "Connected with " << SSL_get_cipher(ssl) << " encryption\n";
        ShowCerts(ssl);                             
        
        #endif

        /* encrypt & send message */
        SSL_write(ssl, msg, msgStr.length());           

        /* get reply & decrypt */
        int bytes = SSL_read(ssl, buf, 4096);    
        buf[bytes] = 0;

        #ifdef DEBUG
        printf("Received: \"%s\"\n", buf);
        #endif

        SSL_free(ssl);
    }

    // Close socket
    close(sock_id);

    // Release CTX
    SSL_CTX_free(ctx);

    return buf;
}

// Send message to server and receive the reply
pair<char*,int> sendMessageForPair(char* hostname, char* portnum, string msgStr) {
    SSL_CTX* ctx = InitCTX();
    int bytes;
    int sock_id = OpenConnection(hostname, atoi(portnum));

    char *buf = new char[4096];

    char *msg = new char[msgStr.length()];
    for(int i=0;i<msgStr.length();i++) msg[i] = msgStr[i];

    /* create new SSL connection state */
    SSL *ssl = SSL_new(ctx);                     
    
    /* attach the socket descriptor */
    SSL_set_fd(ssl, sock_id);

    /* perform the connection */
    if (SSL_connect(ssl) == FAIL)         
        ERR_print_errors_fp(stderr);
    else
    {  
        #ifdef DEBUG_VERBOSE

        cout << msgStr << "\n";
        cout << "Connected with " << SSL_get_cipher(ssl) << " encryption\n";
        ShowCerts(ssl);                             
        
        #endif

        /* encrypt & send message */
        SSL_write(ssl, msg, msgStr.length());           

        /* get reply & decrypt */
        bytes = SSL_read(ssl, buf, 4096);    
        buf[bytes] = 0;

        #ifdef DEBUG_VERBOSE
        printf("Received: \"%s\"\n", buf);
        #endif

        SSL_free(ssl);
    }

    // Close socket
    close(sock_id);

    // Release CTX
    SSL_CTX_free(ctx);

    return make_pair(buf,bytes);
}

// Send register request - Returns session id
int sendRegisterRequest(char* hostname, char* portnum, string user, string pass, string name, string email) { 
    string msgStr = to_string(REGISTER_MESSAGE_CODE);
    msgStr += "$" + to_string(REGISTER_REQUEST);
    msgStr += "$" + user;
    msgStr += "$" + pass;
    msgStr += "$" + name;
    msgStr += "$" + email;

    char* buf = sendMessage(hostname, portnum, msgStr);

    string s(buf);
    vector<string> recv = splitString(s, '$');

    if(stoi(recv[1]) == REGISTRATION_SUCCESS) return stoi(recv[2]);
    else return -1;
}

// Send login request - Returns session id
int sendLoginRequest(char* hostname, char* portnum, string user, string pass) { 
    string msgStr = to_string(LOGIN_MESSAGE_CODE);
    msgStr += "$" + to_string(LOGIN_REQUEST);
    msgStr += "$" + user;
    msgStr += "$" + pass;

    char* buf = sendMessage(hostname, portnum, msgStr);

    string s(buf);
    vector<string> recv = splitString(s, '$');

    if(stoi(recv[1]) == LOGIN_SUCCESS) {
        addUserToDB(user, pass, stoi(recv[2]));
        return stoi(recv[2]);
    }
    else return -1;
}

// Transfer file to server
void uploadFile(char* hostname, char* portnum, int sess_id, string fileName) {
    /* Open file for full send */
    int u_fd = open((FILES_PREFIX+fileName).c_str(), O_RDONLY);
    int u_fileSize = get_size_by_fd(u_fd);

    while(u_fileSize > 0) {
        char tBuf[4096];
        int file_Bytes = read(u_fd, tBuf, sizeof(tBuf));
        
        string s = "";
        for(int i=0;i<file_Bytes;i++) s += tBuf[i];

        char* buf = sendMessage(hostname,portnum,s);
        u_fileSize -= file_Bytes;

        #ifdef DEBUG_VERBOSE
        cout << "Sent " << file_Bytes << "B\n";
        cout << "Received reply : " << buf << "\n";
        #endif
    }

    close(u_fd);

    #ifdef DEBUG
    cout << "File uploaded\n";
    #endif

    addFileToDB(fileName, getMD5Hash(FILES_PREFIX+fileName));
}

// Upload file
int beginUpload(char* hostname, char* portnum, int sess_id, string fileName) {
    // Copy file from location to local folder
    vector<string> fileNameParts = splitString(fileName, '/');

    // Copy file from src to dst
    string dst = FILES_PREFIX + fileNameParts[fileNameParts.size()-1];
    ifstream srcStream(fileName, ios::binary);
    ofstream dstStream(dst, ios::binary);

    dstStream << srcStream.rdbuf();

    srcStream.close();
    dstStream.close();

    // update fileName for further use
    fileName = fileNameParts[fileNameParts.size()-1];

    int file_descript = open((FILES_PREFIX + fileName).c_str(), O_RDONLY);
    
    if(file_descript < 0) cout << "Invalid File\n";
    else {
        /* Prepare message to send */
        string msgStr = to_string(UPLOAD_MESSAGE_CODE);
        msgStr += "$" + to_string(UPLOAD_REQUEST);
        msgStr += "$" + to_string(sess_id);
        msgStr += "$" + fileName;
        msgStr += "$" + to_string(get_size_by_fd(file_descript));
        close(file_descript);
        msgStr += "$" + getMD5Hash(FILES_PREFIX+fileName);

        /* Send to server */
        char* buf = sendMessage(hostname,portnum,msgStr);

        /* Get reply info */
        string reply(buf);
        vector<string> replyComps = splitString(reply,'$');

        switch(stoi(replyComps[1])) {
            case UPLOAD_PROCEED:
                #ifdef DEBUG
                cout << "File to be uploaded\n";
                #endif

                uploadFile(hostname,portnum,sess_id,fileName);

                break;

            case UPLOAD_SUCCESS:
                cout << "Uploaded successfully\n";
                addFileToDB(fileName, getMD5Hash(FILES_PREFIX+fileName));

                break;

            default:
                cout << "Fatal error in upload\n";
        }
    }


    return 0;
}

// Download file from server
void downloadFile(char* hostname, char* portnum, size_t fileSize, string md5, string fileName) {
    /* Open file for full send */
    int d_fd = open((FILES_PREFIX + fileName).c_str(), O_WRONLY | O_CREAT, 0666);

    while(fileSize > 0) {
        char tBuf[4096];
        
        string s = to_string(DOWNLOAD_MESSAGE_CODE);
        s += "$" + to_string(DOWNLOAD_PROCEED);

        pair<char*,int> buf = sendMessageForPair(hostname,portnum,s);
        fileSize -= buf.second;

        // Write to file
        write(d_fd, buf.first, buf.second);

        #ifdef DEBUG_VERBOSE
        cout << "Received : " << buf.second << "B\n";
        #endif
    }

    close(d_fd);

    #ifdef DEBUG
    if(getMD5Hash(FILES_PREFIX+fileName) == md5) cout << "MD5 OK\n";
    else cout << "Download corrupted\n";
    #endif
}

// Begin Download file
int beginDownload(char* hostname, char* portnum, int sess_id, string filename) {
    /* Prepare message to send */
    string msgStr = to_string(DOWNLOAD_MESSAGE_CODE);
    msgStr += "$" + to_string(DOWNLOAD_REQUEST);
    msgStr += "$" + to_string(sess_id);
    msgStr += "$" + filename;

    /* Send to server */
    char* buf = sendMessage(hostname,portnum,msgStr);

    /* Get reply info */
    string reply(buf);
    vector<string> replyComps = splitString(reply,'$');

    switch(stoi(replyComps[1])) {
        case DOWNLOAD_PROCEED:
            #ifdef DEBUG
            cout << "File to be downloaded\n";
            #endif

            downloadFile(hostname,portnum,stoi(replyComps[2]),replyComps[3],replyComps[4]);
            return 0;

            break;

        case DOWNLOAD_SUCCESS:
            cout << "Downloaded successfully\n";
            return 0;

            break;

        default:
            cout << "Fatal error in download\n";
            return -1;
    }

    return -1;
}


// Download file from server
int beginSharedDownload(char* hostname, char* portnum, int sess_id, string fileName) {
    /* Prepare message to send */
    string msgStr = to_string(DOWNLOAD_MESSAGE_CODE);
    msgStr += "$" + to_string(DOWNLOAD_SHARED_REQUEST);
    msgStr += "$" + to_string(sess_id);
    msgStr += "$" + fileName;

    /* Send to server */
    char* buf = sendMessage(hostname,portnum,msgStr);

    /* Get reply info */
    string reply(buf);
    vector<string> replyComps = splitString(reply,'$');

    switch(stoi(replyComps[1])) {
        case DOWNLOAD_PROCEED:
            #ifdef DEBUG
            cout << "File to be downloaded\n";
            #endif

            downloadFile(hostname,portnum,stoi(replyComps[2]),replyComps[3],replyComps[4]);
            return 0;

            break;

        case DOWNLOAD_SUCCESS:
            cout << "Downloaded successfully\n";
            return 0;

            break;

        default:
            cout << "Fatal error in download\n";
            return -1;
    }

    return -1;
}


// Share file with a user
int shareFile(char *hostname, char *portnum, string user, int sess_id, string filename) {
    /* Prepare message to send */
    string msgStr = to_string(SHARE_MESSAGE_CODE);
    msgStr += "$" + to_string(SHARE_REQUEST);
    msgStr += "$" + user;
    msgStr += "$" + to_string(sess_id);
    msgStr += "$" + filename;

    char *buf = sendMessage(hostname,portnum,msgStr);
    string rep(buf);
    vector<string> replyParts = splitString(rep,'$');

    // Add new share
    addNewFileShare(filename,user);

    return stoi(replyParts[1]);
}



// Sync files shared with user
void syncFilesSharedForUser(char *hostname, char *portnum, int sess_id) {
    /* Prepare message to send */
    string msgStr = to_string(SYNC_MESSAGE_CODE);
    msgStr += "$" + to_string(SYNC_REQUEST);
    msgStr += "$" + to_string(sess_id);

    char *buf = sendMessage(hostname,portnum,msgStr);
    string rep(buf);
    vector<string> replyParts = splitString(rep,'$');

    if(stoi(replyParts[1]) == SYNC_PROCEED) {
        int num = stoi(replyParts[2]);
        string proceedMsg = to_string(SYNC_MESSAGE_CODE);
        proceedMsg += to_string(SYNC_PROCEED);

        for(int i=0;i<num;i++) {
            char *buff = sendMessage(hostname,portnum,proceedMsg);
            string s(buff);
            vector<string> parts = splitString(s,'$');
            addNewShare(parts[2],parts[3]);
        }
    }
}


// Sync files shared with user
void syncFiles(char *hostname, char *portnum, int sess_id) {
    /* Prepare message to send */
    string msgStr = to_string(SYNC_MESSAGE_CODE);
    msgStr += "$" + to_string(SYNC_FILES_REQUEST);
    msgStr += "$" + to_string(sess_id);

    char *buf = sendMessage(hostname,portnum,msgStr);
    string rep(buf);
    vector<string> replyParts = splitString(rep,'$');

    if(stoi(replyParts[1]) == SYNC_PROCEED) {
        int num = stoi(replyParts[2]);
        string proceedMsg = to_string(SYNC_MESSAGE_CODE);
        proceedMsg += to_string(SYNC_PROCEED);

        for(int i=0;i<num;i++) {
            char *buff = sendMessage(hostname,portnum,proceedMsg);
            string s(buff);
            vector<string> parts = splitString(s,'$');
            addFileToDB(parts[2],parts[3]);
        }
    }
}


/* Sync files Shared with user into db */
void syncUserShares(char *hostname, char *portnum, int sess_id) {
    /* Prepare message to send */
    string msgStr = to_string(SYNC_MESSAGE_CODE);
    msgStr += "$" + to_string(SYNC_SHARES_REQUEST);
    msgStr += "$" + to_string(sess_id);

    char *buf = sendMessage(hostname,portnum,msgStr);
    string rep(buf);
    vector<string> replyParts = splitString(rep,'$');

    if(stoi(replyParts[1]) == SYNC_PROCEED) {
        int num = stoi(replyParts[2]);
        string proceedMsg = to_string(SYNC_MESSAGE_CODE);
        proceedMsg += to_string(SYNC_PROCEED);

        for(int i=0;i<num;i++) {
            char *buff = sendMessage(hostname,portnum,proceedMsg);
            string s(buff);
            vector<string> parts = splitString(s,'$');
            addNewFileShare(parts[2],parts[3]);
        }
    }
}


/* Check if file exists locally */
bool fileExistsLocally(string file, string hash) {
    int fd = open((FILES_PREFIX + file).c_str(), O_RDONLY);
    if(fd < 0) return false;
    close(fd);

    return (getMD5Hash(FILES_PREFIX+file) == hash);
}