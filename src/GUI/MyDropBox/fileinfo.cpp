#include "fileinfo.h"
#include "ui_fileinfo.h"
#include <QMessageBox>

FileInfo::FileInfo(QWidget *parent, char *hn, char *pn, int sess_id) :
    QWidget(parent),
    ui(new Ui::FileInfo)
{
    ui->setupUi(this);

    this->hostname = hn;
    this->portnum = pn;
    this->sess_id = sess_id;
}

FileInfo::~FileInfo()
{
    delete ui;
}

void FileInfo::setStatusText(string text) {
    ui->share_lbl->setText(QString::fromStdString(text));
}

void FileInfo::setFileName(string file) {
    ui->fileName->setText(QString::fromStdString(file));
}

/* OK on press */
void FileInfo::onOKPress() {
    this->hide();
}

/* On Share press */
void FileInfo::onSharePress() {
    bool ok;
    QString text = QInputDialog::getText(this, tr("Share file"), tr("Username:"),
                                         QLineEdit::Normal, tr("Enter Username"), &ok);

    if (ok && !text.isEmpty()) {
        cout << "Sharing " << ui->fileName->text().toUtf8().constData() << " with " << text.toUtf8().constData() << "\n";
        shareFile(hostname,portnum,text.toUtf8().constData(),sess_id,ui->fileName->text().toUtf8().constData());
    }
}

/* On Download press */
void FileInfo::onDownloadPress() {
    string fileName = ui->fileName->text().toUtf8().constData();
    string md5Hash = getFileHashFromDB(fileName);

    if(fileExistsLocally(fileName, md5Hash) || beginDownload(hostname,portnum,sess_id,fileName) == 0) {
        QMessageBox qmsg;
        qmsg.setText("Download successful");
        qmsg.exec();
    }
}
