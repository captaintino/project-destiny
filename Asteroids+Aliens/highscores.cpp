#include <QDebug>
#include<QFile>
#include<ui_highscorewindow.h>
#include <highscores.h>

using namespace std;

//passes pointer to observer class
HighScores::HighScores(HighScoresObserver * win):observer(win)
{

}

//gets <userName> from the main window GUI
void HighScores::setUserName(const QString &username)
{
    this->username = username;
}

//saves the highscores to a file
void HighScores::save()
{
    this->evaluate();

    ofstream outfile;
    outfile.open("highscores.txt");

    if (!outfile)
    {
        ofstream outfile("highscores.txt");
    }

    for (unsigned int i = 0; i < scores.size(); i++)
        {
        outfile << usernames.at(i) /*"modifiedScore"*/ << " " << scores.at(i) << endl;
        }

    outfile.close();
}

//loads the highscores from a file
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

//displays the highscores in GUI
void HighScores::display()
{
    observer->updateHighScore(usernames,scores);
}

//determines where to place highscores in list
void HighScores::evaluate()
{
    bool erase = false;
    int score = universe->getScore();

    for(unsigned int i = 0; i < scores.size(); ++i)
    {
        if(score>scores.at(i))
        {
            scores.insert(scores.begin() + i,score);
            usernames.insert(usernames.begin() + i,this->username.toStdString());
            erase = true;
            break;
        }
    }

    if(erase==true)
    {
        scores.erase(scores.begin()+5);
        usernames.erase(usernames.begin()+5);
    }
}

//retrieves Universe pointer
void HighScores::setUniverse(Universe * uni)
{
    universe = uni;
}
