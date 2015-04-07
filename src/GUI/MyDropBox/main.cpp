#include "mainapp.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    if(argc != 3)
    {
        printf("Usage: %s <hostname> <portnum>\n", argv[0]);
        exit(0);
    }

    SSL_library_init();

    if(openDB(DB_FILE) == 0) {
        #ifdef DEBUG
        cout << "DB Opened successfully\n";
        #endif
    } else {
        #ifdef DEBUG
        cout << "DB can't be opened\n";
        #endif

        exit(1);
    }

    QApplication a(argc, argv);

    if(!isLoggedIn()) {
        MainApp *w = new MainApp(0,argv[1],argv[2]);
        w->show();
    }
    else {
        UserFiles *w = new UserFiles(0,argv[1],argv[2],getSessionID());
        w->setUser(getLoggedInUser());
        w->show();
    }

    return a.exec();
}
