#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include<QThread>
#include <QWidget>
#include <QTimer>
#include<universe.h>
#include <ship_label.h>
#include<on_screen_object.h>
#include <instructionwindow.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QWidget
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_btnStart_clicked();
    void rotateBackground();
    void update_positions();
    void userShipCrashed();

    void on_btnInstructions_clicked();

private:
    Ui::MainWindow *ui;
    QTimer * backgroundTimer, *updateTimer;
    Universe * universe;
    Ship_Label * user;
    int background_counter, level;
    QThread * itemSpawn;
    on_screen_object * objects[13];
    InstructionWindow instructionWindow;
};

#endif // MAINWINDOW_H
