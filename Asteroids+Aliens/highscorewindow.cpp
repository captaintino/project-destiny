#include "highscorewindow.h"
#include "ui_highscorewindow.h"

HighScoreWindow::HighScoreWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HighScoreWindow)
{
    ui->setupUi(this);
}

HighScoreWindow::~HighScoreWindow()
{
    delete ui;
}

//pass <usernames> and <scores> to the GUI
void HighScoreWindow::updateHighScore(vector<string> &usernames, vector<int> &scores)
{
    ui->lblUsername1->setText(QString::fromStdString(usernames.at(0)));
    ui->lblUsername2->setText(QString::fromStdString(usernames.at(1)));
    ui->lblUsername3->setText(QString::fromStdString(usernames.at(2)));
    ui->lblUsername4->setText(QString::fromStdString(usernames.at(3)));
    ui->lblUsername5->setText(QString::fromStdString(usernames.at(4)));

    ui->lblScore1->setText(QString::number(scores.at(0)));
    ui->lblScore2->setText(QString::number(scores.at(1)));
    ui->lblScore3->setText(QString::number(scores.at(2)));
    ui->lblScore4->setText(QString::number(scores.at(3)));
    ui->lblScore5->setText(QString::number(scores.at(4)));


}

void HighScoreWindow::on_btnBackToMainMenu_clicked()
{
    this->close();
}
