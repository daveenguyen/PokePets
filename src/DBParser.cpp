#include <fstream>
#include <sstream>
#include <iostream>
#include <cstdlib> // for exit()
using namespace std;
#include "DBParser.h"

#define POKEMON_CSV           "../data/csv/pokemon.csv"
#define POKEMON_MOVES_CSV     "../data/csv/pokemon_moves.csv"
#define POKEMON_STATS_CSV     "../data/csv/pokemon_stats.csv"
#define POKEMON_TYPES_CSV     "../data/csv/pokemon_types.csv"
#define POKEMON_SPECIES_CSV   "../data/csv/pokemon_species.csv"
#define POKEMON_ABILITIES_CSV "../data/csv/pokemon_abilities.csv"

#define TYPES_CSV             "../data/csv/types.csv"
#define TYPE_EFFICACY_CSV     "../data/csv/type_efficacy.csv"

#define MAX_POKES 151

DBParser::DBParser() {
    cur_name          = "";
    cur_types[0]      = 0;
    cur_types[1]      = 0;
    cur_abilities[0]  = 0;
    cur_abilities[1]  = 0;
    cur_abilities[2]  = 0;
    cur_genderRate    = 0;
    cur_baseStats[0]  = 0;
    cur_baseStats[1]  = 0;
    cur_baseStats[2]  = 0;
    cur_baseStats[3]  = 0;
    cur_baseStats[4]  = 0;
    cur_baseStats[5]  = 0;
    cur_baseExp       = 0;
    cur_onDeathEVs[0] = 0;
    cur_onDeathEVs[1] = 0;
    cur_onDeathEVs[2] = 0;
    cur_onDeathEVs[3] = 0;
    cur_onDeathEVs[4] = 0;
    cur_onDeathEVs[5] = 0;
    cur_capRate       = 0;
    cur_baseHappiness = 0;
    cur_growthRate    = 0;
}

DBParser::DBParser(int dexNum) {

    if (dexNum<=0) {
        cerr << "ERROR - Invalid dexNum: " << dexNum << endl;
        exit(1); // let's not bother with doing a range
    }

    int maxPoke = 1;
    if (dexNum == 0) maxPoke = MAX_POKES;

    // ** SPECIES **
    _dbPokeSpecies _pokeSpecies[maxPoke];
    parsePokeSpecies(_pokeSpecies, dexNum);

    // ** STATS **
    _dbPokeStats _pokeStats[maxPoke];
    parsePokeStats(_pokeStats, dexNum);

    // ** ABILITIES **
    _dbPokeAbilities _pokeAbilities[maxPoke];
    parsePokeAbilities(_pokeAbilities, dexNum);

    // ** TYPES **
    _dbPokeTypes _pokeTypes[maxPoke];
    parsePokeTypes(_pokeTypes, dexNum);

    // ** POKES **
    _dbPoke _poke[maxPoke];
    parsePoke(_poke, dexNum);

    cur_name          = _pokeSpecies[0]._identifier;
    cur_types[0]      = _pokeTypes[0]._types[0];
    cur_types[1]      = _pokeTypes[0]._types[1];
    cur_abilities[0]  = _pokeAbilities[0]._abilities[0];
    cur_abilities[1]  = _pokeAbilities[0]._abilities[1];
    cur_abilities[2]  = _pokeAbilities[0]._abilities[2];
    cur_genderRate    = _pokeSpecies[0]._gender_rate;
    cur_baseStats[0]  = _pokeStats[0]._base_stat[0];
    cur_baseStats[1]  = _pokeStats[0]._base_stat[1];
    cur_baseStats[2]  = _pokeStats[0]._base_stat[2];
    cur_baseStats[3]  = _pokeStats[0]._base_stat[3];
    cur_baseStats[4]  = _pokeStats[0]._base_stat[4];
    cur_baseStats[5]  = _pokeStats[0]._base_stat[5];
    cur_baseExp       = _poke[0]._base_experience;
    cur_onDeathEVs[0] = _pokeStats[0]._effort[0];
    cur_onDeathEVs[1] = _pokeStats[0]._effort[1];
    cur_onDeathEVs[2] = _pokeStats[0]._effort[2];
    cur_onDeathEVs[3] = _pokeStats[0]._effort[3];
    cur_onDeathEVs[4] = _pokeStats[0]._effort[4];
    cur_onDeathEVs[5] = _pokeStats[0]._effort[5];
    cur_capRate       = _pokeSpecies[0]._capture_rate;
    cur_baseHappiness = _pokeSpecies[0]._base_happiness;
    cur_growthRate    = _pokeSpecies[0]._growth_rate_id;

    // vector<_dbPokeMoves> moves;
    parsePokeMoves(&moves, dexNum);
}

string DBParser::getName(){
    string thisName = cur_name;
    thisName[0] = toupper(thisName[0]); // capitalize first letter
    return thisName;
}

int    DBParser::getTypes(int i){
    if (i != 0 && i != 1) {
        cerr << "ERROR - getTypes(" << i << ")" << endl;
        exit(1);
    }
    return cur_types[i];
}
int    DBParser::getAbilities(int i){
    if (i < 0 || i > 2) {
        cerr << "ERROR - getAbilities(" << i << ")" << endl;
        exit(1);
    }
    return cur_abilities[i];
}
int    DBParser::getGenderRate(){
    return cur_genderRate;
}
int    DBParser::getBaseStats(int i){
    if (i < 0 || i > 5) {
        cerr << "ERROR - getBaseStats(" << i << ")" << endl;
        exit(1);
    }
    return cur_baseStats[i];
}

int    DBParser::getBaseExp(){
    return cur_baseExp;
}

int    DBParser::getOnDeathEVs(int i){
    if (i < 0 || i > 5) {
        cerr << "ERROR - getOnDeathEVs(" << i << ")" << endl;
        exit(1);
    }
    return cur_onDeathEVs[i];
}
int    DBParser::getCapRate(){
    return cur_capRate;
}
int    DBParser::getBaseHappiness(){
    return cur_baseHappiness;
}
int    DBParser::getGrowthRate(){
    return cur_growthRate;
}

string DBParser::getTypeString(int typeNum) {

    parseType(&cur_type, typeNum);
    string thisType = cur_type._identifier;
    if (typeNum == 0) thisType = "none";
    thisType[0] = toupper(thisType[0]); // capitalize first letter
    return thisType;
}

template <class T>
void DBParser::parseLine(stringstream &ss, T &t) {
    if (ss.peek() == ',') {
        ss.ignore();
    }
    else {
        string field;
        getline(ss, field, ',');
        stringstream fs(field);
        fs >> t;
    }
}

void DBParser::parsePokeSpecies(_dbPokeSpecies* _pokeSpecies, int dexNum){

    // open file for parsing
    ifstream ifs(POKEMON_SPECIES_CSV);
    if(!ifs.is_open())
    {
        cerr << "Could not open " << POKEMON_SPECIES_CSV;
        exit(1);
    }

    /* read a line */
    string line;           // string to store line

    getline(ifs, line);     // get rid of title line

    for (int i = 1; i < dexNum; ++i) {
        getline(ifs, line); // discards line before dexNum if doing singles
    }

    for (int i = 0; i < MAX_POKES; ++i) {
        getline(ifs, line);    // get line

        // use stringstream to tokenize line
        stringstream ss(line);

        // clear pokespecies first
        clearStruct(&_pokeSpecies[i]);

        // parse the line by commas and store into second argument
        parseLine(ss, _pokeSpecies[i]._id);
        parseLine(ss, _pokeSpecies[i]._identifier);
        parseLine(ss, _pokeSpecies[i]._generation_id);
        parseLine(ss, _pokeSpecies[i]._evolves_from_species_id);
        parseLine(ss, _pokeSpecies[i]._evolution_chain_id);
        parseLine(ss, _pokeSpecies[i]._color_id);
        parseLine(ss, _pokeSpecies[i]._shape_id);
        parseLine(ss, _pokeSpecies[i]._habitat_id);
        parseLine(ss, _pokeSpecies[i]._gender_rate);
        parseLine(ss, _pokeSpecies[i]._capture_rate);
        parseLine(ss, _pokeSpecies[i]._base_happiness);
        parseLine(ss, _pokeSpecies[i]._is_baby);
        parseLine(ss, _pokeSpecies[i]._hatch_counter);
        parseLine(ss, _pokeSpecies[i]._has_gender_differences);
        parseLine(ss, _pokeSpecies[i]._growth_rate_id);
        parseLine(ss, _pokeSpecies[i]._forms_switchable);
        parseLine(ss, _pokeSpecies[i]._order);
        parseLine(ss, _pokeSpecies[i]._conquest_order);

        if (dexNum != 0) break; // break out if not doing all pokemons
    }
}

void DBParser::parsePokeStats(_dbPokeStats* _pokeStats, int dexNum){

    // open file for parsing
    ifstream ifs(POKEMON_STATS_CSV);
    if(!ifs.is_open())
    {
        cerr << "Could not open " << POKEMON_STATS_CSV;
        exit(1);
    }

    /* read a line */
    string line;           // string to store line

    getline(ifs, line);     // get rid of title line

    for (int i = 1; i < dexNum; ++i) {
        for (int j = 0; j < 6; ++j)
        getline(ifs, line); // discards line before dexNum if doing singles
    }

    for (int i = 0; i < MAX_POKES; ++i) {
        clearStruct(&_pokeStats[i]);
        for (int j = 0; j < 6; ++j) {
            getline(ifs, line);    // get line

            // use stringstream to tokenize line
            stringstream ss(line);

            int k;

            // parse the line by commas and store into second argument
            parseLine(ss, _pokeStats[i]._pokemon_id);
            parseLine(ss, k); // skip next field

            if ((k-1)!=j) {
                cout << "PARSEPOKESTATS PROBLEM" << endl;
                cout << "ERROR: j= " << j << " k= " << k << endl;
                cout << "i = " << i << endl;
                cout << "line = " << line << endl;
                exit(1);
            }

            parseLine(ss, _pokeStats[i]._base_stat[j]); // replaced by this line
            parseLine(ss, _pokeStats[i]._effort[j]);
        }
        if (dexNum != 0) break; // break out if not doing all pokemons
    }
}

void DBParser::parsePokeAbilities(_dbPokeAbilities* _pokeAbilities, int dexNum){
    // open file for parsing
    ifstream ifs(POKEMON_ABILITIES_CSV);
    if(!ifs.is_open())
    {
        cerr << "Could not open " << POKEMON_ABILITIES_CSV;
        exit(1);
    }

    /* read a line */
    string line;            // string to store line
    getline(ifs, line);     // get rid of title line



    int i = 0;
    clearStruct(&_pokeAbilities[i]);

    while (i < MAX_POKES) {

        stringstream ss;        // stringstream for storing tokenized value
        int this_poke_id;

        do {
            getline(ifs, line);    // get line
            ss.str(line);
            parseLine(ss, this_poke_id);
        } while (dexNum!=0 && this_poke_id < dexNum);

        if (dexNum == 0) {
            if (i == 0) {
                if (this_poke_id != 1) {
                    ++i;
                    // cout << i << " INCREMENT " << this_poke_id << endl;
                    if (i >= MAX_POKES) break;
                    clearStruct(&_pokeAbilities[i]);
                }
            }
            else {
                if (this_poke_id != _pokeAbilities[i]._pokemon_id) {
                    ++i;
                    // cout << i << " INCREMENT " << this_poke_id << endl;
                    if (i >= MAX_POKES) break;
                    clearStruct(&_pokeAbilities[i]);
                }
            }
        } else {
            if (this_poke_id != dexNum) {
                break;
            }
        }

        int this_ability_id = 0;
        int this_ishidden = 0;
        int this_slot = 0;

        parseLine(ss, this_ability_id);
        parseLine(ss, this_ishidden);
        parseLine(ss, this_slot);


        _pokeAbilities[i]._pokemon_id             = this_poke_id;
        _pokeAbilities[i]._abilities[this_slot-1] = this_ability_id;
    }

        // cout << "DONE STORING ABILITY" << endl;
        // if (dexNum != 0) break; // break out if not doing all pokemons
}

void DBParser::parsePokeTypes(_dbPokeTypes* _pokeTypes, int dexNum){
    // open file for parsing
    ifstream ifs(POKEMON_TYPES_CSV);
    if(!ifs.is_open())
    {
        cerr << "Could not open " << POKEMON_TYPES_CSV;
        exit(1);
    }

    /* read a line */
    string line;            // string to store line
    getline(ifs, line);     // get rid of title line



    int i = 0;
    clearStruct(&_pokeTypes[i]);

    while (i < MAX_POKES) {

        stringstream ss;        // stringstream for storing tokenized value
        int this_poke_id;

        do {
            getline(ifs, line);    // get line
            ss.str(line);
            parseLine(ss, this_poke_id);
        } while (dexNum!=0 && this_poke_id < dexNum);

        if (dexNum == 0) {
            if (i == 0) {
                if (this_poke_id != 1) {
                    ++i;
                    // cout << i << " INCREMENT " << this_poke_id << endl;
                    if (i >= MAX_POKES) break;
                    clearStruct(&_pokeTypes[i]);
                }
            }
            else {
                if (this_poke_id != _pokeTypes[i]._pokemon_id) {
                    ++i;
                    // cout << i << " INCREMENT " << this_poke_id << endl;
                    if (i >= MAX_POKES) break;
                    clearStruct(&_pokeTypes[i]);
                }
            }
        } else {
            if (this_poke_id != dexNum) {
                break;
            }
        }

        int this_type_id = 0;
        int this_slot = 0;

        parseLine(ss, this_type_id);
        parseLine(ss, this_slot);


        _pokeTypes[i]._pokemon_id         = this_poke_id;
        _pokeTypes[i]._types[this_slot-1] = this_type_id;
    }
}

void DBParser::parsePoke(_dbPoke* _poke, int dexNum){
    // open file for parsing
    ifstream ifs(POKEMON_CSV);
    if(!ifs.is_open())
    {
        cerr << "Could not open " << POKEMON_CSV;
        exit(1);
    }

    /* read a line */
    string line;            // string to store line
    getline(ifs, line);     // get rid of title line


    int i = 0;
    clearStruct(&_poke[i]);

    while (i < MAX_POKES) {

        stringstream ss;        // stringstream for storing tokenized value
        int this_id;

        do {
            getline(ifs, line);    // get line
            ss.str(line);
            parseLine(ss, this_id);
        } while (dexNum!=0 && this_id < dexNum);

        if (dexNum == 0) {
            if (i == 0) {
                if (this_id != 1) {
                    ++i;
                    if (i >= MAX_POKES) break;
                    clearStruct(&_poke[i]);
                }
            }
            else {
                if (this_id != _poke[i]._id) {
                    ++i;
                    if (i >= MAX_POKES) break;
                    clearStruct(&_poke[i]);
                }
            }
        } else {
            if (this_id != dexNum) {
                break;
            }
        }

        _poke[i]._id         = this_id;
        parseLine(ss, _poke[i]._species_id);
        parseLine(ss, _poke[i]._height);
        parseLine(ss, _poke[i]._weight);
        parseLine(ss, _poke[i]._base_experience);
        parseLine(ss, _poke[i]._order);
        parseLine(ss, _poke[i]._is_default);
    }
}


void DBParser::parsePokeMoves(vector<_dbPokeMoves>* moves, int dexNum){

    // open file for parsing
    ifstream ifs(POKEMON_MOVES_CSV);
    if(!ifs.is_open())
    {
        cerr << "Could not open " << POKEMON_MOVES_CSV;
        exit(1);
    }


    /* read a line */
    string line;            // string to store line
    getline(ifs, line);     // get rid of title line

    int i = 0;
    _dbPokeMoves _pokeMoves;

    while (i < MAX_POKES) {

        clearStruct(&_pokeMoves);

        stringstream ss;        // stringstream for storing tokenized value
        int this_poke_id=0;

        do {
            getline(ifs, line);    // get line
            ss.str(line);
            parseLine(ss, this_poke_id);
        } while (dexNum!=0 && this_poke_id < dexNum);

        if (dexNum == 0) {
            if (i == 0) {
                if (this_poke_id != 1) {
                    ++i;
                    if (i >= MAX_POKES) break;
                    clearStruct(&_pokeMoves);
                }
            }
            else {
                if (this_poke_id != _pokeMoves._pokemon_id) {
                    ++i;
                    if (i >= MAX_POKES) break;
                    clearStruct(&_pokeMoves);
                }
            }
        } else {
            if (this_poke_id != dexNum) {
                break;
            }
        }

        _pokeMoves._pokemon_id = this_poke_id;
        parseLine(ss, _pokeMoves._version_group_id);
        parseLine(ss, _pokeMoves._move_id);
        parseLine(ss, _pokeMoves._pokemon_move_method_id);
        parseLine(ss, _pokeMoves._level);
        parseLine(ss, _pokeMoves._order);
        if (_pokeMoves._version_group_id == 14 && _pokeMoves._pokemon_move_method_id > 0 && _pokeMoves._pokemon_move_method_id < 5)
            moves->push_back(_pokeMoves);
    }
}


void DBParser::parseType(_type* type, int typeNum){

    // open file for parsing
    ifstream ifs(TYPE_EFFICACY_CSV);
    if(!ifs.is_open())
    {
        cerr << "Could not open " << TYPE_EFFICACY_CSV;
        exit(1);
    }

    /* read a line */
    string line;            // string to store line
    getline(ifs, line);     // get rid of title line

    int i = 0;
    clearStruct(type);

    while (i < MAX_POKES) {


        stringstream ss;        // stringstream for storing tokenized value
        int damage_type_id=0;

        do {
            getline(ifs, line);    // get line
            ss.str(line);
            parseLine(ss, damage_type_id);
        } while (damage_type_id < typeNum && !ifs.eof());

        if (damage_type_id != typeNum || ifs.eof()) {
            break;
        }

        // type._identifier = this_dmg_type_id;
        int target_type_id = 0;
        int damage_factor  = 0;
        parseLine(ss, target_type_id);
        parseLine(ss, damage_factor);

        if (target_type_id - 1 == type->_damage_factor.size())
            type->_damage_factor.push_back(damage_factor);
    }

    ifs.close();
    ifs.open(TYPES_CSV);
    if(!ifs.is_open())
    {
        cerr << "Could not open " << TYPES_CSV;
        exit(1);
    }



    while (i < MAX_POKES) {

        stringstream ss;        // stringstream for storing tokenized value
        int _type_id=0;

        do {
            getline(ifs, line);    // get line
            ss.str(line);
            parseLine(ss, _type_id);
        } while (_type_id < typeNum && !ifs.eof());

        if (_type_id != typeNum || ifs.eof()) {
            break;
        }

        parseLine(ss, type->_identifier);
    }
}

void DBParser::clearStruct(_dbPokeSpecies* _pokeSpecies) {
    _pokeSpecies->_id = 0;
    _pokeSpecies->_identifier = "";
    _pokeSpecies->_generation_id = 0;
    _pokeSpecies->_evolves_from_species_id = 0;
    _pokeSpecies->_evolution_chain_id = 0;
    _pokeSpecies->_color_id = 0;
    _pokeSpecies->_shape_id = 0;
    _pokeSpecies->_habitat_id = 0;
    _pokeSpecies->_gender_rate = 0;
    _pokeSpecies->_capture_rate = 0;
    _pokeSpecies->_base_happiness = 0;
    _pokeSpecies->_is_baby = 0;
    _pokeSpecies->_hatch_counter = 0;
    _pokeSpecies->_has_gender_differences = 0;
    _pokeSpecies->_growth_rate_id = 0;
    _pokeSpecies->_forms_switchable = 0;
    _pokeSpecies->_order = 0;
    _pokeSpecies->_conquest_order = 0;
}

void DBParser::clearStruct(_dbPokeStats* _pokeStats) {
    _pokeStats->_pokemon_id   = 0;
    _pokeStats->_base_stat[0] = 0;
    _pokeStats->_base_stat[1] = 0;
    _pokeStats->_base_stat[2] = 0;
    _pokeStats->_base_stat[3] = 0;
    _pokeStats->_base_stat[4] = 0;
    _pokeStats->_base_stat[5] = 0;
    _pokeStats->_effort[0]    = 0;
    _pokeStats->_effort[1]    = 0;
    _pokeStats->_effort[2]    = 0;
    _pokeStats->_effort[3]    = 0;
    _pokeStats->_effort[4]    = 0;
    _pokeStats->_effort[5]    = 0;
}

void DBParser::clearStruct(_dbPokeAbilities* _pokeAbilities) {
    _pokeAbilities->_pokemon_id   = 0;
    _pokeAbilities->_abilities[0] = 0;
    _pokeAbilities->_abilities[1] = 0;
}

void DBParser::clearStruct(_dbPokeTypes* _pokeTypes) {
    _pokeTypes->_pokemon_id = 0;
    _pokeTypes->_types[0]   = 0;
    _pokeTypes->_types[1]   = 0;
}

void DBParser::clearStruct(_dbPoke* _poke) {
    _poke->_id = 0;
    _poke->_species_id = 0;
    _poke->_height = 0;
    _poke->_weight = 0;
    _poke->_base_experience = 0;
    _poke->_order = 0;
    _poke->_is_default = 0;
}

void DBParser::clearStruct(_dbPokeMoves* _pokeMoves) {
    _pokeMoves->_pokemon_id = 0;
    _pokeMoves->_version_group_id = 0;
    _pokeMoves->_move_id = 0;
    _pokeMoves->_pokemon_move_method_id = 0;
    _pokeMoves->_level = 0;
    _pokeMoves->_order = 0;
}

void DBParser::clearStruct(_type* _t) {
    _t->_identifier = "";
    _t->_damage_factor.clear();
}