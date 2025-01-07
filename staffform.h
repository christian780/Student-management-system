#ifndef STAFFFORM_H
#define STAFFFORM_H

#include <QDialog>

namespace Ui {
class staffform;
}

class staffform : public QDialog
{
    Q_OBJECT

public:
    explicit staffform(QWidget *parent = nullptr);
    ~staffform();

private:
    Ui::staffform *ui;
};

#endif // STAFFFORM_H
