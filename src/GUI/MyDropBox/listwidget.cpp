#include "listwidget.h"
#include "ui_listwidget.h"

listWidget::listWidget(string text, int fileId, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::listWidget)
{
    ui->setupUi(this);
    ui->fileName->setText(QString::fromStdString(text));

    this->fileName = text;
    this->fileId = fileId;
}

listWidget::~listWidget()
{
    delete ui;
}
