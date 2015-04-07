#ifndef USERFILES_H
#define USERFILES_H

#include <QWidget>
#include <QListWidget>
#include <QListWidgetItem>
#include <string>
#include "../../ClientDBManager/ClientDBManager.hpp"
#include "mainapp.h"

using namespace std;

namespace Ui {
class UserFiles;
}

class UserFiles : public QWidget
{
    Q_OBJECT

public:
    explicit UserFiles(QWidget *parent = 0, char* hn = NULL, char* pn = NULL, int s_id = -1);
    ~UserFiles();
    char *hostname, *portnum;
    int sess_id;

    /* Set username */
    void setUser(string user);

    /* Files */
    vector<pair<int,string> > Files;
    vector<pair<int,string> > myShares;

private:
    Ui::UserFiles *ui;

public slots:
    void listItemOnClick(QListWidgetItem*);
    void sharedItemOnClick(QListWidgetItem*);

private slots:
    void logOut();
    void uploadFile();
};

#endif // USERFILES_H
