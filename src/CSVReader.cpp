#include <iostream> // std::cerr
#include <cstdlib>  // std::exit
using namespace std;

#include "CSVReader.h"

CSVReader::CSVReader() {
    reset();
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
    else
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
    fIndex   = 0;
}


void CSVReader::readLine()
{
    if (!my_ifs.eof())
    {
        getline(my_ifs, curLine);
        my_ss.str(curLine);
        my_ss.clear();
        fIndex = 0;
    }
    else
    {
        cerr << "END OF FILE" << endl;
        // exit(1);
    }
}


void CSVReader::readField() {
    if (!my_ss.eof())
    {
        if (my_ss.peek() == ',') {
            my_ss.ignore();
            curField = "";
        }
        else
        {
            string field;
            getline(my_ss, curField, ',');
        }
        ++fIndex;
    }
    else
    {
        cerr << "END OF LINE" << endl;
        exit(1);
    }
}


string CSVReader::getLine()
{
    return curLine;
}


string CSVReader::getField()
{
    return curField;
}


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


void CSVReader::countFields()
{
    readLine();

    while (!my_ss.eof())
    {
        readField();
        ++fSize;
    }
}