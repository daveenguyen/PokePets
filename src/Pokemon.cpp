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
    _nature.setNatureNum(rand() % 25);
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

    _curHP        = -1;
    _status       = 0;

    for (int i = 0; i < 8; i++)
        _statStage[i] = 0;

    _isWild = true;
}

Pokemon::~Pokemon() {}
void Pokemon::reset()
{
    if (_curHP == -1)
        _curHP = getStats(0);
    if (_curExp == 0)
        _curExp = getExpToLvl(_level-1);
    if (_moves[0].getMoveNum()==0)
        initMoves();

    _statStage[1] = 0;
    _statStage[2] = 0;
    _statStage[3] = 0;
    _statStage[4] = 0;
    _statStage[5] = 0;
    _statStage[6] = 0;
    _statStage[7] = 0;
}


void Pokemon::setLevel(int i)
{
    _level = i;
}

void Pokemon::setStatus(int i)
{
    _status = i;
}

int  Pokemon::getStatStage(int i)
{
    return _statStage[i];
}

void Pokemon::setStatStage(int i, int value)
{
    _statStage[i] = value;

    if (_statStage[i] > 6)
    {
        _statStage[i] = 6;
    }
    else if (_statStage[i] < -6)
    {
        _statStage[i] = -6;
    }
}


string Pokemon::getNickname()
{
    // if not nicknamed, return species' name
    if (_nickname=="") return getName();
    else return _nickname;
}
void Pokemon::setNickname(string i)
{
    _nickname = i;
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

int Pokemon::getBattleStats(int i)
{
    int stat;
    switch (i)
    {
        case 1: // hp
            stat = getStats(1);

        case 2: // atk
            stat = getStats(2);
            if (_statStage[1] > 0)
                stat *= (2+_statStage[1])/double(2);
            else if (_statStage[1] < 0)
                stat *= (-2)/double(_statStage[1]-2);
            if (_status == 4)
                stat /= double(2);
            break;

        case 3: // def
            stat = getStats(3);
            if (_statStage[2] > 0)
                stat *= (2+_statStage[2])/double(2);
            else if (_statStage[2] < 0)
                stat *= (-2)/double(_statStage[2]-2);
            break;

        case 4: // satk
            stat = getStats(4);
            if (_statStage[3] > 0)
                stat *= (2+_statStage[3])/double(2);
            else if (_statStage[3] < 0)
                stat *= (-2)/double(_statStage[3]-2);
            break;

        case 5: // sdef
            stat = getStats(5);
            if (_statStage[4] > 0)
                stat *= (2+_statStage[4])/double(2);
            else if (_statStage[4] < 0)
                stat *= (-2)/double(_statStage[4]-2);
            break;

        case 6: // speed
            stat = getStats(6);
            if (_statStage[5] > 0)
                stat *= (2+_statStage[5])/double(2);
            else if (_statStage[5] < 0)
                stat *= (-2)/double(_statStage[5]-2);
            if (_status == 1)
                stat *= double(0.75);
            break;

        case 7: // accuracy
            stat = 100;
            if (_statStage[6] > 0)
                stat *= (3+_statStage[6])/double(3);
            else if (_statStage[6] < 0)
                stat *= (-3)/double(_statStage[6]-3);
            break;

        case 8: // evasion
            stat = 100;
            if (_statStage[7] > 0)
                stat *= (3+_statStage[7])/double(3);
            else if (_statStage[7] < 0)
                stat *= (-3)/double(_statStage[7]-3);
            break;
    }
    return stat;
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
    if (expGain > 0)
    {
        cout << getNickname() << " gained " << (int)expGain << " experience!" << endl;
    }
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
        cout << getNickname() << " grew to level " << _level << "!" << endl;

        int moveCount = 0;
        for (int j = 0; j < 4 && getMove(j).getMoveNum() != 0; ++j)
        {
            ++moveCount;
        }

        int vectorSize = getLevelUpMoves().size();
        for (int i = 0; i < vectorSize; ++i)
        {
            if (_level == getLevelUpMoves()[i]._level)
            {
                Move tempmove(getLevelUpMoves()[i]._move_id);
                int learnIndex;
                if (moveCount < 4)
                {
                    learnIndex = moveCount;
                }
                else
                {
                    cout << getNickname() << " is trying to learn " << tempmove.getIdentifier() << endl;

                    int moveCount = 0;
                    for (int j = 0; j < 4 && getMove(j).getMoveNum() != 0; ++j)
                    {
                        ++moveCount;
                    }
                    for (int i=0; i < moveCount; ++i) {
                        cout << i+1 << ". " << getMove(i).getIdentifier() << endl;;
                    }
                    cout << "5. Don't learn" << endl;
                    cout << "Which should be forgotten?" << endl;

                    int userInput = 0;

                    while ( !(cin >> userInput) || (userInput <= 0 && userInput > 5) )
                    {
                        cout << "Invalid input!  Try again: ";
                        cin.clear ();   // reset fail flag

                        // skip past invalid input
                        cin.ignore (1000, '\n');  // Skip to next newline or 1000 chars
                    }
                    learnIndex = userInput-1;
                }

                if (learnIndex<4)
                {

                    if (_moves[learnIndex].getMoveNum() != 0)
                    {
                        cout << "1, 2 and... poof! ";
                        cout << getNickname() << " forgot " << _moves[learnIndex].getIdentifier() << " and";
                    }
                    else
                    {
                        cout << getNickname();
                    }
                    _moves[learnIndex].setMoveNum(getLevelUpMoves()[i]._move_id);
                    _curPP[learnIndex] = _moves[learnIndex].getPP();
                    cout << " learned " << _moves[learnIndex].getIdentifier() << "!" << endl;
                }
                else if (learnIndex==4)
                {
                    cout << getNickname() << " did not learn " << tempmove.getIdentifier() << "." << endl;
                }

            }
            if (getLevelUpMoves()[i]._level > _level)
                break;
        }
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
            if (_moves[i].getTarget_id()==7)
            {
                doRaiseUserStat(&_moves[i]);
            }
            else
            {
                doLowersTargetStat(target, &_moves[i]);
            }
            break;
        }
        case 3:
        {
            // heal
            doHealUser(&_moves[i]);
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
            doAilment(target, &_moves[i]);
            doRaiseTargetStat(target, &_moves[i]);
            break;
        }
        case 6:
        {
            // damage + lower
            doDamage(target, &_moves[i]);
            doLowersTargetStat(target, &_moves[i]);
            break;
        }
        case 7:
        {
            // damage + raise
            doDamage(target, &_moves[i]);
            doRaiseUserStat(&_moves[i]);
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

    //// lowers target's stats or raises user's stats
    //2,

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
    if (rand() % 100 <= (move->getAccuracy()*(double)(getBattleStats(7))/(double)(target->getBattleStats(8))) || move->getAccuracy() == 0)
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

        if (crit_rate > 5000)
        {
            crit_rate = 5000;
        }

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
        {
            typeMod *= move->getType().getEfficacy(targetType2);
        }

        if (typeMod > 1)
        {
            cout << "It's super effective!" << endl;
        }
        else if (typeMod == 0)
        {
            cout << "It doesn't affect " << target->getNickname() << "..." << endl;
            typeMod = 1/6.0; // our own implementation instead of x0 it's 1/6
        }
        else if (typeMod < 1)
        {
            cout << "It's not very effective..." << endl;
        }

        modifier *= typeMod;

        // other like items, field advantage, or if double/triple

    // DAMAGE
        // which atk, which def
        int atk;
        int def;
        // physical
        if (move->getDamage_class_id() == 2)
        {
            atk = getBattleStats(1);
            def = target->getBattleStats(2);
        }
        // special
        else if (move->getDamage_class_id() == 3)
        {
            atk = getBattleStats(3);
            def = target->getBattleStats(4);
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
    if (rand() % 100 <= move->getAilment_chance() || move->getAilment_chance() == 0)
    {
        switch (move->getMeta_ailment_id())
        {
            case 1:
                if (target->getStatus() == 0)
                {
                    cout << target->getNickname() << " is paralyzed! It may be unable to move!" << endl;
                    target->setStatus(1);
                }
                break;
            case 2:
                if (target->getStatus() == 0)
                {
                    cout << target->getNickname() << " fell asleep!" << endl;
                    target->setStatus(2);
                    target->setAilmentCounter(rand()%(move->getMax_turns()+1 - move->getMin_turns()) + move->getMin_turns());
                }
                break;
            case 3:
                if (target->getStatus() == 0)
                {
                    cout << target->getNickname() << " was frozen solid!" << endl;
                    target->setStatus(3);
                }
                break;
            case 4:
                if (target->getStatus() == 0)
                {
                    cout << target->getNickname() << " was burned!" << endl;
                    target->setStatus(4);
                }
                break;
            case 5:
                if (target->getStatus() == 0)
                {
                    cout << target->getNickname() << " was poisoned!" << endl;
                    target->setStatus(5);
                }
                // cout << target->getNickname() << " was badly poisoned!" << endl;
                break;
            default:
                break;
        }
    }
}

void Pokemon::doHealUser(Move* move)
{

}

void Pokemon::doLowersTargetStat(Pokemon* target, Move* move)
{
    for (int i = 0; i < 8; i++)
    {
        if (move->getStatChange(i) != 0 && target->getStatStage(i) < 6 && target->getStatStage(i) > -6)
        {
            int curStatChange = move->getStatChange(i);

            if (target->isWild())
            {
                cout << "Wild ";
            }
            cout << target->getNickname() << "'s ";

            switch (i)
            {
                case 1:
                    cout << "Attack ";
                    break;
                case 2:
                    cout << "Defense ";
                    break;
                case 3:
                    cout << "Special Attack ";
                    break;
                case 4:
                    cout << "Special Defense ";
                    break;
                case 5:
                    cout << "Speed ";
                    break;
                case 6:
                    cout << "Accuracy ";
                    break;
                case 7:
                    cout << "Evasion ";
                    break;
                default:
                    break;
            }

            if (curStatChange > 1 || curStatChange < -1)
                cout << "sharply " ;

            if (curStatChange > 0)
            {
                // buff
                cout << "rose!";
            }
            else if (curStatChange < 0)
            {
                // debuff
                cout << "fell!";
            }

            cout << endl;
            target->setStatStage(i, target->getStatStage(i) + move->getStatChange(i));
        }
    }
}

void Pokemon::doRaiseUserStat(Move* move)
{
    doLowersTargetStat(this, move);
}

void Pokemon::doRaiseTargetStat(Pokemon* target, Move* move)
{
    doLowersTargetStat(target, move);
}

bool Pokemon::isWild(){
    return _isWild;
}

void Pokemon::setIsWild(bool value){
    _isWild = value;
}

void Pokemon::setAilmentCounter(int i)
{
    _ailmentCounter = i;
}

void Pokemon::checkAilment()
{
    if (_status == 2)
    {
        _ailmentCounter--;
        cout << getNickname() << " is fast asleep..." << endl;;
        if (_ailmentCounter <= 0)
        {
            _status = 0;
            cout << getNickname() << " woke up!" << endl;
        }
    }
    else if (_status == 3)
    {
        cout << getNickname() << " is frozen solid..." << endl;;
        if (rand()%100 < 25)
        {
            _status = 0;
            cout << getNickname() << " thawed out!" << endl;
        }
    }
}