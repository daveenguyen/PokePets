#include <iostream>
#include <string>
#include <cstdlib> // for rand, srand
#include <time.h>
#include <cmath>
using namespace std;

#include "Pokemon.h"

Pokemon::Pokemon(int dexNum, int level) : PokemonSpecies(dexNum)
{
    srand(time(NULL));

    _nickname     = "";
    _genderValue  = rand() % 256;
    _abilityIndex = rand() % 2;
    // _nature       = rand() % 25;
    _nature.initNature(rand() % 25);
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

    // _moves[0]     = 0;
    // _moves[1]     = 0;
    // _moves[2]     = 0;
    // _moves[3]     = 0;

    _curHP        = getStats(0);
    _status       = 0;
}

Pokemon::~Pokemon() {}
void Pokemon::reset()
{
    _curHP = getStats(0);
    if (_curExp == 0)
        _curExp = getExpToLvl(_level-1);
    if (_moves[0].getMoveNum()==0)
        initMoves();
    for (int i = 0; i < 4; ++i)
    {
    _curPP[i] = _moves[i].getPP();
    }
}


void Pokemon::setLevel(int i)
{
    _level = i;
}

string Pokemon::getNickname()
{
    // if not nicknamed, return species' name
    if (_nickname=="") return getName();
    else return _nickname;
}

string Pokemon::getGender()
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

    string genderString;
    switch (thisGender) {
        case -1:
            genderString = "Genderless";
            break;
        case 0:
            genderString = "Male";
            break;
        case 1:
            genderString = "Female";
            break;
        default:
            cerr << "ERROR - thisGender: " << thisGender << endl;
            break;
    }

    return genderString;
}

int Pokemon::getAbility(){
    if (_abilityIndex != 0 && getSpeciesAbility(1) == 0)
    {
        _abilityIndex = 0;
    }

    return getSpeciesAbility(_abilityIndex);
}

string Pokemon::getNature()
{
    return _nature.toString();
}

int Pokemon::getLevel()
{
    return _level;
}

int Pokemon::getCurExp()
{
    if (_curExp == 0) _curExp = getExpToLvl(_level-1);
    return _curExp;
}

int Pokemon::getIV(int i)
{
    return _IVs[i];
}

int Pokemon::getEV(int i)
{
    return _EVs[i];
}

Move Pokemon::getMove(int i)
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
        if (i+1 == _nature.getDecStat()) nature -= 0.1;
        if (i+1 == _nature.getIncStat()) nature += 0.1;

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

int Pokemon::getCurPP(int i)
{
    return _curPP[i];
}

void Pokemon::adjustExperience(int baseExp, int faintLvl, bool isWild, int participated)
{
    double wild;
    if (isWild) wild = 1;
    else wild = 1.5;

    double expGain;
    expGain = (double)(wild * baseExp * faintLvl)/(5 * participated);
    expGain *= pow ( (2 * faintLvl + 10) , 2.5) / pow ( (faintLvl + _level + 10) , 2.5);
    ++expGain;

    _curExp += (int)expGain;
    checkExperience();
}

void Pokemon::initMoves()
{
    int moveCount=0;
    int vectorSize = getLevelUpMoves().size();

    for (int i = 0; i < vectorSize; ++i)
    {
        if (_level >= getLevelUpMoves()[i]._level)
        {
            // _moves[i%4] = getLevelUpMoves()[i]._move_id;
            _moves[i%4].setMoveNum(getLevelUpMoves()[i]._move_id);
            _curPP[i%4] = _moves[i%4].getPP();
        }
        else
        {
            break;
        }
    }

}

void Pokemon::checkExperience()
{
    while (_level < 100 && _curExp > getExpToLvl(_level)) {
        float hpRatio = float(_curHP)/getStats(0);
        ++_level;
        _curHP = (int)(hpRatio * getStats(0));
        cout << "LEVEL UP!" << endl;
    }
}

void Pokemon::adjustHP(int i)
{
    _curHP += i;
    if (_curHP > getStats(0)) _curHP = getStats(0);
    else if (_curHP < 0) _curHP = 0;
}

void Pokemon::useMove(int i, Pokemon* target)
{
    cout << getNickname() << " used " << _moves[i].getIdentifier() << "!" << endl;

    _curPP[i]--;
    switch (_moves[i].getMeta_category_id())
    {
        case 0:
        {
            // damage
            doDamage(target, &_moves[i]);
            break;
        }
        case 1:
        {
            // ailment
            doAilment(target, &_moves[i]);
            break;
        }
        case 2:
        {
            // net-good-stats
            break;
        }
        case 3:
        {
            // heal
            break;
        }
        case 4:
        {
            // damage + ailment
            doDamage(target, &_moves[i]);
            doAilment(target, &_moves[i]);
            break;
        }
        case 5:
        {
            // swagger
            break;
        }
        case 6:
        {
            // damage + lower
            doDamage(target, &_moves[i]);
            break;
        }
        case 7:
        {
            // damage + raise
            doDamage(target, &_moves[i]);
            break;
        }
        case 8:
        {
            // damage + heal
            doDamage(target, &_moves[i]);
            break;
        }
        case 9:
        {
            // ohko
            break;
        }
        case 10:
        {
            // whole field effect
            break;
        }
        case 11:
        {
            // field effect
            break;
        }
        case 12:
        {
            // force switch
            break;
        }
        case 13:
        {
            // unique
            break;
        }
        default:
        {
            //
            break;
        }
    }
    //// Inflicts damage
    //0, 4, 6, 7, 8

    //// inflicts status ailment
    //1, 4, 5

    //// lowers target's stats or raises user's stats
    //2,

    //// raises target's stats
    //5

    //// heals the user
    //3

    //// lowers target's stats
    //2, 6

    //// raises user's stats
    //2, 7

    //// absorbs damage done to heal the user
    //8

    //// one hit ko
    //9

    //// effect on the whole field
    //10

    //// effect on one side of the field
    //11

    //// Forces target to switch out
    //12

    ////Unique effect
    //13
}

void Pokemon::doDamage(Pokemon* target, Move* move)
{
// CHECK MISS
    if (rand() % 100 <= move->getAccuracy() || move->getAccuracy() == 0)
    {

    // MODIFIERS
        double modifier = 0.85 + (double)rand() / (double)RAND_MAX * 0.15;
        int moveTypeId = move->getType_id();

        // stab
        if (moveTypeId == getType(0).getTypeNum() || moveTypeId == getType(1).getTypeNum())
        {
            modifier *= 1.15;
        }

        // crit
        int crit_rate = move->getCrit_rate(); // add items or moves
        crit_rate *= 625; // each stage is 6.25%
        if (crit_rate > 5000) crit_rate = 5000;
        if (rand() % 10000 < crit_rate)
        {
            cout << "A critical hit!" << endl;
            modifier *= 2;
        }

        // type
        int targetType1 = target->getType(0).getTypeNum();
        int targetType2 = target->getType(1).getTypeNum();
        double typeMod = 1;
        typeMod *= move->getType().getEfficacy(targetType1);
        if (targetType2 != targetType1)
            typeMod *= move->getType().getEfficacy(targetType2);

        if (typeMod > 1)
            cout << "It's super effective!" << endl;
        else if (typeMod == 0)
        {
            cout << "It doesn't affect " << target->getNickname() << "..." << endl;
            typeMod = 0.125; // our own implementation instead of x0 it's 1/8
        }
        else if (typeMod < 1)
            cout << "It's not very effective..." << endl;

        modifier *= typeMod;

        // other like items, field advantage, or if double/triple

    // DAMAGE
        // which atk, which def
        int atk;
        int def;
        // physical
        if (move->getDamage_class_id() == 2)
        {
            atk = getStats(1);
            def = target->getStats(2);
        }
        // special
        else if (move->getDamage_class_id() == 3)
        {
            atk = getStats(3);
            def = target->getStats(4);
        }
        int damage = ((2 * _level + 10) / (double)250 * (atk / (double)def) * move->getPower() + 2) * modifier;

        target->adjustHP(-damage);
    }
    else
    {
        cout << getNickname() << "'s attack missed!" << endl;
    }
}

void Pokemon::doAilment(Pokemon* target, Move* move)
{
    // cout << move->getAilment_chance();
    // cout << "DOAILMENT" << endl;
    if (rand() % 100 <= move->getAilment_chance() || move->getAilment_chance() == 0)
        switch (move->getMeta_ailment_id())
        {
            case 1:
                cout << target->getNickname() << " is paralyzed! It may be unable to move!" << endl;
                _status = 1;
                break;
            case 2:
                cout << target->getNickname() << " fell asleep!" << endl;
                _status = 2;
                break;
            case 3:
                cout << target->getNickname() << " was frozen solid!" << endl;
                _status = 3;
                break;
            case 4:
                cout << target->getNickname() << " was burned!" << endl;
                _status = 4;
                break;
            case 5:
                cout << target->getNickname() << " was poisoned!" << endl;
                _status = 5;
                // cout << target->getNickname() << " was badly poisoned!" << endl;
                break;
            default:
                break;
        }
}