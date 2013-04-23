#include <string>
#include <iostream>
using namespace std;

#include "CSVReader.h"
#include "Nature.h"

Nature::Nature() {

}

Nature::Nature(int natureNum):_natureNum(natureNum)
{
}

void Nature::initNature()
{
    int token = 0;

    CSVReader _reader;

    // NATURE_NAMES_CSV
    _reader.openFile(NATURE_NAMES_CSV);
    token = 0;

    while (true)
    {
        do
        {
            _reader.readLine();
            _reader.readField();
            token = _reader.getField<int>();
        } while ( token < _natureNum && !_reader.isEof());

        if (token != _natureNum || _reader.isEof())
        {
            break;
        }

        _reader.readField();
        if (_reader.getField<int>() == LANGUAGE_ID)
        {
            _reader.readField();
            // _species->setName(_reader.getField<string>());
            _identifier = _reader.getField<string>();
            break;
        }
    }



// NATURES_CSV
    _reader.openFile(NATURES_CSV);
    token = 0;

    while (true)
    {
        do
        {
            _reader.readLine();
            _reader.readField();
            token = _reader.getField<int>();
        } while ( token < _natureNum && !_reader.isEof());

        if (token != _natureNum || _reader.isEof()) break;

        _reader.readField(); // no need for identifier
        _reader.readField();
        _decreased_stat_id = _reader.getField<int>();
        _reader.readField();
        _increased_stat_id = _reader.getField<int>();
    }

    // DBParser db(natureNum+1, 2);
    // _natureNum         = natureNum;
    // _identifier        = db.getNatureString();
    // _decreased_stat_id = db.getNatureDecStat();
    // _increased_stat_id = db.getNatureIncStat();
}

string Nature::toString()
{
    return _identifier;
}

int Nature::getNatureNum()
{
    return _natureNum;
}

int Nature::getDecStat()
{
    return _decreased_stat_id;
}

int Nature::getIncStat()
{
    return _increased_stat_id;
}

void Nature::setNatureNum(int i)
{
    _natureNum = i;
}