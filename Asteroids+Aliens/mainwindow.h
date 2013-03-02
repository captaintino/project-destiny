#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include<QThread>
#include <QWidget>
#include <QTimer>
#include<universe.h>
#include <ship_label.h>
#include<on_screen_object.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QWidget
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    // connect the World's timer object to the
    void connectWorldTimer(QTimer *t);

private slots:
    void on_btnStart_clicked();
    void worldClick();
    void rotateBackground();
    void spawnItems();

private:
    Ui::MainWindow *ui;
    QTimer * backgroundTimer;
    Universe * universe;
    Ship_Label * user;
    int background_counter, level;
    QThread * itemSpawn;
    on_screen_object * objects[13];
};

#endif // MAINWINDOW_H
