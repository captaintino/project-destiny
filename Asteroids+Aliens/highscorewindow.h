#ifndef HIGHSCOREWINDOW_H
#define HIGHSCOREWINDOW_H

#include <vector>
#include <QWidget>
#include <highscores.h>

using namespace std;

namespace Ui {
class HighScoreWindow;
}

class HighScoresObserver
{
  public:
    //pass <usernames> and <scores> to the GUI
    virtual void updateHighScore(vector<string>&usernames,vector<int>&scores)=0;
};

class HighScoreWindow : public QWidget,public HighScoresObserver
{
    Q_OBJECT
    
public:
    explicit HighScoreWindow(QWidget *parent = 0);
    ~HighScoreWindow();

    //pass <usernames> and <scores> to the GUI
    void updateHighScore(vector<string>&usernames,vector<int>&scores);
    
private slots:
    void on_btnBackToMainMenu_clicked();

private:
    Ui::HighScoreWindow *ui;
};




#endif // HIGHSCOREWINDOW_H
