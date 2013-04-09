#include <fstream>
#include <sstream>
#include <iostream>
#include <cstdlib> // for exit()
using namespace std;
#include "DBParser.h"

#define POKEMON_CSV                 "../data/csv/pokemon.csv"
#define POKEMON_MOVES_CSV           "../data/csv/pokemon_moves.csv"
#define POKEMON_STATS_CSV           "../data/csv/pokemon_stats.csv"
#define POKEMON_TYPES_CSV           "../data/csv/pokemon_types.csv"
#define POKEMON_SPECIES_CSV         "../data/csv/pokemon_species.csv"
#define POKEMON_ABILITIES_CSV       "../data/csv/pokemon_abilities.csv"
#define POKEMON_SPECIES_NAMES_CSV   "../data/csv/pokemon_species_names.csv"

#define TYPES_CSV                   "../data/csv/types.csv"
#define TYPE_EFFICACY_CSV           "../data/csv/type_efficacy.csv"

#define NATURES_CSV                   "../data/csv/natures.csv"
#define NATURE_NAMES_CSV           "../data/csv/nature_names.csv"

#define LANGUAGE_ID 9 // 9 for english

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

DBParser::DBParser(int num, int mode) {

    switch (mode) {

        // PokemonSpecies
        case 0:
        {
            initPokemonSpecies(num);
            break;
        }

        // Type Efficacy
        case 1:
        {
            parseType(&cur_type, num);
            break;
        }

        case 2:
        {
            parseNature(&cur_nature, num);
            break;
        }

    }
}

string DBParser::getName(){
    string thisName = cur_name;
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

string DBParser::getTypeString() {
    string thisType = cur_type._identifier;
    thisType[0] = toupper(thisType[0]); // capitalize first letter
    return thisType;
}

int DBParser::getTypeEfficacy(int typeNum) {
    if (typeNum <= 0)
    {
        cerr << "ERROR - getTypeEfficacy(" << typeNum << ")" << endl;
    }
    return cur_type._damage_factor[typeNum-1];
}

int DBParser::getNatureIncStat(){
    return cur_nature._increased_stat_id;
}

int DBParser::getNatureDecStat(){
    return cur_nature._decreased_stat_id;
}

string DBParser::getNatureString(){
    return cur_nature._identifier;
}


void DBParser::initPokemonSpecies(int dexNum) {

    if (dexNum<=0) {
        cerr << "ERROR - Invalid dexNum: " << dexNum << endl;
        exit(1); // let's not bother with doing a range
    }

    // ** SPECIES **
    _dbPokeSpecies _pokeSpecies;
    parsePokeSpecies(&_pokeSpecies, dexNum);

    // ** STATS **
    _dbPokeStats _pokeStats;
    parsePokeStats(&_pokeStats, dexNum);

    // ** ABILITIES **
    _dbPokeAbilities _pokeAbilities;
    parsePokeAbilities(&_pokeAbilities, dexNum);

    // ** TYPES **
    _dbPokeTypes _pokeTypes;
    parsePokeTypes(&_pokeTypes, dexNum);

    // ** POKES **
    _dbPoke _poke;
    parsePoke(&_poke, dexNum);

    // cur_name          = _pokeSpecies._identifier;
    cur_types[0]      = _pokeTypes._types[0];
    cur_types[1]      = _pokeTypes._types[1];
    cur_abilities[0]  = _pokeAbilities._abilities[0];
    cur_abilities[1]  = _pokeAbilities._abilities[1];
    cur_abilities[2]  = _pokeAbilities._abilities[2];
    cur_genderRate    = _pokeSpecies._gender_rate;
    cur_baseStats[0]  = _pokeStats._base_stat[0];
    cur_baseStats[1]  = _pokeStats._base_stat[1];
    cur_baseStats[2]  = _pokeStats._base_stat[2];
    cur_baseStats[3]  = _pokeStats._base_stat[3];
    cur_baseStats[4]  = _pokeStats._base_stat[4];
    cur_baseStats[5]  = _pokeStats._base_stat[5];
    cur_baseExp       = _poke._base_experience;
    cur_onDeathEVs[0] = _pokeStats._effort[0];
    cur_onDeathEVs[1] = _pokeStats._effort[1];
    cur_onDeathEVs[2] = _pokeStats._effort[2];
    cur_onDeathEVs[3] = _pokeStats._effort[3];
    cur_onDeathEVs[4] = _pokeStats._effort[4];
    cur_onDeathEVs[5] = _pokeStats._effort[5];
    cur_capRate       = _pokeSpecies._capture_rate;
    cur_baseHappiness = _pokeSpecies._base_happiness;
    cur_growthRate    = _pokeSpecies._growth_rate_id;

    // vector<_dbPokeMoves> moves;
    parsePokeMoves(&moves, dexNum);
    parsePokeSpeciesName(dexNum);
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
    openFile(POKEMON_SPECIES_CSV);
    clearStruct(_pokeSpecies);

    getline(my_ifs, cur_line);     // get rid of title line

    int token;

    do
    {
        getline(my_ifs, cur_line);
        my_ss.str(cur_line);
        my_ss.clear();
        parseLine(my_ss, token);
    }
    while ( (token < dexNum) && (!my_ifs.eof()) );

    _pokeSpecies->_id = token;

    parseLine(my_ss, _pokeSpecies->_identifier);
    parseLine(my_ss, _pokeSpecies->_generation_id);
    parseLine(my_ss, _pokeSpecies->_evolves_from_species_id);
    parseLine(my_ss, _pokeSpecies->_evolution_chain_id);
    parseLine(my_ss, _pokeSpecies->_color_id);
    parseLine(my_ss, _pokeSpecies->_shape_id);
    parseLine(my_ss, _pokeSpecies->_habitat_id);
    parseLine(my_ss, _pokeSpecies->_gender_rate);
    parseLine(my_ss, _pokeSpecies->_capture_rate);
    parseLine(my_ss, _pokeSpecies->_base_happiness);
    parseLine(my_ss, _pokeSpecies->_is_baby);
    parseLine(my_ss, _pokeSpecies->_hatch_counter);
    parseLine(my_ss, _pokeSpecies->_has_gender_differences);
    parseLine(my_ss, _pokeSpecies->_growth_rate_id);
    parseLine(my_ss, _pokeSpecies->_forms_switchable);
    parseLine(my_ss, _pokeSpecies->_order);
    parseLine(my_ss, _pokeSpecies->_conquest_order);
}

void DBParser::parsePokeStats(_dbPokeStats* _pokeStats, int dexNum){

    // open file for parsing
    openFile(POKEMON_STATS_CSV);
    clearStruct(_pokeStats);

    getline(my_ifs, cur_line);     // get rid of title line

    int token;

    while (true)
    {
        do
        {
            getline(my_ifs, cur_line);
            my_ss.str(cur_line);
            my_ss.clear();
            parseLine(my_ss, token);
        }
        while ( (token < dexNum) && (!my_ifs.eof()) );

        int stat_id = 0;
        int base_stat = 0;
        int effort = 0;
        parseLine(my_ss, stat_id);
        parseLine(my_ss, base_stat);
        parseLine(my_ss, effort);

        if (token != dexNum || my_ifs.eof()) break;

        _pokeStats->_pokemon_id = token;
        _pokeStats->_base_stat[stat_id-1] = base_stat;
        _pokeStats->_effort[stat_id-1]    = effort;
    }
}

void DBParser::parsePokeAbilities(_dbPokeAbilities* _pokeAbilities, int dexNum){

    // open file for parsing
    openFile(POKEMON_ABILITIES_CSV);
    clearStruct(_pokeAbilities);

    getline(my_ifs, cur_line);     // get rid of title line

    int token;

    while (true)
    {
        do
        {
            getline(my_ifs, cur_line);
            my_ss.str(cur_line);
            my_ss.clear();
            parseLine(my_ss, token);
        }
        while ( (token < dexNum) && (!my_ifs.eof()) );

        int this_ability_id = 0;
        int this_ishidden = 0;
        int this_slot = 0;

        parseLine(my_ss, this_ability_id);
        parseLine(my_ss, this_ishidden);
        parseLine(my_ss, this_slot);

        if (token != dexNum || my_ifs.eof()) break;


        _pokeAbilities->_pokemon_id             = token;
        _pokeAbilities->_abilities[this_slot-1] = this_ability_id;
    }
}

void DBParser::parsePokeTypes(_dbPokeTypes* _pokeTypes, int dexNum){

    // open file for parsing
    openFile(POKEMON_TYPES_CSV);
    clearStruct(_pokeTypes);

    getline(my_ifs, cur_line);     // get rid of title line

    int token;

    while (true)
    {
        do
        {
            getline(my_ifs, cur_line);
            my_ss.str(cur_line);
            my_ss.clear();
            parseLine(my_ss, token);
        }
        while ( (token < dexNum) && (!my_ifs.eof()) );


        int this_type_id = 0;
        int this_slot = 0;


        parseLine(my_ss, this_type_id);
        parseLine(my_ss, this_slot);

        if (token != dexNum || my_ifs.eof()) break;

        _pokeTypes->_pokemon_id         = token;
        _pokeTypes->_types[this_slot-1] = this_type_id;
    }
}

void DBParser::parsePoke(_dbPoke* _poke, int dexNum){

    // open file for parsing
    openFile(POKEMON_CSV);
    clearStruct(_poke);

    getline(my_ifs, cur_line);     // get rid of title line

    int token;

    while (true)
    {
        do
        {
            getline(my_ifs, cur_line);
            my_ss.str(cur_line);
            my_ss.clear();
            parseLine(my_ss, token);
        }
        while ( (token < dexNum) && (!my_ifs.eof()) );

        if (token != dexNum || my_ifs.eof()) break;

        _poke->_id = token;
        parseLine(my_ss, _poke->_species_id);
        parseLine(my_ss, _poke->_height);
        parseLine(my_ss, _poke->_weight);
        parseLine(my_ss, _poke->_base_experience);
        parseLine(my_ss, _poke->_order);
        parseLine(my_ss, _poke->_is_default);
    }
}


void DBParser::parsePokeMoves(vector<_dbPokeMoves>* moves, int dexNum){

    // open file for parsing
    openFile(POKEMON_MOVES_CSV);

    getline(my_ifs, cur_line);     // get rid of title line

    int token;
     _dbPokeMoves _pokeMoves;

    while (true)
    {
        clearStruct(&_pokeMoves);
        do
        {
            getline(my_ifs, cur_line);
            my_ss.str(cur_line);
            my_ss.clear();
            parseLine(my_ss, token);
        }
        while ( (token < dexNum) && (!my_ifs.eof()) );

        if (token != dexNum || my_ifs.eof()) break;

        _pokeMoves._pokemon_id = token;
        parseLine(my_ss, _pokeMoves._version_group_id);
        parseLine(my_ss, _pokeMoves._move_id);
        parseLine(my_ss, _pokeMoves._pokemon_move_method_id);
        parseLine(my_ss, _pokeMoves._level);
        parseLine(my_ss, _pokeMoves._order);
        if (_pokeMoves._version_group_id == 14 && _pokeMoves._pokemon_move_method_id > 0 && _pokeMoves._pokemon_move_method_id < 5)
        {
            moves->push_back(_pokeMoves);
        }
    }
}

void DBParser::parsePokeSpeciesName(int dexNum){

    // open file for parsing
    openFile(POKEMON_SPECIES_NAMES_CSV);

    getline(my_ifs, cur_line);     // get rid of title line

    int token;

    while (true)
    {
        do
        {
            getline(my_ifs, cur_line);
            my_ss.str(cur_line);
            my_ss.clear();
            parseLine(my_ss, token);
        }
        while ( (token < dexNum) && (!my_ifs.eof()) );

        if (token != dexNum || my_ifs.eof()) break;

        int local_language_id;

        parseLine(my_ss, local_language_id);

        if (local_language_id == LANGUAGE_ID) {
            getline(my_ss, cur_name, ',');
            break;
        }
    }
}

void DBParser::parseType(_type* type, int typeNum){


    // open file for parsing
    openFile(TYPE_EFFICACY_CSV);
    clearStruct(type);

    getline(my_ifs, cur_line);     // get rid of title line

    int token;

    while (true)
    {
        do
        {
            getline(my_ifs, cur_line);
            my_ss.str(cur_line);
            my_ss.clear();
            parseLine(my_ss, token);
        }
        while ( (token < typeNum) && (!my_ifs.eof()) );

        if (token != typeNum || my_ifs.eof()) break;

        int target_type_id = 0;
        int damage_factor  = 0;
        parseLine(my_ss, target_type_id);
        parseLine(my_ss, damage_factor);

        if (target_type_id - 1 == type->_damage_factor.size())
            type->_damage_factor.push_back(damage_factor);

    }


    // open file for parsing
    openFile(TYPES_CSV);
    // clearStruct(type);

    getline(my_ifs, cur_line);     // get rid of title line

    while (true)
    {
        do
        {
            getline(my_ifs, cur_line);
            my_ss.str(cur_line);
            my_ss.clear();
            parseLine(my_ss, token);
        }
        while ( (token < typeNum) && (!my_ifs.eof()) );

        if (token != typeNum || my_ifs.eof()) break;

        parseLine(my_ss, type->_identifier);
    }
}




void DBParser::parseNature(_nature* nature, int natureNum){

    // open file for parsing
    openFile(NATURES_CSV);
    clearStruct(nature);

    getline(my_ifs, cur_line);     // get rid of title line

    int token;

    nature->_natureNum = natureNum;

    while (true)
    {
        do
        {
            getline(my_ifs, cur_line);
            my_ss.str(cur_line);
            my_ss.clear();
            parseLine(my_ss, token);
        }
        while ( (token < natureNum) && (!my_ifs.eof()) );

        if (token != natureNum || my_ifs.eof()) break;

        parseLine(my_ss, nature->_identifier);
        parseLine(my_ss, nature->_decreased_stat_id);
        parseLine(my_ss, nature->_increased_stat_id);

        // if (target_nature_id - 1 == nature->_damage_factor.size())
        //     nature->_damage_factor.push_back(damage_factor);

    }


    // open file for parsing
    openFile(NATURE_NAMES_CSV);

    getline(my_ifs, cur_line);     // get rid of title line

    while (true)
    {
        do
        {
            getline(my_ifs, cur_line);
            my_ss.str(cur_line);
            my_ss.clear();
            parseLine(my_ss, token);
        }
        while ( (token < natureNum) && (!my_ifs.eof()) );

        if (token != natureNum || my_ifs.eof()) break;

        // parseLine(my_ss, );


        int local_language_id;

        parseLine(my_ss, local_language_id);

        if (local_language_id == LANGUAGE_ID) {
            getline(my_ss, nature->_identifier, ',');
            break;
        }
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

void DBParser::clearStruct(_nature* _n) {
    _n->_identifier = "";
    _n->_natureNum = 0;
    _n->_decreased_stat_id = 0;
    _n->_increased_stat_id = 0;
}

void DBParser::openFile(const char* file)
{
    if(my_ifs.is_open())
    {
        my_ifs.close();
    }

    my_ifs.open(file);

    if(!my_ifs.is_open())
    {
        cerr << "Could not open " << file;
        exit(1);
    }

    my_ifs.clear(); // reset flags
}