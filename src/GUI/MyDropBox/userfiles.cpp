#include "userfiles.h"
#include "ui_userfiles.h"
#include "listwidget.h"
#include "fileinfo.h"
#include "sharedfileinfo.h"
#include <QMessageBox>
#include <QInputDialog>
#include <QFileDialog>

UserFiles::UserFiles(QWidget *parent, char *hn, char *pn, int s_id) :
    QWidget(parent),
    ui(new Ui::UserFiles)
{
    ui->setupUi(this);
    ui->progressBar->hide();

    setWindowTitle(QString::fromStdString("MyDropBox Shared Files"));

    this->hostname = hn;
    this->portnum = pn;
    this->sess_id = s_id;

    // Sync shares
    syncFiles(hn,pn,s_id);
    syncUserShares(hn,pn,s_id);
    syncFilesSharedForUser(hn,pn,s_id);

    // Create list of files
    Files = getAllFiles();
    myShares = getAllSharesWithUser();

    for(unsigned int i=0;i<Files.size();i++) {
        listWidget *lw = new listWidget(Files[i].second, Files[i].first);
        QListWidgetItem *item = new QListWidgetItem();
        item->setSizeHint(QSize(lw->width(), lw->height()+10));

        ui->listWidget->addItem(item);
        ui->listWidget->setStyleSheet( "QListWidget::item { padding: 5px; padding-left: 10px;  border-bottom: 1px solid #ccc; }" );
        ui->listWidget->setItemWidget(item,lw);
    }

    for(unsigned int i=0;i<myShares.size();i++) {
        listWidget *lw = new listWidget(myShares[i].second, myShares[i].first);
        QListWidgetItem *item = new QListWidgetItem();
        item->setSizeHint(QSize(lw->width(), lw->height()+10));

        ui->sharedListWidget->addItem(item);
        ui->sharedListWidget->setStyleSheet( "QListWidget::item { padding: 5px; padding-left: 10px;  border-bottom: 1px solid #ccc; }" );
        ui->sharedListWidget->setItemWidget(item,lw);
    }

    connect(ui->listWidget, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(listItemOnClick(QListWidgetItem*)));
    connect(ui->sharedListWidget, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(sharedItemOnClick(QListWidgetItem*)));
}

UserFiles::~UserFiles()
{
    delete ui;
}

void UserFiles::setUser(string user) {
    ui->user_lbl->setText(QString::fromStdString(user));
}

/* Logging out */
void UserFiles::logOut() {
    logoutUser();
    this->hide();

    MainApp *ma = new MainApp(0,hostname,portnum);
    ma->show();
}

/* Uploading files */
void UserFiles::uploadFile() {
    QString fileName = QFileDialog::getOpenFileName(this, tr("Select file to share"), "~/");
    if(!QString::compare(fileName,"",Qt::CaseInsensitive)) return;

    beginUpload(hostname, portnum, sess_id, fileName.toUtf8().constData());

    // Refresh list
    ui->listWidget->clear();

    Files = getAllFiles();

    for(unsigned int i=0;i<Files.size();i++) {
        listWidget *lw = new listWidget(Files[i].second, Files[i].first);
        QListWidgetItem *item = new QListWidgetItem();
        item->setSizeHint(QSize(lw->width(), lw->height()+10));

        ui->listWidget->addItem(item);
        ui->listWidget->setStyleSheet( "QListWidget::item { padding: 5px; padding-left: 10px;  border-bottom: 1px solid #ccc; }" );
        ui->listWidget->setItemWidget(item,lw);
    }
}

/* Clicking list item */
void UserFiles::listItemOnClick(QListWidgetItem* item) {
    listWidget *lw = (listWidget*) (ui->listWidget->itemWidget(item));

    vector<string> Shares = getAllShared(lw->fileId);

    FileInfo *fileInfo = new FileInfo(0,hostname,portnum,sess_id);
    fileInfo->setFileName(lw->fileName);

    string text = "Shared with " + to_string(Shares.size()) + " people";
    fileInfo->setStatusText(text);
    fileInfo->setWindowTitle("File Information");
    fileInfo->show();

}

/* Clicking list item */
void UserFiles::sharedItemOnClick(QListWidgetItem* item) {
    listWidget *lw = (listWidget*) (ui->sharedListWidget->itemWidget(item));

//    vector<string> Shares = getAllShared(lw->fileId);

    SharedFileInfo *sharedFileInfo = new SharedFileInfo(0,hostname,portnum,sess_id);
    sharedFileInfo->setFileName(lw->fileName);

//    string text = "Shared with " + to_string(Shares.size()) + " people";
    sharedFileInfo->setStatusText("");
    sharedFileInfo->setWindowTitle("File Information");
    sharedFileInfo->show();

}

