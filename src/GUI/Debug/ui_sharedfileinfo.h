/********************************************************************************
** Form generated from reading UI file 'sharedfileinfo.ui'
**
** Created by: Qt User Interface Compiler version 5.4.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SHAREDFILEINFO_H
#define UI_SHAREDFILEINFO_H

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

class Ui_SharedFileInfo
{
public:
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QPushButton *download_btn;
    QPushButton *ok_btn;
    QLabel *fileName;
    QLabel *share_lbl;

    void setupUi(QWidget *SharedFileInfo)
    {
        if (SharedFileInfo->objectName().isEmpty())
            SharedFileInfo->setObjectName(QStringLiteral("SharedFileInfo"));
        SharedFileInfo->resize(341, 128);
        horizontalLayoutWidget = new QWidget(SharedFileInfo);
        horizontalLayoutWidget->setObjectName(QStringLiteral("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(10, 90, 321, 31));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        download_btn = new QPushButton(horizontalLayoutWidget);
        download_btn->setObjectName(QStringLiteral("download_btn"));

        horizontalLayout->addWidget(download_btn);

        ok_btn = new QPushButton(horizontalLayoutWidget);
        ok_btn->setObjectName(QStringLiteral("ok_btn"));

        horizontalLayout->addWidget(ok_btn);

        fileName = new QLabel(SharedFileInfo);
        fileName->setObjectName(QStringLiteral("fileName"));
        fileName->setGeometry(QRect(10, 10, 151, 31));
        QFont font;
        font.setFamily(QStringLiteral("Padauk"));
        font.setPointSize(14);
        font.setBold(true);
        font.setWeight(75);
        fileName->setFont(font);
        share_lbl = new QLabel(SharedFileInfo);
        share_lbl->setObjectName(QStringLiteral("share_lbl"));
        share_lbl->setGeometry(QRect(10, 40, 301, 17));
        QFont font1;
        font1.setFamily(QStringLiteral("Padauk"));
        font1.setPointSize(13);
        share_lbl->setFont(font1);

        retranslateUi(SharedFileInfo);
        QObject::connect(download_btn, SIGNAL(clicked()), SharedFileInfo, SLOT(onDownloadPress()));
        QObject::connect(ok_btn, SIGNAL(clicked()), SharedFileInfo, SLOT(onOKPress()));

        QMetaObject::connectSlotsByName(SharedFileInfo);
    } // setupUi

    void retranslateUi(QWidget *SharedFileInfo)
    {
        SharedFileInfo->setWindowTitle(QApplication::translate("SharedFileInfo", "Form", 0));
        download_btn->setText(QApplication::translate("SharedFileInfo", "Download", 0));
        ok_btn->setText(QApplication::translate("SharedFileInfo", "OK", 0));
        fileName->setText(QApplication::translate("SharedFileInfo", "TextLabel", 0));
        share_lbl->setText(QApplication::translate("SharedFileInfo", "TextLabel", 0));
    } // retranslateUi

};

namespace Ui {
    class SharedFileInfo: public Ui_SharedFileInfo {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SHAREDFILEINFO_H
