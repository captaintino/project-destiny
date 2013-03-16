#ifndef HIGHSCOREWINDOW_H
#define HIGHSCOREWINDOW_H

#include <QWidget>

namespace Ui {
class HighScoreWindow;
}

class HighScoreWindow : public QWidget
{
    Q_OBJECT
    
public:
    explicit HighScoreWindow(QWidget *parent = 0);
    ~HighScoreWindow();
    
private slots:
    void on_btnBackToMainMenu_clicked();

private:
    Ui::HighScoreWindow *ui;
};

#endif // HIGHSCOREWINDOW_H
