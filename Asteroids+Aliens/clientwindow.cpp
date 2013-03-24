#include "clientwindow.h"
#include "ui_clientwindow.h"

ClientWindow::ClientWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ClientWindow)
{
    ui->setupUi(this);
}

ClientWindow::~ClientWindow()
{
    delete ui;
}

void ClientWindow::on_btnClientWinConnect_clicked()
{
    /*QString hostname = ui->lineChatServer->text();
    if (hostname.size() == 0) {
        QMessageBox::critical(this, "Uh oh", "Please specify name of chat server.");
        return;
    }*/
    QString hostname = "localhost";
    QString username = "bob";
    QString score = QString::number(universe->getScore());

    QTcpSocket * socket = new QTcpSocket();

    socket->connectToHost(hostname, 1010);
    if (!socket->waitForConnected())  {
        QMessageBox::critical(this, "Uh oh", "Unable to connect to server.");
        return;
    }

    QString data = QString("UPDATE ") + username + " " + score;
    qDebug() << "Sending " << data;
    socket->write(data.toStdString().c_str());

    // wait for response from server
    while (!socket->canReadLine() && socket->state() == QAbstractSocket::ConnectedState) {
        socket->waitForReadyRead();
    }

    if (socket->state() != QAbstractSocket::ConnectedState) {
        QMessageBox::warning(this, "Uh oh", "Server disconnected.");
        socket->deleteLater();
        return;
    }

    data = QString("REFRESH ");
    qDebug()<<"Sending"<<data;
    socket->write(data.toStdString().c_str());

    while (!socket->canReadLine() && socket->state() == QAbstractSocket::ConnectedState) {
        socket->waitForReadyRead();
    }

    if (socket->state() != QAbstractSocket::ConnectedState) {
        QMessageBox::warning(this, "Uh oh", "Server disconnected.");
        socket->deleteLater();
        return;
    }


    /*data = socket->readLine().trimmed();

    if (data != "+OK") {
        QMessageBox::warning(this, "Uh oh", "Username not valid.");
        socket->deleteLater();
        return;
    }

    data = QString("*PASS ") + ui->linePassword->text() + "\n";
    qDebug() << "Sending " << data;
    socket->write(data.toStdString().c_str());

    // wait for response from server
    while (!socket->canReadLine() && socket->state() == QAbstractSocket::ConnectedState) {
        socket->waitForReadyRead();
    }

    if (socket->state() != QAbstractSocket::ConnectedState) {
        QMessageBox::warning(this, "Uh oh", "Server disconnected.");
        socket->deleteLater();
        return;
    }

    data = socket->readLine().trimmed();
    if (data != "+OK") {
        QMessageBox::warning(this, "Uh oh", "Password not valid.");
        socket->deleteLater();
        return;
    }

    ui->statusBar->showMessage("Connected.");
    ui->btnConnect->setEnabled(false);
    ui->btnSend->setEnabled(true);
    ui->txtMessage->setFocus();*/

    connect(socket, SIGNAL(readyRead()), this, SLOT(dataReceived(QTcpSocket * socket)));
    connect(socket, SIGNAL(disconnected()), this, SLOT(serverDisconnected()));
    socket->write("REFRESH");
}

void ClientWindow::dataReceived(QTcpSocket * socket) {


    QString data;
    stringstream buffer;
    int numUsers = 0;
    string username;
    int score;
    string state;
    int level;    
    QLabel * label;


//    while (socket->canReadLine())
//      data += socket->readLine();

    buffer << "3 user1 100 Alive 2 user2 200 Dead 3 user3 50000 Alive 100"; //data.toStdString();

    buffer>>numUsers;
    int y = 90;

    for (int i;i<numUsers+1;i++)
    {
        buffer>>username>>score>>state>>level;

        label = new QLabel(this);
        label->setText(QString::fromStdString(username));
        label->setGeometry(30,y,66,17);
        labelList.push_back(label);

        label = new QLabel(this);
        label->setText(QString::number(score));
        label->setGeometry(130,y,66,17);
        labelList.push_back(label);

        label = new QLabel(this);
        label->setText(QString::fromStdString(state));
        label->setGeometry(230,y,66,17);
        labelList.push_back(label);

        label = new QLabel(this);
        label->setText(QString::number(level));
        label->setGeometry(330,y,66,17);
        labelList.push_back(label);

        y+=30;

    }

    for (int i = 0; i<labelList.size(); i++)
    {
        label->show();
    }



    //shove into stringstream
    //loop count
    //each time a user score alive/dead level

        /*QString username = "unknown";
        QString msg;

        // get username, text
        int colonPos = str.indexOf(':');
        if (colonPos >= 0) {
            username = str.left(colonPos);
            msg = str.mid(colonPos + 1);
        } else {
            msg = str;
        }

        ui->txtChat->insertHtml("<b>" + username + "</b>: " + msg + "<br><br>");
    }*/

}

void ClientWindow::serverDisconnected(QTcpSocket *socket)
{
     //ui->statusBar->showMessage("Disconnected.");
     //ui->btnConnect->setEnabled(true);
     //ui->btnSend->setEnabled(false);
     socket->deleteLater();
     for (int i; i<labelList.size();i++)
     {
         delete labelList.at(i);
     }
}

/*void ClientWindow::on_btnSend_clicked()
{
    QString username = ui->lineUsername->text();
    QString msg;
    if (username.size() > 0) {
        msg = username + ":" + ui->txtMessage->toPlainText() + "\n";
    } else {
        msg = ui->txtMessage->toPlainText() + "\n";
    }

    ui->txtMessage->document()->setPlainText("");

    socket->write(msg.toStdString().c_str());

    ui->txtMessage->setFocus();
}*/
