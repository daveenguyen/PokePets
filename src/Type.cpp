#include <string>
#include <iostream>
using namespace std;

#include "DBParser.h"
#include "Type.h"
Type::Type(int typeNum)
{
    initType(typeNum);
}

void Type::initType(int typeNum)
{
    DBParser db(typeNum, 1);
    _identifier = db.getTypeString();
    _typeNum = typeNum;
    for (int i = 0; i < 17; ++i)
    {
        _efficacy[i] = db.getTypeEfficacy(i+1);
    }
}

int Type::getEfficacy(int i)
{
    return _efficacy[i];
}