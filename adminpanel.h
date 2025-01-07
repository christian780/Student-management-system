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



    void on_staffcard_clicked();

    void on_actionCreate_Account_triggered();

    void on_actionCreate_triggered();

    void on_actionTimetable_triggered();

    void on_actionClose_triggered();

    void on_actionLogout_triggered();

private:
    Ui::Adminpanel *ui;
    bool loggedOut = false;
};

#endif // ADMINPANEL_H
