#include "clientwindow.h"
#include "ui_clientwindow.h"
#include <QDebug>
#include<mainwindow.h>

ClientWindow::ClientWindow(QWidget *main, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ClientWindow),
    userName("Player"),
    mainwindow(main)
{
    ui->setupUi(this);
}

ClientWindow::~ClientWindow()
{
    delete ui;
}

void ClientWindow::on_btnClientWinConnect_clicked()
{
    serverUpdate();
}

//display other players' info in GUI
void ClientWindow::dataReceived()
{
    QString data;

    while (socket->canReadLine()){
        data = socket->readLine();

        if(data.startsWith("CHAT")){
            data.chop(1);
            ui->chatMessages->appendPlainText(data.toStdString().substr(4, data.size() - 2).c_str());
        }
        else if(data.startsWith("REFR")){
            for (unsigned int i = 0; i<labelList.size();i++)
            {
                labelList.at(i)->setShown(false);
                labelList.at(i)->deleteLater();
            }
            labelList.clear();
            stringstream buffer;
            int numUsers = 0;
            string username;
            int score = 0;
            string state;
            int level = 0;
            QLabel * label;

            buffer << data.toStdString().substr(4);

            buffer>>numUsers;
            int y = 90;

            for (int i = 0;i<numUsers;i++)
            {
                buffer>>username>>score>>state>>level;

                label = new QLabel(this);
                label->setText(QString::fromStdString(username));
                label->setGeometry(30,y,66,17);
                label->setStyleSheet("color:rgb(217, 217, 217)");
                label->show();
                labelList.push_back(label);

                label = new QLabel(this);
                label->setText(QString::number(score));
                label->setGeometry(130,y,66,17);
                label->setStyleSheet("color:rgb(217, 217, 217)");
                label->show();
                labelList.push_back(label);

                label = new QLabel(this);
                label->setText(QString::fromStdString(state));
                label->setGeometry(230,y,66,17);
                label->setStyleSheet("color:rgb(217, 217, 217)");
                label->show();
                labelList.push_back(label);

                label = new QLabel(this);
                label->setText(QString::number(level));
                label->setGeometry(330,y,66,17);
                label->setStyleSheet("color:rgb(217, 217, 217)");
                label->show();
                labelList.push_back(label);

                y+=30;
            }
        }
        else if(data.startsWith("ROUN")){
            //Allow user to start new game
            dynamic_cast<MainWindow*>(mainwindow)->lockStartButton(true);
        }
    }
}

//delete socket, send disconnected signal, disable <btnClientWinConnect> and <btnRefresh>
void ClientWindow::serverDisconnected()
{
    socket->deleteLater();
    emit disconnected();
    ui->btnClientWinConnect->setEnabled(true);
    ui->btnRefresh->setEnabled(false);
    ui->chatMessages->setEnabled(false);
    dynamic_cast<MainWindow*>(mainwindow)->lockStartButton(true);
}

//Updates server with current information
void ClientWindow::serverUpdate()
{
    QString hostname;
    userName = ui->lnUserName->text();
    if(ui->lnHostName->text() != "")
        hostname = ui->lnHostName->text();
    else
        hostname = "localhost";
    socket = new QTcpSocket(this);

    socket->connectToHost(hostname, 5000);
    if (!socket->waitForConnected())  {
        QMessageBox::critical(this, "Uh oh", "Unable to connect to server.");
        return;
    }
    connect(socket, SIGNAL(readyRead()), this, SLOT(dataReceived()));
    connect(socket, SIGNAL(disconnected()), this, SLOT(serverDisconnected()));
    emit connected();
    ui->btnClientWinConnect->setEnabled(false);
    ui->btnRefresh->setEnabled(true);
    ui->chatMessages->setEnabled(true);

    QString data = QString("UPDATE ") + userName + " 0 alive 1\n";
    qDebug() << "Sending " << data.toStdString().c_str();       // When this goes away, we can eliminate the QString <data>
    socket->write(data.toStdString().c_str());

    clientRefresh();
}

//updates client with current information from server
void ClientWindow::clientRefresh()
{
    if(socket==NULL||socket->state() == QAbstractSocket::UnconnectedState)
    {
        return;
    }
    socket->write("REFR\n");
}

//send user status in the game
void ClientWindow::sendUpdate(bool aliveOrDead)
{
    QString aOrD;
    if(aliveOrDead){
        aOrD = " alive";
    }else{
        aOrD = " dead";
    }
    QString data = QString("UPDATE ") + userName + " " + QString::number(universe->getScore()) + aOrD + " " + QString::number(universe->getLevel()) + '\n';
    qDebug() << "Sending " << data.toStdString().c_str();       // When this goes away, we can eliminate the QString <data>
    socket->write(data.toStdString().c_str());
}


void ClientWindow::on_btnRefresh_clicked()
{
    clientRefresh();
}

void ClientWindow::on_btnBackToMenu_clicked()
{
    this->close();
}

void ClientWindow::on_SendMessage_clicked()
{
    if(socket==NULL||socket->state() == QAbstractSocket::UnconnectedState)
    {
        return;
    }
    socket->write(("CHAT" + ui->chatMessageToSend->text().toStdString() + '\n').c_str());
}
