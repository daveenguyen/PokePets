#include <iostream> // std::cerr
#include <cstdlib>  // std::exit
#include <typeinfo>

using namespace std;

#include "CSVReader.h"

CSVReader::CSVReader() {
    reset();
}

CSVReader::CSVReader(const char* file)
{
    reset();
    openFile(file);
}

void CSVReader::openFile(const char* file)
{
    if(my_ifs.is_open())
    {
        my_ifs.close();
    }

    my_ifs.open(file);

    if(!my_ifs.is_open())
    {
        cerr << "Could not open " << file << endl;
        exit(1);
    }

    my_ifs.clear(); // reset flags
    countFields();
}


void CSVReader::reset()
{
    if(my_ifs.is_open())
    {
        my_ifs.close();
    }

    my_ss.str("");
    my_ss.clear();

    curLine  = "";
    curField = "";
    fSize    = 0;
    fIndex   = -1;
}


void CSVReader::readLine()
{
    if (!my_ifs.eof())
    {
        getline(my_ifs, curLine);
        my_ss.str(curLine);
        my_ss.clear();
        fIndex = -1;
        curField = "";
    }
}


void CSVReader::readField() {
    if (!my_ss.eof())
    {
        ++fIndex;
        if (my_ss.peek() == ',') {
            my_ss.ignore();
            curField = "";
        }
        else
        {
            string field;
            getline(my_ss, curField, ',');
            if (my_ss.fail() && (fIndex == fSize-1)) {
                curField = "";
            }
        }
    }
}


string CSVReader::getLine()
{
    return curLine;
}

//template <>
string CSVReader::getCurField(){
    return curField;
};

int CSVReader::getFieldSize()
{
    return fSize;
}


int CSVReader::getFieldIndex()
{
    return fIndex;
}


bool CSVReader::isEol()
{
    return my_ss.eof();
}


bool CSVReader::isEof()
{
    return my_ifs.eof();
}

bool CSVReader::isOpen()
{
    return my_ifs.is_open();
}


void CSVReader::countFields()
{
    fSize = 0;
    readLine();

    while (!my_ss.eof())
    {
        readField();
        ++fSize;
    }

    curField = "";
    fIndex   = -1;

    my_ss.str(curLine);
    my_ss.clear();
}