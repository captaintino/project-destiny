#ifndef HIGHSCORES_H
#define HIGHSCORES_H

#include <vector>
#include <string>

using namespace std;

class HighScores
{
//std::vector<string> usernames;
//std::vector<int> scores;
vector<HighScores> scoreList;
string username;
string score;

public:
    HighScores();

    //saves the high scores to a file
    void save();

    //loads the high scores from a file
    void load();

    //displays the high scores
    void display();
};

#endif // HIGHSCORES_H
