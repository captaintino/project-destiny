#include <QDebug>
#include<QFile>

#include <highscores.h>

using namespace std;

HighScores::HighScores(HighScoresObserver * win):observer(win)
{

}

void HighScores::save()
{
    this->evaluate();

    ofstream outfile;
    outfile.open("highscores.txt");

    if (!outfile)
    {
        ofstream outfile("highscores.txt");
    }

    for (int i = 0; i < scores.size(); i++)
        {
        outfile << /*usernames.at(i)*/ "modifiedScore" << " " << scores.at(i) << endl;
        }

    outfile.close();
}

void HighScores::load()
{
    ifstream infile("highscores.txt");
    stringstream buffer;

    if (!infile)
    {
        ofstream outfile("highscores.txt");
        for (int i = 0; i < 5; i++)
                {
                outfile << "player" << " " << "0" << endl;
                }

            outfile.close();
            infile.open("highscores.txt");
    }
    buffer << infile.rdbuf();
    infile.close();

    int score = 0;
    string username = "";

    for(int i=0; i < 5; i++)
    {
        buffer>>username>>score;
        scores.push_back(score);
        usernames.push_back(username);
    }
}

void HighScores::display()
{
    observer->updateHighScore(usernames,scores);
}

void HighScores::evaluate()
{
    bool erase = false;
    int score = universe->getScore();
    string username;

    for(int i = 0; i < scores.size(); ++i)
    {
        if(score>scores.at(i))
        {
            scores.insert(scores.begin() + i,score);
            usernames.insert(usernames.begin() + i,username);
            erase = true;
            break;
        }
    }

/*
    if(score>scores.at(0))
    {
        scores.insert(scores.begin(),score);
        usernames.insert(usernames.begin(),username);
        erase = true;
    }
    else if(score >scores.at(1))
    {
        scores.insert(scores.begin() + 1,score);
        usernames.insert(usernames.begin() + 1,username);
        erase = true;
    }
    else if(score >scores.at(2))
    {
        scores.insert(scores.begin() + 2,score);
        usernames.insert(usernames.begin() + 2,username);
        erase = true;
    }
    else if(score >scores.at(3))
    {
        scores.insert(scores.begin() + 3,score);
        usernames.insert(usernames.begin() + 3,username);
        erase = true;
    }
    else if(score >scores.at(4))
    {
        scores.insert(scores.begin() + 4,score);
        usernames.insert(usernames.begin() + 4,username);
        erase = true;
    }*/

    if(erase==true)
    {
        scores.erase(scores.begin()+5);
        usernames.erase(usernames.begin()+5);
    }
}

void HighScores::setUniverse(Universe * uni)
{
    universe = uni;
}
