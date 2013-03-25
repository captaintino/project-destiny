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
    int score;
    string state;
    int level;    
    QLabel * label;

//  while (socket->canReadLine())  COMMENTED OUT FOR TESTING
//  data += socket->readLine();
//  buffer << data;

    buffer << "3 user1 100 Alive 2 user2 200 Dead 3 user3 50000 Alive 100"; //data.toStdString();

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

void ClientWindow::serverDisconnected()
{

     //ui->statusBar->showMessage("Disconnected.");         //CHAT STUFF
     //ui->btnConnect->setEnabled(true);
     //ui->btnSend->setEnabled(false);
     socket->deleteLater();
}

//Updates server with current information
void ClientWindow::serverUpdate()
{
    QString hostname = "localhost";
    QString username = "bob";
    QString score = QString::number(universe->getScore());

    socket = new QTcpSocket(this);

    socket->connectToHost(hostname, 5000);
    if (!socket->waitForConnected())  {
        QMessageBox::critical(this, "Uh oh", "Unable to connect to server.");
        return;
    }

    QString data = QString("UPDATE ") + username + " " + score + " alive" + " 1";
    qDebug() << "Sending " << data;
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
    connect(socket, SIGNAL(readyRead()), this, SLOT(dataReceived()));
    connect(socket, SIGNAL(disconnected()), this, SLOT(serverDisconnected()));
    socket->write("REFRESH");    

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
