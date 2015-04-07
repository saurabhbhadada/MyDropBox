#ifndef FILEINFO_H
#define FILEINFO_H

#include <QWidget>
#include <string>
#include <iostream>
#include <QInputDialog>
#include <QLineEdit>
#include "../../client/client.hpp"

using namespace std;

namespace Ui {
class FileInfo;
}

class FileInfo : public QWidget
{
    Q_OBJECT

public:
    explicit FileInfo(QWidget *parent = 0, char *hn=NULL, char *pn=NULL, int sess_id=-1);
    ~FileInfo();
    char *hostname, *portnum;
    int sess_id;

    void setStatusText(string);
    void setFileName(string);

private:
    Ui::FileInfo *ui;

private slots:
    void onOKPress();
    void onSharePress();
    void onDownloadPress();
};

#endif // FILEINFO_H
