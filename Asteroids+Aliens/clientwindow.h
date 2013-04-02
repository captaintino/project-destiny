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

    //send updated info to server
    void serverUpdate();

    //update client with new info from server
    void clientRefresh();

    //get username from main menu
    void updateUsername(QString user){userName = user; ui->lnUserName->setText(userName);}
    
    //send user status in game
    void sendUpdate(bool aliveOrDead);
    
    //get universe pointer from Universe
    void updateUniverse(Universe * uni){universe = uni;}

private slots:
    void on_btnClientWinConnect_clicked();

    //display other players' info in GUI
    void dataReceived();

    //delete socket, send disconnected signal, disable <btnClientWinConnect> and <btnRefresh>
    void serverDisconnected();
    void on_btnRefresh_clicked();
    void on_btnBackToMenu_clicked();

signals:
    void connected();
    void disconnected();

private:
    Ui::ClientWindow *ui;
    Universe *universe;
    vector<QLabel*>labelList;
    QTcpSocket * socket;
    QString userName;
};

#endif // CLIENTWINDOW_H

