#ifndef STAFFPROFILE_H
#define STAFFPROFILE_H

#include <QDialog>
#include <QLabel>
#include <QCheckBox>
#include <QLineEdit>
#include <QTableWidget>
#include <QTextEdit>
#include <QDialogButtonBox>
#include <QPushButton>
#include <QTcpSocket>


namespace Ui {
class StaffProfile;
class QPushButton;
}

class StaffProfile : public QDialog
{
    Q_OBJECT

public:
    explicit StaffProfile( QWidget *parent = nullptr);
    ~StaffProfile();


public slots:
//    void verify();


public:
    QList<QPair<QString, int> > orderItems();
    QString senderName() const;
    QString senderAddress() const;
    bool sendOffers();


private slots:

    void on_attach_clicked();
    void  validateForm();
    void enforceWordLimit();

    void on_submit_clicked();
    void addGenerateSlipButton();
//    void onGenerateSlipButtonClicked(QLabel *statusLabel);
//    void handleServerResponse();
 //   void requestSalarySlip();
    void onGenerateSlipButtonClicked();

private:
    Ui::StaffProfile *ui;
    void setupItemsTable();

    QLabel *nameLabel;
    QLabel *addressLabel;
    QCheckBox *offersCheckBox;
    QLineEdit *nameEdit;
    QStringList items;
    QTableWidget *itemsTable;
    QTextEdit *addressEdit;
    QDialogButtonBox *buttonBox;
    QPushButton *butn;
    QTcpSocket *tcpSocket = nullptr;
};

#endif // STAFFPROFILE_H
