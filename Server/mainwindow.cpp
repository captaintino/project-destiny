#include <QMessageBox>
#include <QDateTime>
#include <QTcpSocket>
#include <QDebug>
#include <sstream>

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    connectCount(0)
{
    ui->setupUi(this);
    connect(&server, SIGNAL(newConnection()), this, SLOT(clientConnected()));
    if (!server.listen(QHostAddress::Any, 5000)) {
        QMessageBox::critical(this, "Uh oh", "Cannot start socket.");
        exit(1);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::addToLog(QString msg)
{
    QDateTime now = QDateTime::currentDateTime();
    ui->txtLog->appendPlainText(now.toString("hh:mm:ss") + " " + msg);
}

void MainWindow::clientConnected()
{
    QTcpSocket *sock = server.nextPendingConnection();
    connect(sock, SIGNAL(disconnected()), this, SLOT(clientDisconnected()));
    connect(sock, SIGNAL(readyRead()), this, SLOT(dataReceived()));
    sockets.push_back(sock);
    users.push_back(new User());
    ++connectCount;
    ui->lblConnected->setText(QString::number(connectCount));
    addToLog("Client connected.");
}

void MainWindow::dataReceived()
{
    /*
    MySocket *sock;
    for (int i = 0; i < sockets.size(); ++i) {
        if (sockets.at(i) == sender()) {
            sock = sockets.at(i);
            break;
        }
    }
*/
    int loc = 0;
    QTcpSocket *sock = dynamic_cast<QTcpSocket *>(sender());

    for(int i = 0; i < sockets.size(); ++i){
        if(sockets.at(i) == sock){
            loc = i;
            break;
        }
    }

    addToLog("Received data from socket ");
    while (sock->canReadLine()) {
        QString qstr = sock->readLine().trimmed();

        addToLog("-> " + qstr);

        /*if (qstr.startsWith("*USER ")) {
            std::string str;
            std::stringstream ss(qstr.toStdString());
            ss >> str >> str;
            qstr = QString::fromStdString(str);
            sock->write("+OK\n");
            sock->setUsername(qstr);
        } else */ if (qstr.startsWith("REFR")) {
            QString output;
            for (int i = 0; i < sockets.size(); ++i) {
                User * user = users.at(loc);
                output += user->getUsername() + " ";
                output += user->getScore() + " ";
                if (user->getAlive()) {
                    output += "A ";
                } else {
                    output += "D ";
                }
                output += user->getLevel() + "\n";
            }
            sock->write(output.toAscii());
        } else if (qstr.startsWith("UPDATE ")) {
            std::string str;
            User * user = users.at(loc);
            std::stringstream ss(qstr.toStdString());
            ss >> str >> str;
            qstr = QString::fromStdString(str);
            user->setUsername(qstr);
            ss >> str;
            qstr = QString::fromStdString(str);
            user->setScore(qstr.toInt());
            ss >> str;
            qstr = QString::fromStdString(str);
            if (qstr == "alive") {
                user->setAlive(true);
            } else if (qstr == "dead") {
                user->setAlive(false);
            }
            ss >> str;
            qstr = QString::fromStdString(str);
            user->setLevel(qstr.toInt());
            QString output;
            output = user->getUsername();
            output += " Level:" + user->getLevel();
            output += " Score:" + user->getScore();
            if (user->getAlive()) {
                output += " A";
            } else {
                output += " D\n";
            }
            addToLog(output);
        }

        }
   // }
}

void MainWindow::clientDisconnected()
{
    QTcpSocket *sock = dynamic_cast<QTcpSocket*>(sender());
    sock->deleteLater();
    --connectCount;
    ui->lblConnected->setText(QString::number(connectCount));
    addToLog("Client disconnected.");
}
