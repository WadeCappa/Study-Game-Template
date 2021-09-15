

#include <iostream>
#include <fstream>
#include <string>

#pragma once




class LinuxData
{
    public:
        LinuxData(std::string *inName, std::string *inDesc);
        LinuxData(LinuxData* indata);
        ~LinuxData();

        std::string* getName(void);
        std::string* getDesc(void);

    private:
        std::string* name;
        std::string* desc;
};


LinuxData::LinuxData(std::string *inName, std::string *inDesc)
{
    // std::cout << "LinuxData Constructor" << std::endl;
    name = inName;
    desc = inDesc;
    // std::cout << "LinuxData Constructed" << std::endl;
}


LinuxData::LinuxData(LinuxData* indata)
{
    name = new std::string(*indata->getName());
    desc = new std::string(*indata->getDesc());
}


LinuxData::~LinuxData()
{
    delete name;
    delete desc;
}


std::string* LinuxData::getName(void)
{
    return name;
}

std::string* LinuxData::getDesc(void)
{
    return desc;
}



std::ostream & operator << (std::ostream &stream, LinuxData &data)
{
    stream << *data.getName() << ": " << *data.getDesc() ;
    return stream;
}



std::ofstream & operator << (std::ofstream &stream, LinuxData &data)
{
    stream << *data.getName() << "," << *data.getDesc() << std::endl;
    return stream;
}



bool operator == (LinuxData &lhs, LinuxData &rhs)
{
    if (*lhs.getName() == *rhs.getName())
    {
        return true;
    }
    return false;
}