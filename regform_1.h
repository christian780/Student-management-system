#ifndef REGFORM_1_H
#define REGFORM_1_H

#include <QWidget>

namespace Ui {
class regForm_1;
}

class regForm_1 : public QWidget
{
    Q_OBJECT

public:
    explicit regForm_1(QWidget *parent = nullptr);
    ~regForm_1();

private slots:
    void on_comboBox_activated(int index);

private:
    Ui::regForm_1 *ui;
};

#endif // REGFORM_1_H
