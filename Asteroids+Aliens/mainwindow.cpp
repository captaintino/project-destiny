#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<universe.h>

MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_btnStart_clicked()
{
    ui->btnStart->setShown(false);
    ui->btnCheat->setShown(false);
    ui->btnHighScores->setShown(false);
    ui->btnLoad->setShown(false);
    this->cursor().setPos(380, 640);
    universe = new Universe(1);
}
