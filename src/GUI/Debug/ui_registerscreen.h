/********************************************************************************
** Form generated from reading UI file 'registerscreen.ui'
**
** Created by: Qt User Interface Compiler version 5.4.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REGISTERSCREEN_H
#define UI_REGISTERSCREEN_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_RegisterScreen
{
public:
    QLineEdit *name;
    QLabel *label;
    QLineEdit *email;
    QLineEdit *user;
    QLineEdit *passwd;
    QPushButton *register_btn;

    void setupUi(QWidget *RegisterScreen)
    {
        if (RegisterScreen->objectName().isEmpty())
            RegisterScreen->setObjectName(QStringLiteral("RegisterScreen"));
        RegisterScreen->resize(400, 300);
        name = new QLineEdit(RegisterScreen);
        name->setObjectName(QStringLiteral("name"));
        name->setGeometry(QRect(90, 70, 221, 27));
        name->setAlignment(Qt::AlignCenter);
        label = new QLabel(RegisterScreen);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(90, 20, 221, 31));
        QFont font;
        font.setFamily(QStringLiteral("Padauk"));
        font.setPointSize(14);
        font.setBold(true);
        font.setWeight(75);
        label->setFont(font);
        label->setAlignment(Qt::AlignCenter);
        email = new QLineEdit(RegisterScreen);
        email->setObjectName(QStringLiteral("email"));
        email->setGeometry(QRect(90, 100, 221, 27));
        email->setAlignment(Qt::AlignCenter);
        user = new QLineEdit(RegisterScreen);
        user->setObjectName(QStringLiteral("user"));
        user->setGeometry(QRect(90, 130, 221, 27));
        user->setAlignment(Qt::AlignCenter);
        passwd = new QLineEdit(RegisterScreen);
        passwd->setObjectName(QStringLiteral("passwd"));
        passwd->setGeometry(QRect(90, 160, 221, 27));
        passwd->setEchoMode(QLineEdit::Password);
        passwd->setAlignment(Qt::AlignCenter);
        register_btn = new QPushButton(RegisterScreen);
        register_btn->setObjectName(QStringLiteral("register_btn"));
        register_btn->setGeometry(QRect(70, 200, 261, 31));

        retranslateUi(RegisterScreen);
        QObject::connect(register_btn, SIGNAL(clicked()), RegisterScreen, SLOT(registerUser()));

        QMetaObject::connectSlotsByName(RegisterScreen);
    } // setupUi

    void retranslateUi(QWidget *RegisterScreen)
    {
        RegisterScreen->setWindowTitle(QApplication::translate("RegisterScreen", "Register", 0));
        name->setPlaceholderText(QApplication::translate("RegisterScreen", "Name", 0));
        label->setText(QApplication::translate("RegisterScreen", "Register for MyDropBox", 0));
        email->setPlaceholderText(QApplication::translate("RegisterScreen", "Email", 0));
        user->setPlaceholderText(QApplication::translate("RegisterScreen", "Username", 0));
        passwd->setPlaceholderText(QApplication::translate("RegisterScreen", "Password", 0));
        register_btn->setText(QApplication::translate("RegisterScreen", "Register", 0));
    } // retranslateUi

};

namespace Ui {
    class RegisterScreen: public Ui_RegisterScreen {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REGISTERSCREEN_H
