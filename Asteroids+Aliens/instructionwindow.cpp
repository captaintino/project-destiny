#include "instructionwindow.h"
#include "ui_instructionwindow.h"

InstructionWindow::InstructionWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::InstructionWindow)
{
    ui->setupUi(this);
}

InstructionWindow::~InstructionWindow()
{
    delete ui;
}

void InstructionWindow::on_btnCloseInstructions_clicked()
{
    this->close();
}
