#include "mainapp.h"
#include "ui_mainapp.h"
#include <QMessageBox>

MainApp::MainApp(QWidget *parent, char *hn, char *pn) :
    QMainWindow(parent),
    ui(new Ui::MainApp)
{
    ui->setupUi(this);
    hostname = hn;
    portnum = pn;
}

MainApp::~MainApp()
{
    delete ui;
}

/* Try logging in */
void MainApp::tryLogin() {
    cout << "Trying to login\n";

    string user = ui->user_txt->text().toUtf8().constData();
    string pass = ui->passwd_txt->text().toUtf8().constData();

    sess_id = sendLoginRequest(hostname, portnum, user, pass);

    if(sess_id > 0) {
        UserFiles *userFiles = new UserFiles(0,hostname,portnum,getSessionID());
        userFiles->setUser(user);
        userFiles->show();

        this->hide();
    } else {
        QMessageBox msgBox;
        msgBox.setText("Can't login");
        msgBox.exec();
    }
}

/* Show register */
void MainApp::showRegister() {
    RegisterScreen *regScreen = new RegisterScreen(0,hostname,portnum);
    regScreen->show();
}
