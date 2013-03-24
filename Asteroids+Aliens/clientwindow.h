#ifndef CLIENTWINDOW_H
#define CLIENTWINDOW_H

#include <ui_clientwindow.h>
#include <universe.h>

#include <QMessageBox>
#include <QDebug>
#include <QWidget>
#include <QString>
#include <QTcpSocket>
#include <QLabel>
#include <sstream>
#include <string>
#include <vector>

using namespace std;


namespace Ui {
class ClientWindow;
}

class ClientWindow : public QWidget
{
    Q_OBJECT

public:
    explicit ClientWindow(QWidget *parent = 0);
    ~ClientWindow();
    void serverUpdate();
    void clientRefresh();

private slots:
    void on_btnClientWinConnect_clicked();
    void dataReceived();//QTcpSocket *socket);
    void serverDisconnected();//QTcpSocket * socket);

    //void on_btnSend_clicked();

    void on_btnRefresh_clicked();

private:
    Ui::ClientWindow *ui;
    Universe *universe;
    vector<QLabel*>labelList;
    QTcpSocket * socket;
};

#endif // CLIENTWINDOW_H

