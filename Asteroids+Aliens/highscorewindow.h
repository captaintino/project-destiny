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
    virtual void updateHighScore(vector<string>&usernames,vector<int>&scores)=0;
    virtual QString updateHighScoreUsername(QString username)=0;
};

class HighScoreWindow : public QWidget,public HighScoresObserver
{
    Q_OBJECT
    
public:
    explicit HighScoreWindow(QWidget *parent = 0);
    ~HighScoreWindow();
    void updateHighScore(vector<string>&usernames,vector<int>&scores);
    QString updateHighScoreUsername(QString username){}
    
private slots:
    void on_btnBackToMainMenu_clicked();

private:
    Ui::HighScoreWindow *ui;
};




#endif // HIGHSCOREWINDOW_H
