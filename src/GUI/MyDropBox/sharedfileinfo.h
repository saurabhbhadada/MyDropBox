#ifndef SHAREDFILEINFO_H
#define SHAREDFILEINFO_H

#include <QWidget>
#include <string>
#include "mainapp.h"

using namespace std;

namespace Ui {
class SharedFileInfo;
}

class SharedFileInfo : public QWidget
{
    Q_OBJECT

public:
    explicit SharedFileInfo(QWidget *parent = 0, char *hn=NULL, char *pn=NULL, int sess_id=-1);
    ~SharedFileInfo();

    char *hostname, *portnum;
    int sess_id;

    void setStatusText(string);
    void setFileName(string);

private:
    Ui::SharedFileInfo *ui;

private slots:
    void onOKPress();
    void onDownloadPress();
};

#endif // SHAREDFILEINFO_H
