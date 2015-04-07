#ifndef REGISTERSCREEN_H
#define REGISTERSCREEN_H

#include <QWidget>
#include "../../client/client.hpp"

namespace Ui {
class RegisterScreen;
}

class RegisterScreen : public QWidget
{
    Q_OBJECT

public:
    explicit RegisterScreen(QWidget *parent = 0, char *hostname = NULL, char *portnum = NULL);
    ~RegisterScreen();
    char *hostname, *portnum;

private:
    Ui::RegisterScreen *ui;

private slots:
    void registerUser();
};

#endif // REGISTERSCREEN_H
