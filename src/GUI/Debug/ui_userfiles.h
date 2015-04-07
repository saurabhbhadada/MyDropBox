/********************************************************************************
** Form generated from reading UI file 'userfiles.ui'
**
** Created by: Qt User Interface Compiler version 5.4.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_USERFILES_H
#define UI_USERFILES_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_UserFiles
{
public:
    QLabel *label;
    QLabel *label_2;
    QLabel *user_lbl;
    QPushButton *logout;
    QProgressBar *progressBar;
    QLabel *label_3;
    QPushButton *upload_btn;
    QListWidget *listWidget;
    QLabel *label_4;
    QListWidget *sharedListWidget;

    void setupUi(QWidget *UserFiles)
    {
        if (UserFiles->objectName().isEmpty())
            UserFiles->setObjectName(QStringLiteral("UserFiles"));
        UserFiles->resize(640, 480);
        label = new QLabel(UserFiles);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(20, 10, 171, 41));
        QFont font;
        font.setFamily(QStringLiteral("Padauk"));
        font.setPointSize(20);
        font.setBold(true);
        font.setWeight(75);
        font.setKerning(true);
        label->setFont(font);
        label_2 = new QLabel(UserFiles);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(480, 20, 67, 17));
        user_lbl = new QLabel(UserFiles);
        user_lbl->setObjectName(QStringLiteral("user_lbl"));
        user_lbl->setGeometry(QRect(530, 20, 101, 17));
        QFont font1;
        font1.setBold(true);
        font1.setWeight(75);
        user_lbl->setFont(font1);
        logout = new QPushButton(UserFiles);
        logout->setObjectName(QStringLiteral("logout"));
        logout->setGeometry(QRect(320, 10, 131, 31));
        progressBar = new QProgressBar(UserFiles);
        progressBar->setObjectName(QStringLiteral("progressBar"));
        progressBar->setGeometry(QRect(20, 440, 601, 23));
        progressBar->setValue(50);
        progressBar->setTextDirection(QProgressBar::TopToBottom);
        label_3 = new QLabel(UserFiles);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(20, 60, 161, 17));
        QFont font2;
        font2.setFamily(QStringLiteral("Padauk"));
        font2.setPointSize(14);
        label_3->setFont(font2);
        upload_btn = new QPushButton(UserFiles);
        upload_btn->setObjectName(QStringLiteral("upload_btn"));
        upload_btn->setGeometry(QRect(20, 440, 601, 27));
        listWidget = new QListWidget(UserFiles);
        listWidget->setObjectName(QStringLiteral("listWidget"));
        listWidget->setGeometry(QRect(20, 90, 291, 341));
        label_4 = new QLabel(UserFiles);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(330, 60, 161, 17));
        label_4->setFont(font2);
        sharedListWidget = new QListWidget(UserFiles);
        sharedListWidget->setObjectName(QStringLiteral("sharedListWidget"));
        sharedListWidget->setGeometry(QRect(330, 90, 291, 341));

        retranslateUi(UserFiles);
        QObject::connect(logout, SIGNAL(clicked()), UserFiles, SLOT(logOut()));
        QObject::connect(upload_btn, SIGNAL(clicked()), UserFiles, SLOT(uploadFile()));

        QMetaObject::connectSlotsByName(UserFiles);
    } // setupUi

    void retranslateUi(QWidget *UserFiles)
    {
        UserFiles->setWindowTitle(QApplication::translate("UserFiles", "Form", 0));
        label->setText(QApplication::translate("UserFiles", "MyDropBox", 0));
        label_2->setText(QApplication::translate("UserFiles", "User  : ", 0));
        user_lbl->setText(QApplication::translate("UserFiles", "TextLabel", 0));
        logout->setText(QApplication::translate("UserFiles", "Log Out", 0));
        label_3->setText(QApplication::translate("UserFiles", "My Files", 0));
        upload_btn->setText(QApplication::translate("UserFiles", "Share new file", 0));
        label_4->setText(QApplication::translate("UserFiles", "Shared With Me", 0));
    } // retranslateUi

};

namespace Ui {
    class UserFiles: public Ui_UserFiles {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_USERFILES_H
