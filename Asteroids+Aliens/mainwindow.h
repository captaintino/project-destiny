#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QTimer>
#include<universe.h>

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

private:
    Ui::MainWindow *ui;
    QTimer backgroundTimer;
    Universe * universe;
};

#endif // MAINWINDOW_H
