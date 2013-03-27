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

public:
    User() {
        username = "User";
        level = 1;
        score = 0;
        alive = true;
    }

    void setUsername(QString newUser) { username = newUser; }
    void setLevel(int newLevel) { level = newLevel; }
    void setScore(int newScore) { score = newScore; }
    void setAlive(bool newAlive) { alive = newAlive; }

    QString getUsername() { return username; }
    int getLevel() { return level; }
    int getScore() { return score; }
    bool getAlive() { return alive; }

};

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void addToLog(QString msg);

private slots:
    void clientConnected();
    void dataReceived();
    void clientDisconnected();

private:
    Ui::MainWindow *ui;

    QTcpServer server;
    int connectCount;

    std::vector<User *> users;
    std::vector<QTcpSocket *> sockets;
};

#endif // MAINWINDOW_H
