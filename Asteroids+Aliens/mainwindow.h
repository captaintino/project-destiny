#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include<QThread>
#include <QWidget>
#include <QTimer>
#include<universe.h>
#include <ship_label.h>
#include<on_screen_object.h>
#include<universethread.h>
#include <instructionwindow.h>
#include<highscorewindow.h>
#include <QKeyEvent>
#include<highscores.h>
#include <clientwindow.h>

namespace Ui {
class MainWindow;
}

class HighScoresObserver;

class MainWindow : public QWidget
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void mousePressEvent(QMouseEvent *ev);
    void mainMenuSetShow(bool m);
    void accelerateBackground();
private slots:
    void on_btnStart_clicked();
    void rotateBackground();
    void update_positions();
    void levelEnd();
    void userShipCrashed();
    void makeProjectile();
    void makeObject(); // Working on this

    void deleteLabel();
    void levelFinished();
    void resumeLevel();
    void on_btnInstructions_clicked();
    void on_btnHighScores_clicked();

    void on_btnCheat_clicked();

    void on_btnMultiplayer_clicked();

    void on_btnLoad_clicked();

    void keyPressEvent(QKeyEvent *e);

    void on_lnUsername_editingFinished();

    void connectedMultiplayer();
    void disconnectedMultiplayer();

    void canFire();

    void osuCreationSlot();
    void removeLevelLabel();

private:
    Ui::MainWindow *ui;
    QTimer * backgroundTimer, *updateTimer, *levelTimer, *fireShot;
    Universe * universe;
    Ship_Label * user;
    int background_counter, level;
    UniverseThread * modelUpdater;
    vector<on_screen_object *> objects, projectiles, user_projectiles;
    QThread * itemSpawn;
    HighScoreWindow highScoreWindow;
    InstructionWindow instructionWindow;
    QLabel * the_Score, * the_Level;
    HighScores * highscores;
    bool cheat, multiplayer, fire, networked, freeze_game;
    ClientWindow clientWindow;
    QString userName;
};

#endif // MAINWINDOW_H
