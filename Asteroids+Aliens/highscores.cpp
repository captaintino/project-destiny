#include "highscores.h"
#include <fstream>
#include <iostream>
#include <string>
#include <QDebug>

using namespace std;

HighScores::HighScores()
{

}

void HighScores::save()
{
    ofstream savefile("highscore.txt");

    if (!savefile)
    {
        cout<<"Unable to open file.";
    }

    for (int i = 0; i < scoreList.size(); i++)
    {
        savefile << scoreList.at(i).username << ":" << scoreList.at(i).score << endl;

    }

    savefile.close();


}

void HighScores::load()
{

}

void HighScores::display()
{

}
