#ifndef HIGHSCORES_H
#define HIGHSCORES_H

#include <vector>
#include <string>

class HighScores
{
std::vector<std::string> usernames;
std::vector<int> scores;

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
