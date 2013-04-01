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
    //passes pointer to observer class
    HighScores(HighScoresObserver *win);

    //gets <userName> from the main window GUI
    void setUserName(const QString & username);

    //saves the highscores to a file
    void save();

    //loads the highscores from a file
    void load();

    //displays the highscores
    void display();

    //determines where to place highscores in list
    void evaluate();

    //retrieves Universe pointer
    void setUniverse(Universe *uni);
};

#endif // HIGHSCORES_H

