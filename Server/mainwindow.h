#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpServer>
#include <QTcpSocket>
#include <vector>

namespace Ui {
class MainWindow;
}

class User {
    QString username;
    int level, score;
    bool alive;
    QTcpSocket *socket;

public:
    User(QTcpSocket * sock) : socket(sock) {
        username = "User";
        level = 1;
        score = 0;
        alive = true;
    }

    ~User() {
        socket->deleteLater();
    }

    void setUsername(QString newUser) { username = newUser; }
    void setLevel(int newLevel) { level = newLevel; }
    void setScore(int newScore) { score = newScore; }
    void setAlive(bool newAlive) { alive = newAlive; }

    QString getUsername() { return username; }
    int getLevel() { return level; }
    int getScore() { return score; }
    bool getAlive() { return alive; }
    QTcpSocket * getSocket() { return socket; }

};

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void addToLog(QString msg);
    static bool sortUserByScore(User * a, User * b);
    void sortUsers();

private slots:
    void clientConnected();
    void dataReceived();
    void clientDisconnected();

private:
    Ui::MainWindow *ui;

    QTcpServer server;
    int connectCount;

    std::vector<User *> users;
};

#endif // MAINWINDOW_H
