#include <iostream>
#include <fstream>
#include <string>

#include "GameManagement.hpp"
#include "LinuxData.hpp"
#include "ListNode.hpp"
#include "LinkedList.hpp"

#pragma once


int main (void)
{
    srand((unsigned int)time(NULL));
    int userInput = 0;    
    GameManagement curgame;

    do 
    {
        system("clear");
        if (userInput == 1)
        {
            std::cout << "You will be given a linux command that you must match to a definition.\nIf you are correct you get a point, incorrect and you lose a point.\n" << std::endl;
        }
        curgame.commitAction(userInput);        
        std::cout << "Please enter an option listed below;\n1)Game Rules\n2)Play Game\n3)Load Previous Game\n4)Add Command\n5)Remove Command\n6)Exit" << std::endl;
        std::cin >> userInput;
    } while (userInput != 6); 
  
    return 0;
}