#include "sharedfileinfo.h"
#include "ui_sharedfileinfo.h"
#include <QMessageBox>

SharedFileInfo::SharedFileInfo(QWidget *parent, char* hn, char* pn, int sess_id) :
    QWidget(parent),
    ui(new Ui::SharedFileInfo)
{
    ui->setupUi(this);

    this->hostname = hn;
    this->portnum = pn;
    this->sess_id = sess_id;
}

SharedFileInfo::~SharedFileInfo()
{
    delete ui;
}


void SharedFileInfo::setStatusText(string text) {
    ui->share_lbl->setText(QString::fromStdString(text));
}

void SharedFileInfo::setFileName(string file) {
    ui->fileName->setText(QString::fromStdString(file));
}

/* OK on press */
void SharedFileInfo::onOKPress() {
    this->hide();
}

/* On Download press */
void SharedFileInfo::onDownloadPress() {
    string fileName = ui->fileName->text().toUtf8().constData();
//    string md5Hash = getFileHashFromDB(fileName);

    if(beginSharedDownload(hostname,portnum,sess_id,fileName) == 0) {
        QMessageBox qmsg;
        qmsg.setText("Download successful");
        qmsg.exec();
    }
}
