#ifndef HIGHSCORES_H
#define HIGHSCORES_H
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <highscorewindow.h>
#include <universe.h>

#include <QString>

using namespace std;


class HighScoresObserver;

class HighScores
{
vector<string>usernames;
vector<int> scores;
Universe* universe;
HighScoresObserver* observer;
QString username;


public:
    HighScores(HighScoresObserver *win);
    //saves the high scores to a file
    void setUserName(const QString & username);
    void save();

    //loads the high scores from a file
    void load();

    //displays the high scores
    void display();

    //parses data from highscores.txt
    void evaluate();

    void setUniverse(Universe *uni);
};

#endif // HIGHSCORES_H

