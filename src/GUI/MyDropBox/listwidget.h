#ifndef LISTWIDGET_H
#define LISTWIDGET_H

#include <QWidget>
#include <string>

using namespace std;

namespace Ui {
class listWidget;
}

class listWidget : public QWidget
{
    Q_OBJECT

public:
    explicit listWidget(string text = "", int fileId = 0, QWidget *parent = 0);
    ~listWidget();
    string fileName;
    int fileId;

private:
    Ui::listWidget *ui;
};

#endif // LISTWIDGET_H
