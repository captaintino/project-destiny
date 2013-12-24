#include <QMessageBox>
#include <QDateTime>
#include <QTcpSocket>
#include <QDebug>
#include <sstream>
#include <algorithm>

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

bool MainWindow::sortUserByScore(User * a, User * b){return (a->getScore() > b->getScore());}

void MainWindow::sortUsers()
{
    std::sort(users.begin(), users.end(), sortUserByScore);
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
    users.push_back(new User(sock));
    ++connectCount;
    ui->lblConnected->setText(QString::number(connectCount));
    addToLog("Client connected.");
}

void MainWindow::dataReceived()
{
    int loc = 0;
    QTcpSocket *sock = dynamic_cast<QTcpSocket *>(sender());

    for(unsigned int i = 0; i < users.size(); ++i){
        if(users.at(i)->getSocket() == sock){
            loc = i;
            break;
        }
    }

    addToLog("Received data from socket ");
    while (sock->canReadLine()) {
        QString qstr = sock->readLine().trimmed();

        addToLog("-> " + qstr);

        if (qstr.startsWith("CHAT")) {
            std::string str = "CHAT" + users.at(loc)->getUsername().toStdString() + ": " + qstr.toStdString().substr(4);
            for(unsigned int i = 0; i < users.size(); ++i){
                users.at(i)->getSocket()->write((str + '\n').c_str());
            }
        } else if (qstr.startsWith("REFR")) {
            QString output;
            for (unsigned int i = 0; i < users.size(); ++i) {
                User * user = users.at(i);
                output += user->getUsername() + " ";
                output += QString::number(user->getScore()) + " ";
                if (user->getAlive()) {
                    output += "A ";
                } else {
                    output += "D ";
                }
                output += QString::number(user->getLevel());
            }
            sock->write("REFR" + (QString::number(users.size()) + ' ' + output).toAscii() + '\n');
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
            output += " Level:" + QString::number(user->getLevel());
            output += " Score:" + QString::number(user->getScore());
            if (user->getAlive()) {
                output += " A\n";
            } else {
                output += " D\n";
            }
            addToLog(output);
            sortUsers();
        }
    }
}

void MainWindow::clientDisconnected()
{
    QTcpSocket *sock = dynamic_cast<QTcpSocket *>(sender());
    for (unsigned int i = 0; i < users.size(); ++i) {
        if(users.at(i)->getSocket() == sock){
            delete users.at(i);
            users.erase(users.begin() + i);
            break;
        }
    }
    --connectCount;
    ui->lblConnected->setText(QString::number(connectCount));
    addToLog("Client disconnected.");
}
