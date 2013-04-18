#ifndef TYPE_H
#define TYPE_H

#include <string>
using namespace std;

#include "CSVReader.h"
// class CSVReader;

class Type
{
    public:

        Type(int typeNum=0);

        ~Type() {};

        void    initType();

        void    setIdentifier(string id);
        void    setTypeNum(int typeNum);
        void    setEfficacy(int index, double value);

        string  getIdentifier();
        int     getTypeNum();
        double  getEfficacy(int i);

    private:
        // CSVReader* _reader;

        string _identifier;
        int    _typeNum;
        double _efficacy[17];

};

#endif // TYPE_H