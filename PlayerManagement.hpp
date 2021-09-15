#include "PlayerStats.hpp"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#pragma once




class PlayerManagement
{
    public:
        PlayerManagement();
        ~PlayerManagement();

        void selectPlayer(void);
        void newPlayer(void);

        std::string getName(void);
        PlayerStats **getPlayerArray(void);
        void incrementScore(void);
        void decrementScore(void);
        PlayerStats* getCurPlayer(void);

        void outputPlayerArray(std::ofstream &stream);

        void PRINT_DEBUG(void);

    private:
        void loadPlayerData(void);
        void inputPlayerData(std::string *newName, std::string * newScore);
        void inputPlayerData(PlayerStats* inPlayer);
        void shuffleArray(void);
        void initArray(void);
        void handleLine(std::string inData);
        
        void searchPlayer(std::string inname);
        void replacePlayer(std::string inname);

        PlayerStats *playersArray[100];
        PlayerStats *curPlayer;
        int playerCount;
};



PlayerManagement::PlayerManagement()
{
    playerCount = 0;
    initArray();
    loadPlayerData();
}



PlayerManagement::~PlayerManagement()
{
    for (int i = 0; i < playerCount; i++ )
    {
        delete playersArray[i];
    }
}


void PlayerManagement::PRINT_DEBUG(void)
{
    for (int i = 0; i < playerCount; i++)
    {
        std::cout << i + 1 << ")" << *playersArray[i] << std::endl;
    }
}


void PlayerManagement::loadPlayerData(void)
{
    std::ifstream infile;
    std::string instring;

    infile.open("profiles.csv");

    while (std::getline(infile, instring) && playerCount < 100)
    {        
        handleLine(instring);
    }
    infile.close();
}


void PlayerManagement::handleLine(std::string inData)
{
    std::istringstream lineStream(inData);
    
    std::string *newName = new std::string();
    std::string *newScore = new std::string();   
   
    std::getline(lineStream, *newName, ',');
    std::getline(lineStream, *newScore, '\n');

    inputPlayerData(newName, newScore);    
}


void PlayerManagement::inputPlayerData(std::string *newName, std::string * newScore)
{
    playerCount++;
    shuffleArray();
    playersArray[0] = new PlayerStats(newName, newScore);
}

void PlayerManagement::inputPlayerData(PlayerStats* inPlayer)
{
    playerCount++;
    shuffleArray();
    playersArray[0] = inPlayer;
}



void PlayerManagement::shuffleArray(void)
{
    for (int index = playerCount + 1; index > 0; index--)
    {
        PlayerStats* temp = playersArray[index - 1];
        playersArray[index - 1] = playersArray[index];
        playersArray[index] = temp;
    }
}



void PlayerManagement::initArray(void)
{
    for (int i = 0; i < 100; i++)
    {
        playersArray[i] = nullptr;
    }
}




void PlayerManagement::selectPlayer(void)
{
    std::cout << "Type in the name of the profile you would like to load" << std::endl;
    std::string inname;std::string getName(void);
    std::cin >> inname;

    searchPlayer(inname);
}


void PlayerManagement::newPlayer(void)
{
    std::cout << "Name?" << std::endl;
    std::string inname;std::string getName(void);
    std::cin >> inname;

    replacePlayer(inname);
}


void PlayerManagement::searchPlayer(std::string inname)
{
    curPlayer = new PlayerStats(new std::string(inname), new std::string("0"));
    bool found = false;
    for (int i = 0; i < playerCount; i++)
    {
        if (playersArray[i]->getName() == curPlayer->getName())
        {
            delete curPlayer;
            curPlayer = playersArray[i];
            found = true;
        }
    }
    if (found == false) { inputPlayerData(curPlayer); }  
}


void PlayerManagement::replacePlayer(std::string inname)
{
    curPlayer = new PlayerStats(new std::string(inname), new std::string("0"));
    bool found = false;
    for (int i = 0; i < playerCount; i++)
    {
        if (playersArray[i]->getName() == curPlayer->getName())
        {
            delete playersArray[i];
            playersArray[i] = curPlayer;
            found = true;
        }
    }
    if (found == false) { inputPlayerData(curPlayer); }  
}



std::string PlayerManagement::getName(void)
{
    return curPlayer->getName();
}



void PlayerManagement::incrementScore(void)
{
    curPlayer->incrementScore();
}


void PlayerManagement::decrementScore(void)
{
    curPlayer->decrementScore();
}



PlayerStats* PlayerManagement::getCurPlayer(void)
{
    return curPlayer;
}




PlayerStats** PlayerManagement::getPlayerArray(void)
{
    return playersArray;
}



void PlayerManagement::outputPlayerArray(std::ofstream &stream)
{
    int count = 0;
    while (playersArray[count] != nullptr)
    {
        stream << *playersArray[count];
        count++;
    }

}


// std::ofstream & operator << (std::ofstream &stream, PlayerStats* inArray[])
// {
//     int count = 0;
//     while (inArray[count] != nullptr)
//     {
//         stream << *inArray[count];
//         count++;
//     }
//     return stream;
// }