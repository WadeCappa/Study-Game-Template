

#include "LinkedList.hpp"
#include "ListNode.hpp"
#include "LinuxData.hpp"
#include "PlayerManagement.hpp"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <limits>

#pragma once



class GameManagement
{
    public:
        GameManagement(void);
        ~GameManagement(void);

        void loadGameList(void);

        void commitAction(int input);

    private:
        void inputListData(std::string inData);
        void playGame(void);
        void dupMasterList(void);
        int collectTotalRounds(void);
        ListNode<LinuxData>* randNode(LinkedList<LinuxData>* targetList);
        int presentOptions(std::string* target);
        std::string* randOption(std::string* target);
        int collectGameAnswer(void);

        void applyCorrectAnswer(LinuxData* inData);

        void nextRound(void);

        void addNewData(void);
        void removeData(void);

        void saveAllData(void);

        LinkedList<LinuxData>* gameList;
        LinkedList<LinuxData>* masterList;

        PlayerManagement* playerData;
};



GameManagement::GameManagement(void)
{
    gameList = new LinkedList<LinuxData>;
    masterList = new LinkedList<LinuxData>;
    loadGameList();

    playerData = new PlayerManagement;
}


GameManagement::~GameManagement(void)
{
    saveAllData();
    delete gameList;
    delete masterList;
    delete playerData;
}



void GameManagement::loadGameList(void)
{
    std::ifstream infile;
    std::string instring;

    infile.open("commands.csv");

    while (std::getline(infile, instring))
    {        
        inputListData(instring);
    }
    infile.close();
}




void GameManagement::inputListData(std::string inData)
{
    std::istringstream lineStream(inData);
    
    std::string *newTerm = new std::string();
    std::string *newDefinition = new std::string();            

    std::getline(lineStream, *newTerm, ',');
    std::getline(lineStream, *newDefinition, '\n');

    LinuxData *newData = new LinuxData(newTerm, newDefinition);

    masterList->pushNode(new ListNode(newData));
}




void GameManagement::commitAction(int input)
{
    switch (input)
    {
        case 1:
            break;

        case 2:
            dupMasterList();
            playerData->newPlayer();
            playGame();
            break;
        
        case 3:
            dupMasterList();
            playerData->selectPlayer();
            playGame();
            break;

        case 4:
            addNewData();
            break;

        case 5:
            removeData();
            break;

        case 6:
            
            break;
    }
}




void GameManagement::playGame(void)
{
    int gameLength = collectTotalRounds();
    for (int round = 0; round < gameLength; round++)
    {
        system("clear");
        std::cout << "Round; " << round + 1 << ",  " << *playerData->getCurPlayer() << std::endl;
        ListNode<LinuxData>* targetNode = randNode(gameList);

        std::cout << "Define " << *targetNode->getData()->getName() << std::endl;
        int ans = presentOptions(targetNode->getData()->getDesc());
        std::cout << "\n\nCorrect Definition: " << std::endl;

        if (collectGameAnswer() == ans)
        {
            applyCorrectAnswer(targetNode->getData());
        }
        else
        {
            std::cout << "Incorrect! You were looking for " << *targetNode->getData()->getDesc() << std::endl;
            playerData->decrementScore();
        }
        nextRound();
    }
}



void GameManagement::dupMasterList(void)
{
    delete gameList;
    gameList = new LinkedList<LinuxData>(masterList);
}



int GameManagement::collectTotalRounds(void)
{
    int totalRounds;
    do 
    {
        std::cout << "How many rounds would you like to play? \n(5 - 30)" << std::endl;
        std::cin >> totalRounds;
        system("clear");
    } while (totalRounds > 30 || totalRounds < 5);
    return totalRounds;
}


ListNode<LinuxData>* GameManagement::randNode(LinkedList<LinuxData>* targetList)
{
    int targetIndex = rand() % targetList->getLength();
    return targetList->getNode(targetIndex);
}



int GameManagement::presentOptions(std::string* target)
{
    int targetOption = rand() % 3;

    switch (targetOption)
    {
        case 0:
            std::cout << "1) " << *target << "\n2) " << *randOption(target) << "\n3) " << *randOption(target) << std::endl;
            break;
        case 1:
            std::cout << "1) " << *randOption(target) << "\n2) " << *target<< "\n3) " << *randOption(target) << std::endl;
            break;
        case 2:
            std::cout << "1) " << *randOption(target) << "\n2) " << *randOption(target) << "\n3) " << *target << std::endl;
            break;
    }
    return targetOption + 1;
}




std::string* GameManagement::randOption(std::string* target)
{
    std::string* option1;
    do 
    {
        option1 = randNode(masterList)->getData()->getDesc();
    } while (*option1 == *target);
    return option1;
}



int GameManagement::collectGameAnswer(void)
{
    int userAns;
    do 
    {
        std::cin >> userAns;
    } while (userAns > 3 || userAns < 1);
    return userAns;
}



void GameManagement::applyCorrectAnswer(LinuxData* inData)
{
    std::cout << "Correct!" << std::endl;
    playerData->incrementScore();
    gameList->removeNode(inData);
}


void GameManagement::nextRound(void)
{
    getchar();  
    std::cout << "Press Enter to Continue" << std::endl;
    getchar();   
}




void GameManagement::addNewData(void)
{
    std::cout << "Enter the name of the new command\nEnter 'N' to return to the main menu" << std::endl;
    std::string stringName;
    std::cin.ignore();
    std::getline(std::cin, stringName);
    if (stringName != "N")
    {
        std::cout << "Enter the description of the new command" << std::endl;
        std::string stringDesc;
        std::getline(std::cin, stringDesc);
        LinuxData *newData = new LinuxData(new std::string(stringName), new std::string(stringDesc));
        if (masterList->checkDuplicate(newData))
        {
            system("clear");
            std::cout << "This command already exists. Try again" << std::endl; 
            addNewData();
        }
        else 
        {
            masterList->pushNode(new ListNode(newData));
        }
    }    
}



void GameManagement::removeData(void)
{
    std::cout << "Enter the name of the command you would like to remove\nEnter 'N' to return to the main menu" << std::endl;
    std::string stringName;
    std::cin.ignore();
    std::getline(std::cin, stringName);
    if (stringName != "N")
    {
        LinuxData *newData = new LinuxData(new std::string(stringName), new std::string("What goes here is irrelevant"));
        if(masterList->checkDuplicate(newData))
        {
            masterList->removeNode(newData);
        }
        else 
        {
            std::cout << "Could not find the command '" << stringName << "'" << std::endl;
            removeData();
        }
    }    
}





void GameManagement::saveAllData(void)
{
    std::ofstream outfile;

    outfile.open("commands.csv");
    outfile << *masterList;
    outfile.close();

    outfile.open("profiles.csv");
    playerData->outputPlayerArray(outfile);
    outfile.close();
}