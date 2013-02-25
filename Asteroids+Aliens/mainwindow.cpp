#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<universe.h>
#include<QTimer>

MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setMouseTracking(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::connectWorldTimer(QTimer * t)
{
    connect(t, SIGNAL(timeout()), this, SLOT(worldClick()));
}



void MainWindow::on_btnStart_clicked()
{
    ui->btnStart->setShown(false);
    ui->btnCheat->setShown(false);
    ui->btnHighScores->setShown(false);
    ui->btnLoad->setShown(false);
    this->cursor().setPos(380, 540);
    universe = new Universe(this, 1);
}

void MainWindow::worldClick(){
    universe->move();
}
