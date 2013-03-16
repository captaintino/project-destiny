#ifndef INSTRUCTIONWINDOW_H
#define INSTRUCTIONWINDOW_H

#include <QWidget>

namespace Ui {
class InstructionWindow;
}

class InstructionWindow : public QWidget
{
    Q_OBJECT
    
public:
    explicit InstructionWindow(QWidget *parent = 0);
    ~InstructionWindow();
    
private slots:
    void on_btnCloseInstructions_clicked();

private:
    Ui::InstructionWindow *ui;
};

#endif // INSTRUCTIONWINDOW_H
