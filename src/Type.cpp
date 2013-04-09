#include <string>
#include <iostream>
using namespace std;

#include "DBParser.h"
#include "Type.h"
Type::Type(int typeNum)
{
    DBParser db(typeNum, 1);
    _identifier = db.getTypeString();
    _typeNum = typeNum;
    for (int i = 0; i < 17; ++i)
    {
        _efficacy[i] = db.getTypeEfficacy(i+1);
    }

    cout << _identifier << endl;
    cout << _typeNum << endl;
    for (int i = 0; i < 17; ++i)
    {
        cout << _efficacy[i] << endl;
    }
}