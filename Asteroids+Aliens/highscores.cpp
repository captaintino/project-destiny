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
    ofstream outfile("highscores.txt");

    if (!outfile)
    {
        cout<<"Unable to open file.";
        exit(1);
    }

    for (int i = 0; i < scoreList.size(); i++)
    {
        outfile << scoreList.at(i).username << ":" << scoreList.at(i).score << endl;

    }
}

void HighScores::load()
{
    ifstream infile("highscores.txt");

    if (!infile)
    {
        cout << "Unable to open file.";
        exit(1);
    }

    string line;
    while (infile)
    {
        getline(infile, line);
    }
}

void HighScores::display()
{

}

void HighScores::parseData(string dataString)
{
    string data;
    vector<string>dataList;
        int pos = 0;
        while (dataString.find(':') != -1)
        {
        pos = dataString.find(':');
        data = dataString.substr(0,pos);
        dataList.push_back(data);
        dataString = dataString.substr(pos+1);
        }
    data = dataString;
    dataList.push_back(data);

}
