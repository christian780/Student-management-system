#include "staffprofile.h"
#include "ui_staffprofile.h"

#include <QFileDialog>
#include <QPushButton>
#include <QLineEdit>
#include <QWidget>
#include <QMessageBox>
#include <QDialogButtonBox>
#include <QVBoxLayout>
#include <QFile>
#include <QDesktopServices>
#include <QUrl>

#include <QFormLayout>
#include <QLabel>
#include <QHBoxLayout>
#include <QTimer>




StaffProfile::StaffProfile(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::StaffProfile)
    , tcpSocket(new QTcpSocket(this))
{
    ui->setupUi(this);

    nameLabel = new QLabel(tr("Name:"));
    addressLabel = new QLabel(tr("Address:"));
    addressLabel->setAlignment(Qt::AlignLeft | Qt::AlignTop);
//    QLabel *statusLabel = new QLabel;

    nameEdit = new QLineEdit;
    addressEdit = new QTextEdit;
     ui->tabWidget->addTab(new QWidget, "Salary Scheme");
     addGenerateSlipButton();



    // Set the layout to the tab


//    addGenerateSlipButton(); // Add the button programmatically




    connect(ui->attach, &QPushButton::clicked, this, &StaffProfile::on_attach_clicked);
    setAttribute(Qt::WA_DeleteOnClose);

    ui->submit->setEnabled(false);

    connect(ui->firstname, &QLineEdit::textChanged, this, &StaffProfile::validateForm);
    connect(ui->lastname, &QLineEdit::textChanged, this, &StaffProfile::validateForm);
    connect(ui->mobile, &QLineEdit::textChanged, this, &StaffProfile::validateForm);
    connect(ui->StateComboBox, &QComboBox::currentTextChanged, this, &StaffProfile::validateForm);
    connect(ui->filePathEdit, &QLineEdit::textChanged, this, &StaffProfile::validateForm);
    connect(ui->desciplinetext, &QTextEdit::textChanged, this, &StaffProfile::enforceWordLimit);
/*    connect(generateSlipButton, &QPushButton::clicked, this, [this, statusLabel]() {
        onGenerateSlipButtonClicked(statusLabel);
    });
*/






}

StaffProfile::~StaffProfile()
{
    delete ui;
}





void StaffProfile::on_attach_clicked()
{
    QString filePath = QFileDialog::getOpenFileName(this, "Select File", QDir::homePath(), "Images (*.png *.jpg);;Documents (*.pdf *.docx)");

    if (!filePath.isEmpty()) {
         ui->filePathEdit->setText(filePath);
    }

    QFileInfo fileInfo(filePath);
    QString fileExtension = fileInfo.suffix().toLower();

    QStringList allowedFormats = { "pdf", "docx"};

    if (allowedFormats.contains(fileExtension)) {
        qDebug() << "Valid file selected:" << filePath;
        ui->filePathEdit->setText(filePath); // Assuming you have a QLineEdit for display
    } else {
        QMessageBox::warning(this, "Invalid File", "The selected file format is not supported.");
        qDebug() << "Invalid file format:" << fileExtension;
    }
}


void StaffProfile::validateForm() {
    // Check if required fields are not empty
    bool isFormValid = !ui->firstname->text().isEmpty() &&
                       !ui->lastname->text().isEmpty() &&
                       !ui->mobile->text().isEmpty() &&
                       ui->StateComboBox->currentText() != "Abia";
//        !ui->address->text().isEmpty() &&
//        !ui->city->text().isEmpty() &&
//        !ui->filePathEdit->text().isEmpty() &&
//        !ui->DOB->text.isEmpty(); // Example default text

    // Enable or disable the Submit button based on validation
    ui->submit->setEnabled(isFormValid);
}





void StaffProfile::enforceWordLimit()
{
    const int maxWords = 120;

    // Get the current text
    QString currentText = ui->desciplinetext->toPlainText();

    // Split text into words
    QStringList words = currentText.split(QRegularExpression("\\s+"), Qt::SkipEmptyParts);

    // Check if the word count exceeds the limit
    if (words.size() > maxWords)
    {
        // Truncate the text to the first maxWords
        QString truncatedText = words.mid(0, maxWords).join(" ");
        ui->desciplinetext->blockSignals(true); // Prevent recursive textChanged signal
        ui->desciplinetext->setPlainText(truncatedText);
        ui->desciplinetext->blockSignals(false);

        // Move the cursor to the end
        QTextCursor cursor = ui->desciplinetext->textCursor();
        cursor.movePosition(QTextCursor::End);
        ui->desciplinetext->setTextCursor(cursor);

        QMessageBox::warning(ui->desciplinetext, "Word Limit Exceeded",
                             QString("You can only enter up to %1 words.").arg(maxWords));

        qDebug() << "Word limit reached! Truncated to" << maxWords << "words.";
    }
}


/*
void enforceWordLimit(QTextEdit *textEdit, int maxWords = 120) {
    // Get the current text from the QTextEdit
    QString text = textEdit->toPlainText();

    // Split the text into words
    QStringList words = text.split(QRegularExpression("\\s+"), Qt::SkipEmptyParts);

    // Check if word count exceeds the limit
    if (words.size() > maxWords) {
        // Truncate to the first `maxWords` words
        QString truncatedText = words.mid(0, maxWords).join(" ");
        textEdit->blockSignals(true); // Prevent triggering textChanged again
        textEdit->setPlainText(truncatedText); // Set the truncated text
        textEdit->blockSignals(false);
        textEdit->moveCursor(QTextCursor::End); // Move cursor to the end




        // Optionally show a warning message
        QMessageBox::warning(textEdit, "Word Limit Exceeded",
                             QString("You can only enter up to %1 words.").arg(maxWords));
    }
}

*/


void StaffProfile::on_submit_clicked()
{



}


// Assuming 'ui' is your UI object.


/*
void StaffProfile::onGenerateSlipButtonClicked(QLabel *statusLabel) {
    // Set the message in the label
    statusLabel->setText("Salary Slip generation initiated!");

    // Establish a connection to the server
    QTcpSocket *tcpSocket = new QTcpSocket(this);
    tcpSocket->connectToHost(QHostAddress::LocalHost, 12345);

    // Check if the connection is established
    if (tcpSocket->waitForConnected(3000)) {
        // Send the GENERATE request
        QByteArray request = "GENERATE";
        tcpSocket->write(request);
        tcpSocket->flush();
        qDebug() << "Request sent:" << request;

        // Handle server response
        connect(tcpSocket, &QTcpSocket::readyRead, this, [tcpSocket, statusLabel]() {
            QByteArray response = tcpSocket->readAll();

            // Handle PDF size and data
            if (response.startsWith("PDF_SIZE:")) {
                int pdfSize = response.mid(9).toInt();
                qDebug() << "Receiving PDF of size:" << pdfSize;

                QFile pdfFile("received_salary_slip.pdf");
                if (pdfFile.open(QIODevice::WriteOnly)) {
                    pdfFile.write(response);
                    pdfFile.close();
                    qDebug() << "Salary slip saved as received_salary_slip.pdf";

                    // Notify the user
                    statusLabel->setText("Salary Slip saved locally!");
                }
            } else {
                qDebug() << "Server response:" << response;
                statusLabel->setText("Error: " + QString(response));
            }

            tcpSocket->disconnectFromHost();
        });

        // Handle connection errors
        connect(tcpSocket, &QTcpSocket::errorOccurred, this, [tcpSocket, statusLabel](QAbstractSocket::SocketError error) {
            qDebug() << "Socket error:" << tcpSocket->errorString();
            statusLabel->setText("Error: " + tcpSocket->errorString());
        });
    } else {
        qDebug() << "Unable to connect to server.";
        statusLabel->setText("Error: Unable to connect to server.");
    }
}

*/

// Assuming 'ui' is your UI object.
void StaffProfile::addGenerateSlipButton() {
    // Get the "Salary Scheme" tab from the QTabWidget
    QWidget *salarySchemeTab = ui->tabWidget->widget(2); // Assuming "Salary Scheme" is the third tab (index starts from 0)

    // Create a new QPushButton
    QPushButton *generateSlipButton = new QPushButton("Generate Slip", salarySchemeTab);
    generateSlipButton->setFixedSize(120, 40);

    // Set up a vertical layout (or append to an existing one if available)
    QVBoxLayout *layout = qobject_cast<QVBoxLayout *>(salarySchemeTab->layout());
    if (!layout) {
        layout = new QVBoxLayout(salarySchemeTab);

        salarySchemeTab->setLayout(layout);
    }

    // Add the button to the bottom of the layout
    layout->addStretch(); // Add space above the button
     layout->addWidget(generateSlipButton, 0, Qt::AlignCenter);


     // Create the Salary Form
     QWidget *salaryFormWidget = new QWidget(salarySchemeTab);
     QFormLayout *formLayout = new QFormLayout(salaryFormWidget);



     // Add form fields
     QLineEdit *staffName = new QLineEdit();
     staffName->setMaxLength(32767);
     QLineEdit *staffID = new QLineEdit();
     staffID->setMaxLength(32767);
     QLineEdit *basicSalary = new QLineEdit();
     basicSalary->setMaxLength(32767);
     QLineEdit *allowances = new QLineEdit();
     allowances->setMaxLength(32767);
     QLineEdit *netSalary = new QLineEdit();
     netSalary->setMaxLength(32767);
     QLineEdit *bank = new QLineEdit();
     bank->setMaxLength(32767);


     formLayout->addRow("Staff Name:", staffName);
     formLayout->addRow("Staff ID:", staffID);
     formLayout->addRow("Basic Salary:", basicSalary);
     formLayout->addRow("Allowances:", allowances);
     formLayout->addRow("bank", bank);

     // Add image upload
     QLabel *imageLabel = new QLabel();
     imageLabel->setFixedSize(100, 100);
     imageLabel->setStyleSheet("border: 1px solid black; background-color: lightgray;");

     QPushButton *uploadImageButton = new QPushButton("Upload Image");
     uploadImageButton->setFixedSize(120, 40);
     QHBoxLayout *imageLayout = new QHBoxLayout();
     imageLayout->addWidget(imageLabel);
     imageLayout->addWidget(uploadImageButton);
     formLayout->addRow("Staff Image:", imageLayout);

     // Add the salary form to the layout
     layout->addWidget(salaryFormWidget);

     // Add the "Generate Slip" button
//     QPushButton *generateSlipButton = new QPushButton("Generate Slip", salarySchemeTab);
     generateSlipButton->setFixedSize(120, 40);
     layout->addStretch(); // Add space above the button
     layout->addWidget(generateSlipButton, 0, Qt::AlignCenter);

     // Connect the upload button to its slot
     connect(uploadImageButton, &QPushButton::clicked, [imageLabel]() {
         QString filePath = QFileDialog::getOpenFileName(nullptr, "Upload Staff Image", "", "Images (*.png *.jpg *.jpeg)");
         if (!filePath.isEmpty()) {
             QPixmap pixmap(filePath);
             imageLabel->setPixmap(pixmap.scaled(imageLabel->size(), Qt::KeepAspectRatio));
         }
     });

     // Connect the "Generate Slip" button to its slot
     connect(generateSlipButton, &QPushButton::clicked, this, &StaffProfile::onGenerateSlipButtonClicked);


    // Connect the button to its slot
//    connect(generateSlipButton, &QPushButton::clicked, this, &StaffProfile::onGenerateSlipButtonClicked);
}

/*
void StaffProfile::onGenerateSlipButtonClicked() {
    QMessageBox::information(this, "Generate Slip", "Salary Slip generation initiated!");
    QLabel *statusLabel = new QLabel;
}
*/

void StaffProfile::onGenerateSlipButtonClicked() {
    // Create a QLabel for the status message
    QLabel *statusLabel = new QLabel("Salary Slip generation initiated!");

    // Customize the label appearance
    statusLabel->setStyleSheet("color: green; font-weight: bold; font-size: 14px;");
    statusLabel->setAlignment(Qt::AlignCenter);

    // Add the label to the "Salary Scheme" tab
    QWidget *salarySchemeTab = ui->tabWidget->widget(2); // Assuming this is the third tab
    QVBoxLayout *layout = qobject_cast<QVBoxLayout *>(salarySchemeTab->layout());
    if (!layout) {
        layout = new QVBoxLayout(salarySchemeTab);
        salarySchemeTab->setLayout(layout);
    }

    // Add the label above the "Generate Slip" button
    layout->insertWidget(layout->count() - 1, statusLabel); // Insert above the last widget (button)

    // Optional: Clear the label after a few seconds
    QTimer::singleShot(3000, [statusLabel]() {
        statusLabel->deleteLater();
    });
}

