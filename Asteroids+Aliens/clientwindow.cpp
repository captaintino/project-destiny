#include "clientwindow.h"
#include "ui_clientwindow.h"

ClientWindow::ClientWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ClientWindow)
{
    ui->setupUi(this);
    userName = "Player";
}

ClientWindow::~ClientWindow()
{
    delete ui;
}

void ClientWindow::on_btnClientWinConnect_clicked()
{
    serverUpdate();
}

void ClientWindow::dataReceived()
{
    for (int i = 0; i<labelList.size();i++)
    {
        labelList.at(i)->setShown(false);
        labelList.at(i)->deleteLater();
    }
    labelList.clear();

    QString data;
    stringstream buffer;
    int numUsers = 0;
    string username;
    int score = 0;
    string state;
    int level = 0;
    QLabel * label;

    while (socket->canReadLine()){
    data += socket->readLine();

    buffer << data.toStdString();

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
                                                            //CHAT STUFF

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
}

void ClientWindow::serverDisconnected()
{

     //ui->statusBar->showMessage("Disconnected.");         //CHAT STUFF
     //ui->btnConnect->setEnabled(true);
     //ui->btnSend->setEnabled(false);
     socket->deleteLater();
     emit disconnected();
     ui->btnClientWinConnect->setEnabled(true);
     ui->btnRefresh->setEnabled(false);
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
    QString score = "0";
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

    QString data = QString("UPDATE ") + userName + " " + score + " alive 1\n";
    qDebug() << "Sending " << data.toStdString().c_str();
    socket->write(data.toStdString().c_str());

    clientRefresh();
}

//Refreshes client with current information
void ClientWindow::clientRefresh()
{
    /*ui->statusBar->showMessage("Connected.");         //CHAT STUFF
    ui->btnConnect->setEnabled(false);
    ui->btnSend->setEnabled(true);
    ui->txtMessage->setFocus();*/

    if(socket==NULL||socket->state() == QAbstractSocket::UnconnectedState)
    {
        return;
    }
    socket->write("REFRESH\n");

}

void ClientWindow::sendUpdate(bool aliveOrDead)
{
    QString aOrD;
    if(aliveOrDead){
        aOrD = " alive";
    }else{
        aOrD = " dead";
    }
    QString score = QString::number(universe->getScore());
    QString data = QString("UPDATE ") + userName + " " + score + aOrD + " " + QString::number(universe->getLevel()) + '\n';
    qDebug() << "Sending " << data.toStdString().c_str();
    socket->write(data.toStdString().c_str());
}

/*void ClientWindow::on_btnSend_clicked()               //CHAT STUFF
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

void ClientWindow::on_btnRefresh_clicked()
{
    clientRefresh();
}

void ClientWindow::on_btnBackToMenu_clicked()
{
    this->close();
}
