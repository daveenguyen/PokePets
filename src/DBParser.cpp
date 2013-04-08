#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

#include "DBParser.h"

#define POKEMON_CSV "../data/csv/pokemon.csv"
#define POKEMON_ABILITIES_CSV "../data/csv/pokemon_abilities.csv"
#define POKEMON_SPECIES_CSV "../data/csv/pokemon_species.csv"
#define POKEMON_STATS_CSV "../data/csv/pokemon_stats.csv"
#define POKEMON_TYPES_CSV "../data/csv/pokemon_types.csv"

// #define POKEMON_MOVES_CSV "../data/csv/pokemon_moves_edited.csv"
#define POKEMON_MOVES_CSV "../data/csv/pokemon_moves.csv"
// #define DEBUG

#define MAX_POKES 151

DBParser::DBParser(int dexNum) {
    if (dexNum<=0) {
        cout << "*** Invalid dexNum ***" << endl;
        exit(1); // let's not bother with doing a range
    }
    int maxPoke = 1;
    if (dexNum == 0) maxPoke = MAX_POKES;

    #ifdef DEBUG
        cout << endl << "** SPECIES **" << endl;
    #endif
    _dbPokeSpecies _pokeSpecies[maxPoke];
    parsePokeSpecies(_pokeSpecies, dexNum);

    #ifdef DEBUG
        cout << endl << "** STATS **" << endl;
    #endif
    _dbPokeStats _pokeStats[maxPoke];
    parsePokeStats(_pokeStats, dexNum);

    #ifdef DEBUG
        cout << endl << "** ABILITIES **" << endl;
    #endif
    _dbPokeAbilities _pokeAbilities[maxPoke];
    parsePokeAbilities(_pokeAbilities, dexNum);

    #ifdef DEBUG
        cout << endl << "** TYPES **" << endl;
    #endif
    _dbPokeTypes _pokeTypes[maxPoke];
    parsePokeTypes(_pokeTypes, dexNum);

    #ifdef DEBUG
        cout << endl << "** POKES **" << endl;
    #endif
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

    #ifdef DEBUG
        cout << "** THIS POKEMON **" << endl;
        cout << "cur_name         : " << cur_name          << endl;
        cout << "cur_types[0]     : " << cur_types[0]      << endl;
        cout << "cur_types[1]     : " << cur_types[1]      << endl;
        cout << "cur_abilities[0] : " << cur_abilities[0]  << endl;
        cout << "cur_abilities[1] : " << cur_abilities[1]  << endl;
        cout << "cur_abilities[2] : " << cur_abilities[2]  << endl;
        cout << "cur_genderRate   : " << cur_genderRate    << endl;
        cout << "cur_baseStats[0] : " << cur_baseStats[0]  << endl;
        cout << "cur_baseStats[1] : " << cur_baseStats[1]  << endl;
        cout << "cur_baseStats[2] : " << cur_baseStats[2]  << endl;
        cout << "cur_baseStats[3] : " << cur_baseStats[3]  << endl;
        cout << "cur_baseStats[4] : " << cur_baseStats[4]  << endl;
        cout << "cur_baseStats[5] : " << cur_baseStats[5]  << endl;
        cout << "cur_baseExp      : " << cur_baseExp       << endl;
        cout << "cur_onDeathEVs[0]: " << cur_onDeathEVs[0] << endl;
        cout << "cur_onDeathEVs[1]: " << cur_onDeathEVs[1] << endl;
        cout << "cur_onDeathEVs[2]: " << cur_onDeathEVs[2] << endl;
        cout << "cur_onDeathEVs[3]: " << cur_onDeathEVs[3] << endl;
        cout << "cur_onDeathEVs[4]: " << cur_onDeathEVs[4] << endl;
        cout << "cur_onDeathEVs[5]: " << cur_onDeathEVs[5] << endl;
        cout << "cur_capRate      : " << cur_capRate       << endl;
        cout << "cur_baseHappines : " << cur_baseHappiness << endl;
        cout << "cur_growthRate   : " << cur_growthRate    << endl;
    #endif

    // vector<_dbPokeMoves> moves;
    parsePokeMoves(&moves, dexNum);
    #ifdef DEBUG
        cout << endl << "** MOVES **" << endl;
    cout << moves.size() << endl;
    for (int i = 0; i < moves.size(); ++i) {
        cout << "_pokemon_id            : " << moves[i]._pokemon_id << endl;
        cout << "_version_group_id      : " << moves[i]._version_group_id << endl;
        cout << "_move_id               : " << moves[i]._move_id << endl;
        cout << "_pokemon_move_method_id: " << moves[i]._pokemon_move_method_id << endl;
        cout << "_level                 : " << moves[i]._level << endl;
        cout << "_order                 : " << moves[i]._order << endl << endl;
    }
    #endif
}

DBParser::~DBParser(){}

string DBParser::getName(){
    return cur_name;
}
int    DBParser::getTypes(int i){
    if (i != 0 && i != 1) {
        cout << "ERROR ON getTypes" << endl;
        cout << "index: " << i << endl;
        exit(1);
    }
    return cur_types[i];
}
int    DBParser::getAbilities(int i){
    if (i < 0 || i > 2) {
        cout << "ERROR ON getAbilities" << endl;
        cout << "index: " << i << endl;
        exit(1);
    }
    return cur_abilities[i];
}
int    DBParser::getGenderRate(){
    return cur_genderRate;
}
int    DBParser::getBaseStats(int i){
    if (i < 0 || i > 5) {
        cout << "ERROR ON getBaseStats" << endl;
        cout << "index: " << i << endl;
        exit(1);
    }
    return cur_baseStats[i];
}
int    DBParser::getBaseExp(){
    return cur_baseExp;
}
int    DBParser::getOnDeathEVs(int i){
    if (i < 0 || i > 5) {
        cout << "ERROR ON getOnDeathEVs" << endl;
        cout << "index: " << i << endl;
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
        cout << "Could not open " << POKEMON_SPECIES_CSV;
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

        // for debugging
        #ifdef DEBUG
            cout << "                     _id: " << _pokeSpecies[i]._id << endl;
            cout << "             _identifier: " << _pokeSpecies[i]._identifier << endl;
            cout << "          _generation_id: " << _pokeSpecies[i]._generation_id << endl;
            cout << "_evolves_from_species_id: " << _pokeSpecies[i]._evolves_from_species_id << endl;
            cout << "     _evolution_chain_id: " << _pokeSpecies[i]._evolution_chain_id << endl;
            cout << "               _color_id: " << _pokeSpecies[i]._color_id << endl;
            cout << "               _shape_id: " << _pokeSpecies[i]._shape_id << endl;
            cout << "             _habitat_id: " << _pokeSpecies[i]._habitat_id << endl;
            cout << "            _gender_rate: " << _pokeSpecies[i]._gender_rate << endl;
            cout << "           _capture_rate: " << _pokeSpecies[i]._capture_rate << endl;
            cout << "         _base_happiness: " << _pokeSpecies[i]._base_happiness << endl;
            cout << "                _is_baby: " << _pokeSpecies[i]._is_baby << endl;
            cout << "          _hatch_counter: " << _pokeSpecies[i]._hatch_counter << endl;
            cout << " _has_gender_differences: " << _pokeSpecies[i]._has_gender_differences << endl;
            cout << "         _growth_rate_id: " << _pokeSpecies[i]._growth_rate_id << endl;
            cout << "       _forms_switchable: " << _pokeSpecies[i]._forms_switchable << endl;
            cout << "                  _order: " << _pokeSpecies[i]._order << endl;
            cout << "         _conquest_order: " << _pokeSpecies[i]._conquest_order << endl;
        #endif

        if (dexNum != 0) break; // break out if not doing all pokemons
    }
}

void DBParser::parsePokeStats(_dbPokeStats* _pokeStats, int dexNum){

    // open file for parsing
    ifstream ifs(POKEMON_STATS_CSV);
    if(!ifs.is_open())
    {
        cout << "Could not open " << POKEMON_STATS_CSV;
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
            // for debugging
        }
        #ifdef DEBUG
            cout << "  _pokemon_id: " << _pokeStats[i]._pokemon_id << endl;
            cout << "_base_stat[0]: " << _pokeStats[i]._base_stat[0] << '\t';
            cout << "_effort[0]: " << _pokeStats[i]._effort[0] << endl;

            cout << "_base_stat[1]: " << _pokeStats[i]._base_stat[1] << '\t';
            cout << "_effort[1]: " << _pokeStats[i]._effort[1] << endl;

            cout << "_base_stat[2]: " << _pokeStats[i]._base_stat[2] << '\t';
            cout << "_effort[2]: " << _pokeStats[i]._effort[2] << endl;

            cout << "_base_stat[3]: " << _pokeStats[i]._base_stat[3] << '\t';
            cout << "_effort[3]: " << _pokeStats[i]._effort[3] << endl;

            cout << "_base_stat[4]: " << _pokeStats[i]._base_stat[4] << '\t';
            cout << "_effort[4]: " << _pokeStats[i]._effort[4] << endl;

            cout << "_base_stat[5]: " << _pokeStats[i]._base_stat[5] << '\t';
            cout << "_effort[5]: " << _pokeStats[i]._effort[5] << endl;
        #endif
        if (dexNum != 0) break; // break out if not doing all pokemons
    }
}

void DBParser::parsePokeAbilities(_dbPokeAbilities* _pokeAbilities, int dexNum){
    // open file for parsing
    ifstream ifs(POKEMON_ABILITIES_CSV);
    if(!ifs.is_open())
    {
        cout << "Could not open " << POKEMON_ABILITIES_CSV;
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

                    // for debugging
                    #ifdef DEBUG
                        cout << "id: " << _pokeAbilities[i]._pokemon_id << endl;
                        cout << "1: "  << _pokeAbilities[i]._abilities[0] << endl;
                        cout << "2: "  << _pokeAbilities[i]._abilities[1] << endl;
                        cout << "3: "  << _pokeAbilities[i]._abilities[2] << endl << endl;
                    #endif

                    ++i;
                    // cout << i << " INCREMENT " << this_poke_id << endl;
                    if (i >= MAX_POKES) break;
                    clearStruct(&_pokeAbilities[i]);
                }
            }
            else {
                if (this_poke_id != _pokeAbilities[i]._pokemon_id) {

                    // for debugging
                    #ifdef DEBUG
                        cout << "id: " << _pokeAbilities[i]._pokemon_id << endl;
                        cout << "1: "  << _pokeAbilities[i]._abilities[0] << endl;
                        cout << "2: "  << _pokeAbilities[i]._abilities[1] << endl;
                        cout << "3: "  << _pokeAbilities[i]._abilities[2] << endl << endl;
                    #endif

                    ++i;
                    // cout << i << " INCREMENT " << this_poke_id << endl;
                    if (i >= MAX_POKES) break;
                    clearStruct(&_pokeAbilities[i]);
                }
            }
        } else {
            if (this_poke_id != dexNum) {

                // for debugging
                #ifdef DEBUG
                    cout << "id: " << _pokeAbilities[i]._pokemon_id << endl;
                    cout << "1: "  << _pokeAbilities[i]._abilities[0] << endl;
                    cout << "2: "  << _pokeAbilities[i]._abilities[1] << endl;
                    cout << "3: "  << _pokeAbilities[i]._abilities[2] << endl << endl;
                #endif

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
        cout << "Could not open " << POKEMON_TYPES_CSV;
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

                    // for debugging
                    #ifdef DEBUG
                        cout << "id: " << _pokeTypes[i]._pokemon_id << endl;
                        cout << "1: "  << _pokeTypes[i]._types[0] << endl;
                        cout << "2: "  << _pokeTypes[i]._types[1] << endl;
                    #endif

                    ++i;
                    // cout << i << " INCREMENT " << this_poke_id << endl;
                    if (i >= MAX_POKES) break;
                    clearStruct(&_pokeTypes[i]);
                }
            }
            else {
                if (this_poke_id != _pokeTypes[i]._pokemon_id) {

                    // for debugging
                    #ifdef DEBUG
                        cout << "id: " << _pokeTypes[i]._pokemon_id << endl;
                        cout << "1: "  << _pokeTypes[i]._types[0] << endl;
                        cout << "2: "  << _pokeTypes[i]._types[1] << endl;
                    #endif

                    ++i;
                    // cout << i << " INCREMENT " << this_poke_id << endl;
                    if (i >= MAX_POKES) break;
                    clearStruct(&_pokeTypes[i]);
                }
            }
        } else {
            if (this_poke_id != dexNum) {

                // for debugging
                #ifdef DEBUG
                        cout << "id: " << _pokeTypes[i]._pokemon_id << endl;
                        cout << "1: "  << _pokeTypes[i]._types[0] << endl;
                        cout << "2: "  << _pokeTypes[i]._types[1] << endl;
                #endif

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
        cout << "Could not open " << POKEMON_CSV;
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
                // for debugging
                #ifdef DEBUG
                    cout << "             _id: " << _poke[i]._id << endl;
                    cout << "     _species_id: " << _poke[i]._species_id << endl;
                    cout << "         _height: " << _poke[i]._height << endl;
                    cout << "         _weight: " << _poke[i]._weight << endl;
                    cout << "_base_experience: " << _poke[i]._base_experience << endl;
                    cout << "          _order: " << _poke[i]._order << endl;
                    cout << "     _is_default: " << _poke[i]._is_default << endl;
                #endif
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
        cout << "Could not open " << POKEMON_MOVES_CSV;
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

                    // for debugging
                    #ifdef DEBUG

                    #endif

                    ++i;
                    if (i >= MAX_POKES) break;
                    clearStruct(&_pokeMoves);
                }
            }
            else {
                if (this_poke_id != _pokeMoves._pokemon_id) {

                    // for debugging
                    #ifdef DEBUG

                    #endif

                    ++i;
                    if (i >= MAX_POKES) break;
                    clearStruct(&_pokeMoves);
                }
            }
        } else {
            if (this_poke_id != dexNum) {

                // for debugging
                #ifdef DEBUG

                #endif

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


// testing
// int main() {
//     cout << "Enter a pokedex number or 0 for all: ";
//     int dexNum;
//     cin  >> dexNum;
//     cout << endl;
//     DBParser db(dexNum);
//     return 0;
// }