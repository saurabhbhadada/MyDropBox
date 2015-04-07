/********************************************************************************
** Form generated from reading UI file 'fileinfo.ui'
**
** Created by: Qt User Interface Compiler version 5.4.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FILEINFO_H
#define UI_FILEINFO_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FileInfo
{
public:
    QLabel *fileName;
    QLabel *share_lbl;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QPushButton *share_Btn;
    QPushButton *download_btn;
    QPushButton *ok_btn;

    void setupUi(QWidget *FileInfo)
    {
        if (FileInfo->objectName().isEmpty())
            FileInfo->setObjectName(QStringLiteral("FileInfo"));
        FileInfo->resize(341, 128);
        fileName = new QLabel(FileInfo);
        fileName->setObjectName(QStringLiteral("fileName"));
        fileName->setGeometry(QRect(10, 10, 151, 31));
        QFont font;
        font.setFamily(QStringLiteral("Padauk"));
        font.setPointSize(14);
        font.setBold(true);
        font.setWeight(75);
        fileName->setFont(font);
        share_lbl = new QLabel(FileInfo);
        share_lbl->setObjectName(QStringLiteral("share_lbl"));
        share_lbl->setGeometry(QRect(10, 40, 301, 17));
        QFont font1;
        font1.setFamily(QStringLiteral("Padauk"));
        font1.setPointSize(13);
        share_lbl->setFont(font1);
        horizontalLayoutWidget = new QWidget(FileInfo);
        horizontalLayoutWidget->setObjectName(QStringLiteral("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(10, 90, 321, 31));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        share_Btn = new QPushButton(horizontalLayoutWidget);
        share_Btn->setObjectName(QStringLiteral("share_Btn"));

        horizontalLayout->addWidget(share_Btn);

        download_btn = new QPushButton(horizontalLayoutWidget);
        download_btn->setObjectName(QStringLiteral("download_btn"));

        horizontalLayout->addWidget(download_btn);

        ok_btn = new QPushButton(horizontalLayoutWidget);
        ok_btn->setObjectName(QStringLiteral("ok_btn"));

        horizontalLayout->addWidget(ok_btn);


        retranslateUi(FileInfo);
        QObject::connect(ok_btn, SIGNAL(clicked()), FileInfo, SLOT(onOKPress()));
        QObject::connect(share_Btn, SIGNAL(clicked()), FileInfo, SLOT(onSharePress()));
        QObject::connect(download_btn, SIGNAL(clicked()), FileInfo, SLOT(onDownloadPress()));

        QMetaObject::connectSlotsByName(FileInfo);
    } // setupUi

    void retranslateUi(QWidget *FileInfo)
    {
        FileInfo->setWindowTitle(QApplication::translate("FileInfo", "Form", 0));
        fileName->setText(QApplication::translate("FileInfo", "TextLabel", 0));
        share_lbl->setText(QApplication::translate("FileInfo", "TextLabel", 0));
        share_Btn->setText(QApplication::translate("FileInfo", "Share", 0));
        download_btn->setText(QApplication::translate("FileInfo", "Download", 0));
        ok_btn->setText(QApplication::translate("FileInfo", "OK", 0));
    } // retranslateUi

};

namespace Ui {
    class FileInfo: public Ui_FileInfo {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FILEINFO_H
