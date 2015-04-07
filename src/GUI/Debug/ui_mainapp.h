/********************************************************************************
** Form generated from reading UI file 'mainapp.ui'
**
** Created by: Qt User Interface Compiler version 5.4.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINAPP_H
#define UI_MAINAPP_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainApp
{
public:
    QWidget *centralWidget;
    QLineEdit *user_txt;
    QLineEdit *passwd_txt;
    QPushButton *login_btn;
    QPushButton *register_btn;
    QLabel *label;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainApp)
    {
        if (MainApp->objectName().isEmpty())
            MainApp->setObjectName(QStringLiteral("MainApp"));
        MainApp->resize(400, 300);
        centralWidget = new QWidget(MainApp);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        user_txt = new QLineEdit(centralWidget);
        user_txt->setObjectName(QStringLiteral("user_txt"));
        user_txt->setGeometry(QRect(110, 60, 181, 27));
        user_txt->setFocusPolicy(Qt::StrongFocus);
        user_txt->setAlignment(Qt::AlignCenter);
        user_txt->setClearButtonEnabled(false);
        passwd_txt = new QLineEdit(centralWidget);
        passwd_txt->setObjectName(QStringLiteral("passwd_txt"));
        passwd_txt->setGeometry(QRect(110, 90, 181, 27));
        passwd_txt->setEchoMode(QLineEdit::Password);
        passwd_txt->setAlignment(Qt::AlignCenter);
        login_btn = new QPushButton(centralWidget);
        login_btn->setObjectName(QStringLiteral("login_btn"));
        login_btn->setGeometry(QRect(70, 130, 261, 31));
        register_btn = new QPushButton(centralWidget);
        register_btn->setObjectName(QStringLiteral("register_btn"));
        register_btn->setGeometry(QRect(70, 170, 261, 31));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(110, 20, 181, 21));
        QFont font;
        font.setFamily(QStringLiteral("Padauk"));
        font.setPointSize(15);
        label->setFont(font);
        label->setFocusPolicy(Qt::NoFocus);
        label->setAlignment(Qt::AlignCenter);
        MainApp->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainApp);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 400, 25));
        MainApp->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainApp);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainApp->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainApp);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainApp->setStatusBar(statusBar);

        retranslateUi(MainApp);
        QObject::connect(login_btn, SIGNAL(clicked()), MainApp, SLOT(tryLogin()));
        QObject::connect(register_btn, SIGNAL(clicked()), MainApp, SLOT(showRegister()));

        QMetaObject::connectSlotsByName(MainApp);
    } // setupUi

    void retranslateUi(QMainWindow *MainApp)
    {
        MainApp->setWindowTitle(QApplication::translate("MainApp", "MyDropBox", 0));
        user_txt->setPlaceholderText(QApplication::translate("MainApp", "Username", 0));
        passwd_txt->setPlaceholderText(QApplication::translate("MainApp", "Password", 0));
        login_btn->setText(QApplication::translate("MainApp", "Login", 0));
        register_btn->setText(QApplication::translate("MainApp", "Register", 0));
        label->setText(QApplication::translate("MainApp", "MyDropBox Login", 0));
    } // retranslateUi

};

namespace Ui {
    class MainApp: public Ui_MainApp {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINAPP_H
