#ifndef SCHLSERVER_H
#define SCHLSERVER_H

#include <QObject>
#include <QWidget>

QT_BEGIN_NAMESPACE
class QLabel;
class QTcpServer;
QT_END_NAMESPACE

class schlserver : public QDialog
{


    Q_OBJECT

public:
    explicit schlserver(QWidget *parent = nullptr);

private slots:
    void sendFortune();

private:
    void initServer();

    QLabel *statusLabel = nullptr;
    QTcpServer *tcpServer = nullptr;
    QList<QString> fortunes;

};

#endif // SCHLSERVER_H
