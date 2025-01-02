#ifndef ADMINPANEL_H
#define ADMINPANEL_H

#include <QMainWindow>

namespace Ui {
class Adminpanel;
}

class Adminpanel : public QMainWindow
{
    Q_OBJECT

public:
    explicit Adminpanel(QWidget *parent = nullptr);
    ~Adminpanel();

private slots:
    void on_pushButton_clicked();



private:
    Ui::Adminpanel *ui;
};

#endif // ADMINPANEL_H
