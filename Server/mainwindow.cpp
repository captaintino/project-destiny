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

void MainWindow::endRound()
{
    addToLog(("Round Over " + users.at(0)->getUsername().toStdString() + " won").c_str());
    users.at(0)->incrementRoundsWon();
    for(User * us: users){
        us->setAlive(true);
        us->setScore(0);
        us->setLevel(1);
        //Alert everyone that the round ended, who won, and tell the client to refresh
        us->getSocket()->write(("CHATADMIN: " + users.at(0)->getUsername().toStdString() + " has won the round\nROUN\n").c_str());
    }
    for(User * us: users){
        writeRefresh(us->getSocket());
    }
}

void MainWindow::writeRefresh(QTcpSocket * sock)
{
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

void MainWindow::addToAdminLog(QString msg)
{
    ui->adminLog->appendPlainText(msg);
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
            writeRefresh(sock);
        } else if (qstr.startsWith("UPDATE ")) {
            bool roundOver = false;
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
                roundOver = true;
                for (User * us : users){ // is everyone dead?
                    if(us->getAlive()){
                        roundOver = false;  // if Someone is alive, round is not over
                        break;}
                }
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
            // Everyone is dead
            if(roundOver){
                endRound();
            }
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
    bool roundOver = true;
    for (User * us : users){ // is everyone dead?
        if(us->getAlive()){
            roundOver = false;  // if Someone is alive, round is not over
            break;}
    }
    if(roundOver){
        endRound();
    }
}

void MainWindow::on_administrate_clicked()
{
    QString command = ui->adminCommands->text();
    if(command.length() > 0){
        if(command.startsWith('/')){
            if(command.startsWith("/users")){
                addToAdminLog("Users:");
                for(User * us: users){
                    addToAdminLog(us->getUsername() + " Score: " + QString::number(us->getScore()) + " " + (us->getAlive() ? "Alive" : "Dead") + " Level: " + QString::number(us->getLevel()) + " Rounds won: " + QString::number(us->getRoundsWon()));
                }
                addToAdminLog("");
            }else if(command.startsWith("/user")){
                command = command.remove(0,5).trimmed();
                for (unsigned int i = 0; i < users.size(); ++i) {
                    if(users.at(i)->getUsername() == command){
                        addToAdminLog(users.at(i)->getUsername() + " Score: " + QString::number(users.at(i)->getScore()) + " " + (users.at(i)->getAlive() ? "Alive" : "Dead") + " Level: " + QString::number(users.at(i)->getLevel()) + " Rounds won: " + QString::number(users.at(i)->getRoundsWon()));
                        break;
                    }
                }
            }else if(command.startsWith("/kick")){
                command = command.remove(0,5).trimmed();
                for (unsigned int i = 0; i < users.size(); ++i) {
                    if(users.at(i)->getUsername() == command){
                        addToAdminLog("Kicked " + users.at(i)->getUsername());
                        delete users.at(i);
                        users.erase(users.begin() + i);
                        for(User * us: users){
                            us->getSocket()->write(("CHATADMIN kicked " + command.toStdString() + '\n').c_str());
                        }
                        bool roundOver = true;
                        for (User * us : users){ // is everyone dead?
                            if(us->getAlive()){
                                roundOver = false;  // if Someone is alive, round is not over
                                break;}
                        }
                        if(roundOver){
                            endRound();
                        }
                        break;
                    }
                }
            }else if(command.startsWith("/")){

            }else if(command.startsWith("/")){

            }
        }else{
            addToLog(("CHATADMIN: " + command.toStdString() + '\n').c_str());
            for(User * us: users){
                us->getSocket()->write(("CHATADMIN: " + command.toStdString() + '\n').c_str());
            }
        }
    }
}
