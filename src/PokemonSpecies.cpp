#include <string>
#include <iostream>
using namespace std;

#include "PokemonSpecies.h"

PokemonSpecies::PokemonSpecies(int dexNum)
{
    /* parse database file based on pokedex number
       then set these variables */
    clear();
    _dexNum = dexNum;
}

PokemonSpecies::~PokemonSpecies() {}

void PokemonSpecies::clear()
{
    _dexNum        = 0;
    _capRate       = 0;
    _baseHappiness = 0;
    _growthRate    = 0;
    _genderRate    = 0;

    // POKEMON_SPECIES_NAME
    _name          = "";

    // POKEMON_TYPES_CSV
    //_types[0]     = 0;
    //_types[1]     = 0;

    // POKEMON_ABILITIES_CSV
    _abilities[0] = 0;
    _abilities[1] = 0;
    _abilities[2] = 0;

    // POKEMON_STATS_CSV
    _baseStats[0] = 0;
    _baseStats[1] = 0;
    _baseStats[2] = 0;
    _baseStats[3] = 0;
    _baseStats[4] = 0;
    _baseStats[5] = 0;

    // POKEMON_CSV
    _baseExp       = 0;

    // POKEMON_STATS_CSV
    _effortYield[0] = 0;
    _effortYield[1] = 0;
    _effortYield[2] = 0;
    _effortYield[3] = 0;
    _effortYield[4] = 0;
    _effortYield[5] = 0;

    // moves
    levelMoves.clear();
    machineMoves.clear();
    tutorMoves.clear();
    eggMoves.clear();

    for (int i = 0; i < 100; ++i)
    {
        _expToLvl[i] = 0;
    }

}

int PokemonSpecies::getDexNum()
{
    return _dexNum;
}

string PokemonSpecies::getName()
{
    return _name;
}

Type PokemonSpecies::getType(int i)
{
    if (i != 0 && i != 1)
    {
        cerr << "ERROR - getType(" << i << ")" << endl;
        exit(1);
    }
    return _types[i];
}

int PokemonSpecies::getSpeciesAbility(int i)
{
    if (i < 0 || i > 2)
    {
        cerr << "ERROR - getSpeciesAbility(" << i << ")" << endl;
        exit(1);
    }
    return _abilities[i];
}

int PokemonSpecies::getGenderRate()
{
    return _genderRate;
}

int PokemonSpecies::getBaseStats(int i)
{
    if (i < 0 || i > 5)
    {
        cerr << "ERROR - getBaseStats(" << i << ")" << endl;
        exit(1);
    }
    return _baseStats[i];
}

int PokemonSpecies::getBaseExp()
{
    return _baseExp;
}

int PokemonSpecies::getEffortYield(int i)
{
    if (i < 0 || i > 5)
    {
        cerr << "ERROR - getEffortYield(" << i << ")" << endl;
        exit(1);
    }
    return _effortYield[i];
}

int PokemonSpecies::getCapRate()
{
    return _capRate;
}

int PokemonSpecies::getBaseHappiness()
{
    return _baseHappiness;
}

int PokemonSpecies::getGrowthRate()
{
    return _growthRate;
}

vector<LevelUpMoves> PokemonSpecies::getLevelUpMoves()
{
    return levelMoves;
}

vector<int> PokemonSpecies::getEggMoves()
{
    return eggMoves;
}

vector<int> PokemonSpecies::getTutorMoves()
{
    return tutorMoves;
}

vector<int> PokemonSpecies::getMachineMoves()
{
    return machineMoves;
}

int PokemonSpecies::getExpToLvl(int i)
{
    return _expToLvl[i];
}

void PokemonSpecies::setDexNum(int num)
{
    _dexNum = num;
}

void PokemonSpecies::setName(string name)
{
    _name = name;
}

void PokemonSpecies::setType(int index, int typeId)
{
    // _types[index] = typeId;
    _types[index].setTypeNum(typeId);
}

void PokemonSpecies::setSpeciesAbility(int index, int abilityId)
{
    _abilities[index] = abilityId;
}

void PokemonSpecies::setGenderRate(int value)
{
    _genderRate = value;
}

void PokemonSpecies::setBaseStat(int statId, int value)
{
    _baseStats[statId] = value;
}

void PokemonSpecies::setBaseExp(int num)
{
    _baseExp = num;
}

void PokemonSpecies::setEffortYield(int statId, int value)
{
    _effortYield[statId] = value;
}

void PokemonSpecies::setCapRate(int value)
{
    _capRate = value;
}

void PokemonSpecies::setBaseHappiness(int value)
{
    _baseHappiness = value;
}

void PokemonSpecies::setGrowthRate(int value)
{
    _growthRate = value;
}

void PokemonSpecies::setExpToLvl(int level, int value)
{
    _expToLvl[level] = value;
}

void PokemonSpecies::addLevelUpMoves(int level, int move_id, int order)
{
    levelMoves.push_back(LevelUpMoves(level,move_id,order));
    sort(levelMoves.begin(), levelMoves.end());
}

void PokemonSpecies::addEggMove(int moveId)
{
    eggMoves.push_back(moveId);
}

void PokemonSpecies::addTutorMove(int moveId)
{
    tutorMoves.push_back(moveId);
}

void PokemonSpecies::addMachineMove(int moveId)
{
    machineMoves.push_back(moveId);
}