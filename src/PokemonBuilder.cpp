#include "PokemonBuilder.h"
#include "Pokemon.h"
#include "CSVReader.h"

void PokemonBuilder::initSpecies()
{
    _dexNum = _pkmn->getDexNum();

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
    {
        _reader->readField();
    }

    // pokemon_species 8
    _pkmn->setGenderRate(_reader->getField<int>());

    // pokemon_species 9
    _reader->readField();
    _pkmn->setCapRate(_reader->getField<int>());

    // pokemon_species 10
    _reader->readField();
    _pkmn->setBaseHappiness(_reader->getField<int>());

    while (_reader->getFieldIndex() < 14 && !_reader->isEol())
    {
        _reader->readField();
    }

    // pokemon_species 14
    _pkmn->setGrowthRate(_reader->getField<int>());



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

        if (token != _dexNum || _reader->isEof())
        {
            break;
        }

        _reader->readField();
        if (_reader->getField<int>() == LANGUAGE_ID)
        {
            _reader->readField();
            _pkmn->setName(_reader->getField<string>());
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

        _pkmn->setType(this_slot-1, this_type_id);
    }

    if (_pkmn->getType(1).getTypeNum() == 0) _pkmn->setType(1, _pkmn->getType(0).getTypeNum());


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

        _pkmn->setSpeciesAbility(this_slot-1, this_ability_id);
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

        _pkmn->setBaseStat(this_slot-1, this_base);
        _pkmn->setEffortYield(this_slot-1, this_effort);
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

        _pkmn->setBaseExp(_reader->getField<int>());
    }


// POKEMON_MOVES_CSV
    _reader->openFile(POKEMON_MOVES_CSV);
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
                    _pkmn->addLevelUpMoves(level,move_id,order);
                    break;
                }
                case 2: {
                    _pkmn->addEggMove(move_id);
                    break;
                }
                case 3: {
                    _pkmn->addTutorMove(move_id);
                    break;
                }
                case 4: {
                    _pkmn->addMachineMove(move_id);
                    break;
                }
            }
        }
    }
    //sort(levelMoves.begin(), levelMoves.end());

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
        } while ( token < _pkmn->getGrowthRate() && !_reader->isEof());

        if (token != _pkmn->getGrowthRate() || _reader->isEof()) break;

        int lvl = 0;

        _reader->readField();
        lvl = _reader->getField<int>();
        _reader->readField();
        _pkmn->setExpToLvl(lvl-1, _reader->getField<int>());
    }
}


void PokemonBuilder::setReader(CSVReader* myReader)
{
    _reader = myReader;
}

void PokemonBuilder::setPokemon(Pokemon* myPkmn)
{
    _pkmn = myPkmn;
}
