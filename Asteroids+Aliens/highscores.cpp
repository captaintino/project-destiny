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
            outfile << usernames.at(i) << " " << scores.at(i) << endl;
        }

    outfile.close();
}

void HighScores::load()
{
    ifstream infile("highscores.txt");
    stringstream buffer;

    if (infile)
    {
        buffer << infile.rdbuf();
        infile.close();
    }

    for(int i=0; i<scores.size(); i++)
    {
        buffer>>scores.at(i);
        buffer>>usernames.at(i);
    }
}

void HighScores::display()
{
    observer->updateHighScore(usernames,scores);
}

void HighScores::evaluate()
{
    bool erase = true;
    int score = universe->getScore();
    string username;

    if(score>scores.at(0))
    {
        scores.insert(scores.begin(),score);
        usernames.insert(usernames.begin(),username);
    }
    else if(score <scores.at(0) && score >scores.at(1))
    {
        scores.insert(scores.begin() + 1,score);
        usernames.insert(usernames.begin() + 1,username);
    }
    else if(score <scores.at(0) && score <scores.at(1) && score >scores.at(2))
    {
        scores.insert(scores.begin() + 2,score);
        usernames.insert(usernames.begin() + 2,username);
    }
    else if(score <scores.at(0) && score <scores.at(1) && score <scores.at(2) &&
             score >scores.at(3))
    {
        scores.insert(scores.begin() + 3,score);
        usernames.insert(usernames.begin() + 3,username);
    }
    else if(score <scores.at(0) && score <scores.at(1) && score <scores.at(2) &&
            score <scores.at(3) && score >scores.at(4))
    {
        scores.insert(scores.begin() + 4,score);
        usernames.insert(usernames.begin() + 4,username);
    }
    else
    {
        erase = false;
    }

    if(erase=true)
    {
        scores.erase(scores.begin()+5);
        usernames.erase(usernames.begin()+5);
    }
}

void HighScores::setUniverse(Universe * uni)
{
    universe = uni;
}
