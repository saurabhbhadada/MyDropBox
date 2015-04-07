#include "registerscreen.h"
#include "ui_registerscreen.h"
#include <QMessageBox>

RegisterScreen::RegisterScreen(QWidget *parent, char *hostname, char *portnum) :
    QWidget(parent),
    ui(new Ui::RegisterScreen)
{
    ui->setupUi(this);

    this->hostname = hostname;
    this->portnum = portnum;
}

RegisterScreen::~RegisterScreen()
{
    delete ui;
}


/* Registration button press */
void RegisterScreen::registerUser() {
    string user = ui->user->text().toUtf8().constData();
    string pass = ui->passwd->text().toUtf8().constData();
    string name = ui->name->text().toUtf8().constData();
    string email = ui->email->text().toUtf8().constData();

    int uid = sendRegisterRequest(hostname, portnum, user, pass, name, email);

    QMessageBox msgBox;

    if(uid == -1) {
        msgBox.setText("User already exists or\nconnection to server failed");
        msgBox.exec();
    } else {
        msgBox.setText("Registration success. You may login.");
        msgBox.exec();
        this->hide();
    }
}
