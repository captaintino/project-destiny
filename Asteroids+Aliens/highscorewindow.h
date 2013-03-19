#ifndef HIGHSCOREWINDOW_H
#define HIGHSCOREWINDOW_H

#include <QWidget>
#include <highscores.h>

namespace Ui {
class HighScoreWindow;
}

class HighScoresObserver
{
    virtual void updateInstructions()=0;
};

class HighScoreWindow : public QWidget,public HighScoresObserver
{
    Q_OBJECT
    
public:
    explicit HighScoreWindow(QWidget *parent = 0);
    ~HighScoreWindow();
    void updateInstructions(){}
    
private slots:
    void on_btnBackToMainMenu_clicked();

private:
    Ui::HighScoreWindow *ui;
};




#endif // HIGHSCOREWINDOW_H
