#include <iostream>
#include <fstream>
#include <string>

#pragma once




class PlayerStats
{
    public:
        PlayerStats();
        PlayerStats(std::string* inname, std::string* inscore);
        PlayerStats(PlayerStats* inStat);
        ~PlayerStats();

        std::string getName(void);
        int getScore(void);
        void setScore(int newScore);
        void incrementScore(void);
        void decrementScore(void);

    private:
       std::string* playerName;
       int* score;
};


PlayerStats::PlayerStats()
{
    playerName = new std::string();
    score = new int();
}

PlayerStats::PlayerStats(std::string* inname, std::string* inscore)
{
    playerName = inname;
    score = new int(std::stoi( *inscore ));
}

PlayerStats::PlayerStats(PlayerStats* inStat)
{
    playerName = new std::string(*(inStat->playerName));
    score = new int(*(inStat->score));
}


PlayerStats::~PlayerStats()
{
    delete playerName;
    delete score;
}




std::string PlayerStats::getName(void)
{
    return *playerName;
}




int PlayerStats::getScore(void)
{
    return *score;
}




void PlayerStats::setScore(int newScore)
{
    delete score;
    score = new int(newScore);
}


void PlayerStats::incrementScore(void)
{
    *score = *score + 1;
}


void PlayerStats::decrementScore(void)
{
    *score = *score - 1;
}




std::ostream & operator << (std::ostream &stream, PlayerStats &data)
{
    stream << data.getName() << ": " << data.getScore() ;
    return stream;
}



std::ofstream & operator << (std::ofstream &stream, PlayerStats &data)
{
    stream << data.getName() << "," << data.getScore() << std::endl;
    return stream;
}