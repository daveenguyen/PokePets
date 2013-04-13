#include <string>
#include <iostream>
using namespace std;

#include "PokemonSpecies.h"
#include "CSVReader.h"
#include "Parser.h"

PokemonSpecies::PokemonSpecies(CSVReader* reader, int dexNum)
{
    /* parse database file based on pokedex number
       then set these variables */
    _reader = reader;
    clear();
    _dexNum = dexNum;
    if (dexNum>0){
        initFromParser();
    }
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
    _types[0]     = 0;
    _types[1]     = 0;

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

void PokemonSpecies::initFromParser()
{

    // POKEMON_SPECIES_CSV
    _reader->openFile(POKEMON_SPECIES_CSV);
    int token = 0;

    do
    {
        _reader->readLine();
        _reader->readField();
        token = _reader->getField<int>();
    } while ( token < _dexNum && !_reader->isEof());

    // at 1
    while (_reader->getFieldIndex() < 8 && !_reader->isEol())
        _reader->readField();

    _genderRate    = _reader->getField<int>();            // pokemon_species 8

    _reader->readField();
    _capRate       = _reader->getField<int>();            // pokemon_species 9

    _reader->readField();
    _baseHappiness = _reader->getField<int>();            // pokemon_species 10

    while (_reader->getFieldIndex() < 14 && !_reader->isEol())
        _reader->readField();

    _growthRate    = _reader->getField<int>();            // pokemon_species 14


    // POKEMON_SPECIES_NAME
    _reader->openFile(POKEMON_SPECIES_NAMES_CSV);
    token = 0;

    while (true)
    {
        do
        {
            _reader->readLine();
            _reader->readField();
            token = _reader->getField<int>();
        } while ( token < _dexNum && !_reader->isEof());

        if (token != _dexNum || _reader->isEof()) break;

        _reader->readField();
        if (_reader->getField<int>() == LANGUAGE_ID)
        {
            _reader->readField();
            _name = _reader->getField<string>();
            break;
        }
    }


    // POKEMON_TYPES_CSV
    _reader->openFile(POKEMON_TYPES_CSV);
    token = 0;


    while (true)
    {
        do
        {
            _reader->readLine();
            _reader->readField();
            token = _reader->getField<int>();
        } while ( token < _dexNum && !_reader->isEof());

        if (token != _dexNum || _reader->isEof()) break;

        int this_type_id = 0;
        int this_slot = 0;
        _reader->readField();
        this_type_id = _reader->getField<int>();
        _reader->readField();
        this_slot = _reader->getField<int>();

        _types[this_slot-1] = this_type_id;
    }

    if (_types[1] == 0) _types[1] = _types[0];

    // POKEMON_ABILITIES_CSV
    _reader->openFile(POKEMON_ABILITIES_CSV);
    token = 0;

    while (true)
    {
        do
        {
            _reader->readLine();
            _reader->readField();
            token = _reader->getField<int>();
        } while ( token < _dexNum && !_reader->isEof());

        if (token != _dexNum || _reader->isEof()) break;

        int this_ability_id = 0;
        int this_slot = 0;

        _reader->readField();
        this_ability_id = _reader->getField<int>();
        _reader->readField();
        _reader->readField();
        this_slot = _reader->getField<int>();

        _abilities[this_slot-1] = this_ability_id;
    }

    // POKEMON_STATS_CSV
    _reader->openFile(POKEMON_STATS_CSV);
    token = 0;

    while (true)
    {
        do
        {
            _reader->readLine();
            _reader->readField();
            token = _reader->getField<int>();
        } while ( token < _dexNum && !_reader->isEof());

        if (token != _dexNum || _reader->isEof()) break;

        int this_slot   = 0;
        int this_base   = 0;
        int this_effort = 0;

        _reader->readField();
        this_slot = _reader->getField<int>();
        _reader->readField();
        this_base = _reader->getField<int>();
        _reader->readField();
        this_effort = _reader->getField<int>();

        _baseStats[this_slot-1]   = this_base;
        _effortYield[this_slot-1] = this_effort;
    }
    // POKEMON_CSV
    _reader->openFile(POKEMON_CSV);
    token = 0;

    while (true)
    {
        do
        {
            _reader->readLine();
            _reader->readField();
            token = _reader->getField<int>();
        } while ( token < _dexNum && !_reader->isEof());

        if (token != _dexNum || _reader->isEof()) break;


        while (_reader->getFieldIndex() < 4 && !_reader->isEol())
            _reader->readField();

        _baseExp = _reader->getField<int>();
    }


    // POKEMON_MOVES_CSV
    _reader->openFile(POKEMON_CSV);
    token = 0;

    while (true)
    {
        do
        {
            _reader->readLine();
            _reader->readField();
            token = _reader->getField<int>();
        } while ( token < _dexNum && !_reader->isEof());

        if (token != _dexNum || _reader->isEof()) break;

        int level   = 0;
        int move_id = 0;
        int order   = 0;
        int method  = 0;
        int version = 0;

        _reader->readField();
        version = _reader->getField<int>();
        _reader->readField();
        move_id = _reader->getField<int>();
        _reader->readField();
        method = _reader->getField<int>();
        _reader->readField();
        level = _reader->getField<int>();
        _reader->readField();
        order = _reader->getField<int>();

        if (version == VERSION_GROUP_ID)
        {
            switch (method)
            {
                case 1: {
                    levelMoves.push_back(LevelUpMoves(level,move_id,order));
                    break;
                }
                case 2: {
                    eggMoves.push_back(move_id);
                    break;
                }
                case 3: {
                    tutorMoves.push_back(move_id);
                    break;
                }
                case 4: {
                    machineMoves.push_back(move_id);
                    break;
                }
            }
        }
    }
    sort(levelMoves.begin(), levelMoves.end());

    // EXPERIENCE_CSV
    _reader->openFile(EXPERIENCE_CSV);
    token = 0;

    while (true)
    {
        do
        {
            _reader->readLine();
            _reader->readField();
            token = _reader->getField<int>();
        } while ( token < _growthRate && !_reader->isEof());

        if (token != _growthRate || _reader->isEof()) break;

        int lvl = 0;

        _reader->readField();
        lvl = _reader->getField<int>();
        _reader->readField();
        _expToLvl[lvl-1] = _reader->getField<int>();
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

int PokemonSpecies::getTypes(int i)
{
    if (i != 0 && i != 1)
    {
        cerr << "ERROR - getTypes(" << i << ")" << endl;
        exit(1);
    }
    return _types[i];
}

int PokemonSpecies::getAbilities(int i)
{
    if (i < 0 || i > 2)
    {
        cerr << "ERROR - getAbilities(" << i << ")" << endl;
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

void PokemonSpecies::setDexNum(int i)
{
    _dexNum = i;
}
