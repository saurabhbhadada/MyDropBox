#ifndef MAINAPP_H
#define MAINAPP_H

#include <QMainWindow>
#include "../../client/client.hpp"
#include "registerscreen.h"
#include "userfiles.h"

namespace Ui {
class MainApp;
}

class MainApp : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainApp(QWidget *parent = 0, char *hn = NULL, char *pn = NULL);
    ~MainApp();
    char *hostname, *portnum;
    int sess_id;

private:
    Ui::MainApp *ui;

private slots:
    void tryLogin();
    void showRegister();
};

#endif // MAINAPP_H
