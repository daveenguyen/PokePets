#include <string>
#include <iostream>
using namespace std;

#include "DBParser.h"
#include "Nature.h"

Nature::Nature() {

}

Nature::Nature(int natureNum)
{
    initNature(natureNum);
}

void Nature::initNature(int natureNum)
{
    DBParser db(natureNum+1, 2);
    _natureNum         = natureNum;
    _identifier        = db.getNatureString();
    _decreased_stat_id = db.getNatureDecStat();
    _increased_stat_id = db.getNatureIncStat();
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




