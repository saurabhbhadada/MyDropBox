/********************************************************************************
** Form generated from reading UI file 'listwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.4.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LISTWIDGET_H
#define UI_LISTWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_listWidget
{
public:
    QLabel *fileName;

    void setupUi(QWidget *listWidget)
    {
        if (listWidget->objectName().isEmpty())
            listWidget->setObjectName(QStringLiteral("listWidget"));
        listWidget->resize(320, 33);
        QFont font;
        font.setFamily(QStringLiteral("Padauk"));
        font.setPointSize(13);
        listWidget->setFont(font);
        listWidget->setAutoFillBackground(false);
        fileName = new QLabel(listWidget);
        fileName->setObjectName(QStringLiteral("fileName"));
        fileName->setGeometry(QRect(0, 0, 321, 31));

        retranslateUi(listWidget);

        QMetaObject::connectSlotsByName(listWidget);
    } // setupUi

    void retranslateUi(QWidget *listWidget)
    {
        listWidget->setWindowTitle(QApplication::translate("listWidget", "Form", 0));
        fileName->setText(QApplication::translate("listWidget", "TextLabel", 0));
    } // retranslateUi

};

namespace Ui {
    class listWidget: public Ui_listWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LISTWIDGET_H
