#include <string>
#include <iostream>
using namespace std;

#include "Type.h"

Type::Type(int typeNum)
{
    _typeNum = typeNum;
    if (_typeNum!=0)
        initType();
}

void Type::initType()
{
    int token = 0;

    CSVReader _reader;

    // TYPE_NAMES_CSV
    _reader.openFile(TYPE_NAMES_CSV);
    token = 0;

    while (true)
    {
        do
        {
            _reader.readLine();
            _reader.readField();
            token = _reader.getField<int>();
        } while ( token < _typeNum && !_reader.isEof());

        if (token != _typeNum || _reader.isEof())
        {
            break;
        }

        _reader.readField();
        if (_reader.getField<int>() == LANGUAGE_ID)
        {
            _reader.readField();
            // _species->setName(_reader.getField<string>());
            _identifier = _reader.getCurField();//.getField<string>();
            break;
        }
    }



// TYPE_EFFICACY_CSV
    _reader.openFile(TYPE_EFFICACY_CSV);
    token = 0;

    while (true)
    {
        do
        {
            _reader.readLine();
            _reader.readField();
            token = _reader.getField<int>();
        } while ( token < _typeNum && !_reader.isEof());

        if (token != _typeNum || _reader.isEof()) break;

        int target_type_id = 0;
        int damage_factor  = 0;
        _reader.readField();
        target_type_id = _reader.getField<int>();
        _reader.readField();
        damage_factor = _reader.getField<int>();

        _efficacy[target_type_id-1] = damage_factor/(double)100;
    }




    // DBParser db(typeNum, 1);
    // _identifier = db.getTypeString();
    // _typeNum = typeNum;
    // for (int i = 0; i < 17; ++i)
    // {
        // _efficacy[i] = db.getTypeEfficacy(i+1);
    // }
}

void Type::setIdentifier(string id)
{
    _identifier = id;
}

void Type::setTypeNum(int typeNum)
{
    _typeNum = typeNum;
    initType();
}

void Type::setEfficacy(int typeId, double value)
{
    _efficacy[typeId-1] = value;
}


string Type::getIdentifier()
{
    return _identifier;
}

int Type::getTypeNum()
{
    return _typeNum;
}

double Type::getEfficacy(int typeId)
{
    return _efficacy[typeId-1];
}

