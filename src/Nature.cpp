#include <string>
#include <iostream>
using namespace std;

#include "DBParser.h"
#include "Nature.h"

Nature::Nature(int natureNum)
{
    DBParser db(natureNum, 1);
    _identifier = db.getTypeString();
    _natureNum = natureNum;
    for (int i = 0; i < 17; ++i)
    {
        _efficacy[i] = db.getTypeEfficacy(i+1);
    }
}