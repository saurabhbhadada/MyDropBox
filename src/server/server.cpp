/* The port number is passed as an argument */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <openssl/ssl.h>
#include <openssl/err.h>
#include <string>
#include <iostream>
#include <vector>
#include <sqlite3.h>

#include "../common/common.hpp"
#include "../register/register.hpp"
#include "../login/login.hpp"
#include "../DBManager/DBManager.hpp"
#include "../upload/upload.hpp"
#include "../download/download.hpp"
#include "../share/share.hpp"
#include "../sync/sync.hpp"

#define DEBUG TRUE
#define USER_DB "../info/users.db"
#define FILES_PREFIX "storage/"

#define FAIL -1

using namespace std;

// Socket used globally
int server;

// Error show method
void error(const char *msg)
{
    perror(msg);
    exit(1);
}

// Open and bind socket to port for listening
int openListener(int port) {
    int sd;
    struct sockaddr_in addr;
 
    // Open socket
    sd = socket(PF_INET, SOCK_STREAM, 0);
    
    // Clear address structure
    bzero(&addr, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = INADDR_ANY;
    
    // Bind to port
    if(bind(sd, (struct sockaddr*)&addr, sizeof(addr)) != 0)
    {
        perror("can't bind port");
        abort();
    }

    // Listen on port
    if(listen(sd, 10) != 0)
    {
        perror("Can't configure listening port");
        abort();
    }

    return sd;
}

// Check if user is root
int isRoot() {
    return (getuid() == 0);
}

// Init server context
SSL_CTX* InitServerCTX(void)
{   
    const SSL_METHOD *method;
    SSL_CTX *ctx;
 
    OpenSSL_add_all_algorithms();  /* load & register all cryptos, etc. */
    SSL_load_error_strings();   /* load all error messages */
    method = SSLv3_server_method();  /* create new server-method instance */
    ctx = SSL_CTX_new(method);   /* create new context from method */
    if(ctx == NULL)
    {
        ERR_print_errors_fp(stderr);
        abort();
    }
    return ctx;
}
 
// Load all certificates in context
void LoadCertificates(SSL_CTX* ctx, char* CertFile, char* KeyFile)
{
    /* set the local certificate from CertFile */
    if (SSL_CTX_use_certificate_file(ctx, CertFile, SSL_FILETYPE_PEM) <= 0 )
    {
        ERR_print_errors_fp(stderr);
        abort();
    }

    /* set the private key from KeyFile (may be the same as CertFile) */
    if (SSL_CTX_use_PrivateKey_file(ctx, KeyFile, SSL_FILETYPE_PEM) <= 0 )
    {
        ERR_print_errors_fp(stderr);
        abort();
    }

    /* verify private key */
    if(!SSL_CTX_check_private_key(ctx))
    {
        fprintf(stderr, "Private key does not match the public certificate\n");
        abort();
    }
}
 
void ShowCerts(SSL* ssl)
{
    X509 *cert;
    char *line;
 
    cert = SSL_get_peer_certificate(ssl); /* Get certificates (if available) */
    if(cert != NULL)
    {
        printf("Server certificates:\n");
        line = X509_NAME_oneline(X509_get_subject_name(cert), 0, 0);
        printf("Subject: %s\n", line);
        free(line);
        line = X509_NAME_oneline(X509_get_issuer_name(cert), 0, 0);
        printf("Issuer: %s\n", line);
        free(line);
        X509_free(cert);
    }
    else
        printf("No certificates.\n");
}
 
void downloadFile(SSL_CTX *ctx, string u_fileName, unsigned long u_fileSize, string u_md5, int u_uid) {
    // Open file for full fetch 
    int u_fd = open((FILES_PREFIX + u_fileName).c_str(), O_WRONLY | O_CREAT, 0666);
    char tBuf[4096];

    while(u_fileSize > 0) {
        struct sockaddr_in addr;
        socklen_t len = sizeof(addr);
        SSL *ssl;

        // accept connection as usual
        int client = accept(server, (struct sockaddr*)&addr, &len); 
        
        // Get new SSL state with context
        ssl = SSL_new(ctx);

        // Set connection socket to SSL state
        SSL_set_fd(ssl, client);

        char tBuf[4096];
        int sd;

        /* do SSL-protocol accept */
        if(SSL_accept(ssl) == FAIL) ERR_print_errors_fp(stderr);

        int file_Bytes = SSL_read(ssl, tBuf, sizeof(tBuf));
        if(file_Bytes == 0) { ERR_print_errors_fp(stderr); break; }

        if(u_fileSize >= file_Bytes) {
            write(u_fd, tBuf, file_Bytes);
            u_fileSize -= file_Bytes;
        }
        else {
            write(u_fd, tBuf, file_Bytes-1);
            u_fileSize = 0;
        }

        if(u_fileSize == 0) {
            string reply = to_string(UPLOAD_MESSAGE_CODE);
            reply += "$" + to_string(UPLOAD_SUCCESS);
            SSL_write(ssl, reply.c_str(), reply.length());
        } else {
            string reply = to_string(UPLOAD_MESSAGE_CODE);
            reply += "$" + to_string(UPLOAD_PROCEED);
            SSL_write(ssl, reply.c_str(), reply.length());
        }

        /* get socket connection */
        sd = SSL_get_fd(ssl);       

        /* release SSL state */
        SSL_free(ssl);      

        /* close connection */   
        close(sd);
    }

    close(u_fd);

    // check HASH match
    bool hashMatch = (getMD5Hash(FILES_PREFIX+u_fileName) == u_md5);

    #ifdef DEBUG
    
    if(hashMatch) cout << "MD5 Match : OK\n";
    else cout << "MD5 Match : Not OK\n";
    
    #endif

    // Add file to DB
    if(hashMatch) addFileToDB(u_uid,u_fileName,u_md5);
}

void sendFileToClient(SSL_CTX *ctx, string u_fileName, unsigned long u_fileSize) {
    // Open file for full fetch 
    int u_fd = open((FILES_PREFIX+u_fileName).c_str(), O_RDONLY);

    while(u_fileSize > 0) {
        struct sockaddr_in addr;
        socklen_t len = sizeof(addr);
        SSL *ssl;

        // accept connection as usual
        int client = accept(server, (struct sockaddr*)&addr, &len); 
        
        // Get new SSL state with context
        ssl = SSL_new(ctx);

        // Set connection socket to SSL state
        SSL_set_fd(ssl, client);

        char tBuf[4096];
        char fileBuf[4096];
        int sd;

        /* do SSL-protocol accept */
        if(SSL_accept(ssl) == FAIL) ERR_print_errors_fp(stderr);

        /* Read from file */
        int bytes = read(u_fd, fileBuf, sizeof(fileBuf));
        u_fileSize -= bytes;

        SSL_read(ssl, tBuf, sizeof(tBuf));
        SSL_write(ssl, fileBuf, bytes);

        /* get socket connection */
        sd = SSL_get_fd(ssl);       

        /* release SSL state */
        SSL_free(ssl);      

        /* close connection */   
        close(sd);

        #ifdef DEBUG
        cout << "Sent " << bytes << "B from server\n";
        #endif
    }

    close(u_fd);

    #ifdef DEBUG
    
    cout << "Send to client complete\n";
    
    #endif
}


/* Send share info to client */
void sendFileShareInfo(SSL_CTX* ctx, vector<pair<string,string> > shares) {
    int num_shares = shares.size();

    while(num_shares > 0) {
        struct sockaddr_in addr;
        socklen_t len = sizeof(addr);
        SSL *ssl;

        // accept connection as usual
        int client = accept(server, (struct sockaddr*)&addr, &len); 
        
        // Get new SSL state with context
        ssl = SSL_new(ctx);

        // Set connection socket to SSL state
        SSL_set_fd(ssl, client);

        char tBuf[4096];
        int sd;

        /* do SSL-protocol accept */
        if(SSL_accept(ssl) == FAIL) ERR_print_errors_fp(stderr);

        /* Read from vector */
        string filename = shares[--num_shares].first;
        string hash = shares[num_shares].second;

        /* Reply */
        string reply = to_string(SYNC_MESSAGE_CODE);
        reply += "$" + to_string(SYNC_DATA);
        reply += "$" + filename;
        reply += "$" + hash;

        SSL_read(ssl, tBuf, sizeof(tBuf));
        SSL_write(ssl, reply.c_str(), reply.size());

        /* get socket connection */
        sd = SSL_get_fd(ssl);       

        /* release SSL state */
        SSL_free(ssl);      

        /* close connection */   
        close(sd);

        #ifdef DEBUG
        cout << "Sent sync data from server\n";
        #endif
    }
}


void Servlet(SSL_CTX* ctx, SSL* ssl, sqlite3* sql) /* Serve the connection -- threadable */
{   
    char buf[1024];
    int sd, bytes;
    bool freePerm = true;
 
    // Message Types
    int msgType, msgAction;

    if(SSL_accept(ssl) == FAIL)     /* do SSL-protocol accept */
        ERR_print_errors_fp(stderr);
    else
    {
        #ifdef DEBUG
        ShowCerts(ssl);        /* get any certificates */
        #endif

        bytes = SSL_read(ssl, buf, sizeof(buf)); /* get request */
        if(bytes > 0)
        {
            buf[bytes] = 0;
            string rep(buf);
            vector<string> msgParts = splitString(rep,'$');
            
            // Set message type and action
            msgType = stoi(msgParts[0]);
            msgAction = stoi(msgParts[1]);

            #ifdef DEBUG

            cout << "Client msg : " << rep << "\n";
            
            /* cout << "Msg parts : ";
            for(int i=0;i<msgParts.size();i++) cout << msgParts[i] << ", ";
            cout << "\n"; */

            #endif

            // Handle message according to its type
            switch(msgType) {
                case REGISTER_MESSAGE_CODE:
                    cout << "Registration request for user: " << msgParts[2] << ", pass: " << msgParts[3] << "\n";

                    // Check if user exists
                    if(userExists(sql, msgParts[2])) {
                        string reply = to_string(REGISTER_MESSAGE_CODE);
                        reply += "$" + to_string(USER_EXISTS);

                        #ifdef DEBUG
                        cout << "User Exists\n";
                        #endif

                        SSL_write(ssl, reply.c_str(), reply.length()); /* send reply */
                    } else {
                        int regId = registerUser(sql, msgParts[4], msgParts[5], msgParts[2], msgParts[3]);

                        string reply = to_string(REGISTER_MESSAGE_CODE);
                        reply += "$" + to_string(REGISTRATION_SUCCESS);
                        reply += "$" + to_string(regId);

                        SSL_write(ssl, reply.c_str(), reply.length()); /* send reply */
                    }

                    break;

                case LOGIN_MESSAGE_CODE:
                    cout << "Login request for user: " << msgParts[2] << "\n";
                    int uid;

                    // Check if user pass is ok
                    if((uid = verifyPass(sql,msgParts[2],msgParts[3])) != -1) {
                        int sess_id = loginUser(sql,uid);
                        string reply;

                        if(sess_id > 0) {
                            reply = to_string(LOGIN_MESSAGE_CODE);
                            reply += "$" + to_string(LOGIN_SUCCESS);
                            reply += "$" + to_string(sess_id);

                            #ifdef DEBUG
                            cout << "Login OK\n";
                            #endif
                        } else {
                            reply = to_string(LOGIN_MESSAGE_CODE);
                            reply += "$" + to_string(LOGIN_FATAL_ERROR);

                            #ifdef DEBUG
                            cout << "Can't feed session\n";
                            #endif
                        }

                        SSL_write(ssl, reply.c_str(), reply.length()); /* send reply */
                    } else {
                        string reply = to_string(LOGIN_MESSAGE_CODE);
                        reply += "$" + to_string(LOGIN_INCORRECT);

                        #ifdef DEBUG
                        cout << "Login incorrect\n";
                        #endif

                        SSL_write(ssl, reply.c_str(), reply.length()); /* send reply */
                    }

                    break;

                case UPLOAD_MESSAGE_CODE:
                    if(stoi(msgParts[1]) == UPLOAD_REQUEST) {
                        /* Fetch params */
                        string u_fileName = msgParts[3];
                        unsigned long int u_fileSize = stoi(msgParts[4]);
                        string u_md5 = msgParts[5];
                        int u_uid = getUIDFromSession(stoi(msgParts[2]));

                        cout << "Upload request from User Id: " << u_uid << "\n";
                        int file_id;              

                        if((file_id = checkFileExists(sql,msgParts[5])) != -1) {
                            #ifdef DEBUG
                            cout << "File exists\n";
                            #endif

                            /* Send upload begin */
                            string reply = to_string(UPLOAD_MESSAGE_CODE);
                            reply += "$" + to_string(UPLOAD_SUCCESS);
                            SSL_write(ssl, reply.c_str(), reply.length());

                            addFileToDB(u_uid,u_fileName,u_md5);

                        } else {
                            #ifdef DEBUG
                            cout << "File doesn't exist\n";
                            #endif

                            /* Send upload begin */
                            string reply = to_string(UPLOAD_MESSAGE_CODE);
                            reply += "$" + to_string(UPLOAD_PROCEED);
                            SSL_write(ssl, reply.c_str(), reply.length());

                            /* Close to open new conns */
                            sd = SSL_get_fd(ssl);       
                            SSL_free(ssl);      
                            close(sd);   

                            downloadFile(ctx, u_fileName, u_fileSize, u_md5, u_uid);
                            freePerm = false;
                        }
                    }

                    break;

                case DOWNLOAD_MESSAGE_CODE:
                    if(stoi(msgParts[1]) == DOWNLOAD_REQUEST) {
                        /* Fetch params */
                        int d_uid = getUIDFromSession(stoi(msgParts[2]));
                        int d_fileId = getFileId(d_uid,msgParts[3]);

                        vector<string> fileDetails = getFileFromId(sql,d_fileId);

                        int d_fd = open((FILES_PREFIX + fileDetails[0]).c_str(),O_RDONLY);
                        unsigned long int d_fileSize = get_size_by_fd(d_fd);
                        close(d_fd);

                        cout << "Download request from User Id: " << d_uid << "\n";
                        
                        /* Send download begin */
                        string reply = to_string(DOWNLOAD_MESSAGE_CODE);
                        reply += "$" + to_string(DOWNLOAD_PROCEED);
                        reply += "$" + to_string(d_fileSize);
                        reply += "$" + fileDetails[1];
                        reply += "$" + fileDetails[0];
                        SSL_write(ssl, reply.c_str(), reply.length());

                        sendFileToClient(ctx, fileDetails[0], d_fileSize);
                    } else if(stoi(msgParts[1]) == DOWNLOAD_SHARED_REQUEST) {
                        /* Fetch params */
                        int d_uid = getUIDFromSession(stoi(msgParts[2]));
                        int d_fileId = getFileShareId(d_uid,msgParts[3]);

                        vector<string> fileDetails = getFileFromId(sql,d_fileId);

                        int d_fd = open((FILES_PREFIX + fileDetails[0]).c_str(),O_RDONLY);
                        unsigned long int d_fileSize = get_size_by_fd(d_fd);
                        close(d_fd);

                        cout << "Download request from User Id: " << d_uid << "\n";
                        
                        /* Send download begin */
                        string reply = to_string(DOWNLOAD_MESSAGE_CODE);
                        reply += "$" + to_string(DOWNLOAD_PROCEED);
                        reply += "$" + to_string(d_fileSize);
                        reply += "$" + fileDetails[1];
                        reply += "$" + fileDetails[0];
                        SSL_write(ssl, reply.c_str(), reply.length());

                        sendFileToClient(ctx, fileDetails[0], d_fileSize);
                    }

                    break;

                case SHARE_MESSAGE_CODE:
                    if(stoi(msgParts[1]) == SHARE_REQUEST) {
                        string user = msgParts[2];
                        int owner = getUIDFromSession(stoi(msgParts[3]));
                        string fileName = msgParts[4];
                        int uid = getUID(user);
                        
                        if(uid != -1) {
                            shareWithUser(sql,owner,fileName,uid);

                            /* Send share successful */
                            string reply = to_string(SHARE_MESSAGE_CODE);
                            reply += "$" + to_string(SHARE_SUCCESS);
                            SSL_write(ssl, reply.c_str(), reply.length());
                        } else {
                            /* Send no-user share */
                            string reply = to_string(SHARE_MESSAGE_CODE);
                            reply += "$" + to_string(SHARE_NO_USER);
                            SSL_write(ssl, reply.c_str(), reply.length());
                        }
                    }

                    break;

                case SYNC_MESSAGE_CODE:
                    if(stoi(msgParts[1]) == SYNC_REQUEST) {
                        int uid = getUIDFromSession(stoi(msgParts[2]));

                        cout << "Sync Request from user: " << uid << "\n";
                        vector<pair<string,string> > shares = getFilesShared(uid);

                        /* Send sync begin */
                        string reply = to_string(SYNC_MESSAGE_CODE);
                        reply += "$" + to_string(SYNC_PROCEED);
                        reply += "$" + to_string(shares.size());
                        SSL_write(ssl, reply.c_str(), reply.length());

                        sendFileShareInfo(ctx, shares);
                    } else if(stoi(msgParts[1]) == SYNC_FILES_REQUEST) {
                        int uid = getUIDFromSession(stoi(msgParts[2]));

                        cout << "Sync Files Request from user: " << uid << "\n";
                        vector<pair<string,string> > uploads = getFilesUploaded(uid);

                        /* Send sync begin */
                        string reply = to_string(SYNC_MESSAGE_CODE);
                        reply += "$" + to_string(SYNC_PROCEED);
                        reply += "$" + to_string(uploads.size());
                        SSL_write(ssl, reply.c_str(), reply.length());

                        sendFileShareInfo(ctx, uploads);
                    } else if(stoi(msgParts[1]) == SYNC_SHARES_REQUEST) {
                        int uid = getUIDFromSession(stoi(msgParts[2]));

                        cout << "Sync Shares Request from user: " << uid << "\n";
                        vector<pair<string,string> > uploads = getUserShares(uid);

                        /* Send sync begin */
                        string reply = to_string(SYNC_MESSAGE_CODE);
                        reply += "$" + to_string(SYNC_PROCEED);
                        reply += "$" + to_string(uploads.size());
                        SSL_write(ssl, reply.c_str(), reply.length());

                        sendFileShareInfo(ctx, uploads);
                    }

                    break;

                default:
                    cout << "Invalid message received\n";
            }
        }
        else
            ERR_print_errors_fp(stderr);
    }

    if(freePerm) {
        /* get socket connection */
        sd = SSL_get_fd(ssl);       

        /* release SSL state */
        SSL_free(ssl);      

        /* close connection */   
        close(sd);          
    }
}

int main(int argc, char *argv[])
{
    SSL_CTX *ctx;
    char *portnum;
 
    // DB
    sqlite3* sql;

    if(openDB(USER_DB) == 0) {
        #ifdef DEBUG
        cout << "DB Opened successfully\n";
        #endif

        sql = getDBInstance();
    } else {
        #ifdef DEBUG
        cout << "DB can't be opened\n";
        #endif

        exit(1);
    }

    if(!isRoot())
    {
        printf("This program must be run as root/sudo user!!\n");
        exit(0);
    }

    if(argc != 2)
    {
        printf("Usage: %s <portnum>\n", argv[0]);
        exit(0);
    }

    SSL_library_init();
 
    // Port number
    portnum = argv[1];
    
    // Init SSL
    ctx = InitServerCTX();
    string cert = "../certs/MyDropBoxCert.pem";
    char *certFile = new char[cert.length()+1];
    strcpy(certFile, cert.c_str());

    // Load certs
    LoadCertificates(ctx, certFile, certFile);
    delete[] certFile;

    // Create Server listener
    server = openListener(atoi(portnum));

    while(true)
    {   
        struct sockaddr_in addr;
        socklen_t len = sizeof(addr);
        SSL *ssl;
 
        // accept connection as usual
        int client = accept(server, (struct sockaddr*)&addr, &len); 
        printf("\nConnection: %s:%d\n", inet_ntoa(addr.sin_addr), ntohs(addr.sin_port));
        
        // Get new SSL state with context
        ssl = SSL_new(ctx);

        // Set connection socket to SSL state
        SSL_set_fd(ssl, client);

        // Service connection
        Servlet(ctx, ssl, sql);
    }

    // Close server socket
    close(server);

    // Release context
    SSL_CTX_free(ctx);

    // Close DB
    closeDB();

    return 0; 
}