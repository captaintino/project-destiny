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

public:
    HighScores();

    //saves the high scores to a file
    void save();

    //loads the high scores from a file
    void load();

    //displays the high scores
    void display();

    //parses data from highscores.txt
    void evaluate();
};

#endif // HIGHSCORES_H

