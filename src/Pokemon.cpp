#include <iostream>
#include <string>
#include <cstdlib> // for rand, srand
#include <time.h>

#include "Pokemon.h"

Pokemon::Pokemon(int dexNum, int level) : PokemonSpecies(dexNum)
{
    srand(time(NULL));

    _nickname     = getName();
    _genderValue  = rand() % 256;
    _abilityIndex = rand() % 2;
    _nature       = rand() % 25;
    _level        = level;
    _curExp       = 0;

    // IVs are between 0 and 31
    _IVs[0]       = rand() % 32;
    _IVs[1]       = rand() % 32;
    _IVs[2]       = rand() % 32;
    _IVs[3]       = rand() % 32;
    _IVs[4]       = rand() % 32;
    _IVs[5]       = rand() % 32;

    _EVs[0]       = 0;
    _EVs[1]       = 0;
    _EVs[2]       = 0;
    _EVs[3]       = 0;
    _EVs[4]       = 0;
    _EVs[5]       = 0;

    _moves[0]     = 0;
    _moves[1]     = 0;
    _moves[2]     = 0;
    _moves[3]     = 0;

    initMoves();
    _curHP        = getStats(0);
    _status       = 0;
}

Pokemon::~Pokemon() {}

string Pokemon::getNickname()
{
    return _nickname;
}

int Pokemon::getGender()
{
    int thisGender = -2;

    switch (getGenderRate())
    {
        // genderless
        case -1:
        {
            thisGender = -1;
            break;
        }

        // male only
        case 0:
        {
            thisGender = 0;
            break;
        }

        // 1f:7m
        case 1:
        {
            if (_genderValue < 224)
            {
                thisGender = 0;
            }
            else
            {
                thisGender = 1;
            }
            break;
        }

        // 1f:3m
        case 2:
        {
            if (_genderValue < 192)
            {
                thisGender = 0;
            }
            else
            {
                thisGender = 1;
            }
            break;
        }

        // 1f:1m
        case 4:
        {
            if (_genderValue < 128)
            {
                thisGender = 0;
            }
            else
            {
                thisGender = 1;
            }
            break;
        }

        // 3f:1m
        case 6:
        {
            if (_genderValue < 64)
            {
                thisGender = 0;
            }
            else
            {
                thisGender = 1;
            }
            break;
        }

        // female only
        case 8:
        {
            thisGender = 1;
            break;
        }

        default:
        {
            cerr << "ERROR - gender: " << getGenderRate() << endl;
            exit(1);
            break;
        }
    }

    return thisGender;
}

int Pokemon::getAbility(){
    if (_abilityIndex != 0 && getAbilities(1) == 0)
    {
        _abilityIndex = 0;
    }

    return getAbilities(_abilityIndex);
}

int Pokemon::getNature()
{
    return _nature;
}

int Pokemon::getLevel()
{
    return _level;
}

int Pokemon::getCurExp()
{
    return _curExp;
}

int Pokemon::getIVs(int i)
{
    return _IVs[i];
}

int Pokemon::getEVs(int i)
{
    return _EVs[i];
}

int Pokemon::getMoves(int i)
{
    return _moves[i];
}

int Pokemon::getCurHP()
{
    return _curHP;
}

int Pokemon::getStatus()
{
    return _status;
}

int Pokemon::getStats(int i)
{
    // The stat is rounded down if the result is a decimal.
    // It is also rounded down before the Nature multiplier, if any, is applied.
    int calc_stat=0;

    // hp calculation
    if (i == 0)
    {
        calc_stat = ((_IVs[i] + (2 * getBaseStats(i)) + (_EVs[i] / (double)4) + 100) * _level)/100 + 10;
    }
    else if (i < 6)
    {
        double nature = 1;
        calc_stat = ((_IVs[i] + (2 * getBaseStats(i)) + (_EVs[i] / (double)4)) * _level)/100 + 5;
        calc_stat *= nature;
    }
    else
    {
        cerr << "ERROR - getStats(" << i << ")" << endl;
        exit(1);
    }

    return calc_stat;
}

void Pokemon::initMoves()
{
    int moveCount=0;
    int vectorSize = getLevelUpMoves().size();

    for (int i = 0; i < vectorSize; ++i)
    {
        if (_level >= getLevelUpMoves()[i]._level)
        {
            _moves[i%4] = getLevelUpMoves()[i]._move_id;
        }
        else
        {
            break;
        }
    }

}