#include <iostream>
#include <string>
#include <cstdlib> // for rand, srand
#include <time.h>

#include "PokemonSpecies.h"
#include "Pokemon.h"

Pokemon::Pokemon(int dexNum, int level) : PokemonSpecies(dexNum) {

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

    // cout << "_nickname     = " << _nickname     << endl;
    // cout << "_genderValue  = " << _genderValue  << endl;
    // cout << "_abilityIndex = " << _abilityIndex << endl;
    // cout << "_nature       = " << _nature       << endl;
    // cout << "_level        = " << _level        << endl;
    // cout << "_curExp       = " << _curExp       << endl;
    // cout << "_IVs[0]       = " << _IVs[0]       << endl;
    // cout << "_IVs[1]       = " << _IVs[1]       << endl;
    // cout << "_IVs[2]       = " << _IVs[2]       << endl;
    // cout << "_IVs[3]       = " << _IVs[3]       << endl;
    // cout << "_IVs[4]       = " << _IVs[4]       << endl;
    // cout << "_IVs[5]       = " << _IVs[5]       << endl;
    // cout << "_EVs[0]       = " << _EVs[0]       << endl;
    // cout << "_EVs[1]       = " << _EVs[1]       << endl;
    // cout << "_EVs[2]       = " << _EVs[2]       << endl;
    // cout << "_EVs[3]       = " << _EVs[3]       << endl;
    // cout << "_EVs[4]       = " << _EVs[4]       << endl;
    // cout << "_EVs[5]       = " << _EVs[5]       << endl;
    // cout << "_moves[0]     = " << _moves[0]     << endl;
    // cout << "_moves[1]     = " << _moves[1]     << endl;
    // cout << "_moves[2]     = " << _moves[2]     << endl;
    // cout << "_moves[3]     = " << _moves[3]     << endl;
    // cout << "_curHP        = " << _curHP        << endl;
    // cout << "_status       = " << _status       << endl;
}

Pokemon::~Pokemon() {}

void Pokemon::getNickname(){
    cout << "NICKNAME: ";
    cout << _nickname << endl;
}

void Pokemon::getGender(){
    int thisGender = -2;
    switch (getGenderRate()) {
        case -1: {
            // genderless
            thisGender = -1;
            break;
        }
        case 0: {
            // male only
            thisGender = 0;
            break;
        }
        case 1: {
            // 1f:7m
            if (_genderValue < 224) {
                thisGender = 0;
            } else {
                thisGender = 1;
            }
            break;
        }
        case 2: {
            // 1f:3m
            if (_genderValue < 192) {
                thisGender = 0;
            } else {
                thisGender = 1;
            }
            break;
        }
        case 4: {
            // 1f:1m
            if (_genderValue < 128) {
                thisGender = 0;
            } else {
                thisGender = 1;
            }
            break;
        }
        case 6: {
            // 3f:1m
            if (_genderValue < 64) {
                thisGender = 0;
            } else {
                thisGender = 1;
            }
            break;
        }
        case 8: {
            thisGender = 1;
            break;
        }
        default: {
            cout << "GENDER ERROR" << endl;
            exit(1);
            break;
        }
    }
    cout << "GENDER:  ";
    if (thisGender == -1)
        cout << "GENDERLESS" << endl;
    else if (thisGender == 0)
        cout << "MALE" << endl;
    else if (thisGender == 1)
        cout << "FEMALE" << endl;
    else {
        cout << "GENDER ERROR" << endl;
        exit(1);
    }
}

void Pokemon::getAbility(){
    if (_abilityIndex != 0) {
        // check if it has ability 2
        if (getAbilities(1) != 0) {
            // cout << _abilityIndex << endl;
        }
        else {
            // cout << '0' << endl;
            _abilityIndex = 0;
        }
    }
    cout << "ABILITY: ";
    cout << _abilityIndex << endl;
}

void Pokemon::getNature(){
    cout << "NATURE:  " << _nature << endl;
}

void Pokemon::getLevel(){
    cout << "LEVEL:   ";
    cout << _level << endl;
}

void Pokemon::getCurExp(){
    cout << "CUR EXP: ";
    cout << _curExp << endl;
}

void Pokemon::getIVs(int i){
    cout << "IV[" << i << "]: ";
    cout << _IVs[i] << endl;
}

void Pokemon::getEVs(int i){
    cout << "EV[" << i << "]: ";
    cout << _EVs[i] << endl;
}

void Pokemon::getMoves(int i){
    cout << "MOVE[" << i << "]: ";
    cout << _moves[i] << endl;
}

void Pokemon::getCurHP(){
    cout << "CUR HP:  ";
    cout << _curHP << endl;
}

void Pokemon::getStatus(){
    cout << "STATUS:  ";
    cout << _status << endl;
}

int Pokemon::getStats(int i){
    cout << "STAT[" << i << "]: ";
    // The stat is rounded down if the result is a decimal.
    // It is also rounded down before the Nature multiplier, if any, is applied.
    int calc_stat=0;
    if (i == 0) {   // hp
        calc_stat = ((_IVs[i] + (2 * getBaseStats(i)) + (_EVs[i] / (double)4) + 100) * _level)/100 + 10;
        // calc_stat = ((24 + (2 * 108) + (71 / (float)4) + 100) * 78)/100 + 10;
        cout << calc_stat << endl;
    }
    else if (i < 6) {
        double nature = 1;
        calc_stat = ((_IVs[i] + (2 * getBaseStats(i)) + (_EVs[i] / (double)4)) * _level)/100 + 5;
        calc_stat *= nature;
        // calc_stat = ((24 + (2 * 108) + (71 / (float)4) + 100) * 78)/100 + 10;
        cout << calc_stat << endl;
    }
    else {
        // error
        cout << "getStats error: " << i << endl;
        exit(1);
    }
    return calc_stat;
}
void Pokemon::initMoves(){
    int moveCount=0;
    // LevelUpMoves _thisMov = getLevelUpMoves();
    int vectorSize = getLevelUpMoves().size();
    // cout << vectorSize << endl;
        // levelUpMoves.pop_back();

    // }
    for (int i = 0; i < vectorSize; ++i) {
        if (_level >= getLevelUpMoves()[i]._level) {
            _moves[i%4] = getLevelUpMoves()[i]._move_id;
        } else {
            break;
        }
    }
    // cout << "MOVE: " << _moves[0] << endl ;
    // cout << "MOVE: " << _moves[1] << endl ;
    // cout << "MOVE: " << _moves[2] << endl ;
    // cout << "MOVE: " << _moves[3] << endl ;
    // }
}


// testing
int main() {
    cout << "Enter a pokedex number or 0 for all: ";
    int dexNum;
    cin  >> dexNum;
    cout << endl;
    Pokemon myPokemon(dexNum, 6);

    myPokemon.getNickname();
    myPokemon.getGender();
    myPokemon.getAbility();
    myPokemon.getNature();
    myPokemon.getLevel();
    myPokemon.getCurExp();

    myPokemon.getMoves(0);
    myPokemon.getMoves(1);
    myPokemon.getMoves(2);
    myPokemon.getMoves(3);

    myPokemon.getCurHP();
    myPokemon.getStatus();

    myPokemon.getStats(0);
    myPokemon.getStats(1);
    myPokemon.getStats(2);
    myPokemon.getStats(3);
    myPokemon.getStats(4);
    myPokemon.getStats(5);
    return 0;
}