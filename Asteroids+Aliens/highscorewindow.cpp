#include "highscorewindow.h"
#include "ui_highscorewindow.h"

HighScoreWindow::HighScoreWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HighScoreWindow)
{
    ui->setupUi(this);
    ui->lblHighScoreContent->setText("high score");
}

HighScoreWindow::~HighScoreWindow()
{
    delete ui;
}

void HighScoreWindow::on_btnBackToMainMenu_clicked()
{
    this->close();
}
