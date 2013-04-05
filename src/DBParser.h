#ifndef DBPARSER_H
#define DBPARSER_H

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
using namespace std;

const int MAX_POKEMON = 151;

// stuff from POKEMON_SPECIES_CSV
struct _dbPokeSpecies {
    int    _id;
    string _identifier;
    int    _generation_id;
    int    _evolves_from_species_id;
    int    _evolution_chain_id;
    int    _color_id;
    int    _shape_id;
    int    _habitat_id;
    int    _gender_rate;
    int    _capture_rate;
    int    _base_happiness;
    int    _is_baby;
    int    _hatch_counter;
    int    _has_gender_differences;
    int    _growth_rate_id;
    int    _forms_switchable;
    int    _order;
    int    _conquest_order;
};

struct _dbPokeStats {
    int _pokemon_id;
    int _base_stat[6];
    int _effort[6];
};

struct _dbPokeAbilities {
    int _pokemon_id;
    int _abilities[3];
};

struct _dbPokeTypes {
    int _pokemon_id;
    int _types[2];
};

struct _dbPoke {
    int _id;
    int _species_id;
    int _height;
    int _weight;
    int _base_experience;
    int _order;
    int _is_default;
};

class DBParser
{
    public:
        DBParser(int dexNum=0);
        ~DBParser();
        string getName();
        int    getTypes(int i);
        int    getAbilities(int i);
        int    getGenderRate();
        int    getBaseStats(int i);
        int    getBaseExp();
        int    getOnDeathEVs(int i);
        int    getCapRate();
        int    getBaseHappiness();
        int    getGrowthRate();

    private:

        template <class T>
        void parseLine(stringstream &ss, T &t);

        void parsePokeSpecies(_dbPokeSpecies* _pokeSpecies, int dexNum=0);
        void parsePokeStats(_dbPokeStats* _pokeStats, int dexNum=0);
        void parsePokeAbilities(_dbPokeAbilities* _pokeAbilities, int dexNum=0);
        void parsePokeTypes(_dbPokeTypes* _pokeTypes, int dexNum=0);
        void parsePoke(_dbPoke* _poke, int dexNum=0);

        void clearStruct(_dbPokeSpecies* _pokeSpecies);
        void clearStruct(_dbPokeStats* _pokeStats);
        void clearStruct(_dbPokeAbilities* _pokeAbilities);
        void clearStruct(_dbPokeTypes* _pokeTypes);
        void clearStruct(_dbPoke* _poke);


        string cur_name;

        int cur_types[2];      // pokemon_types
        int cur_abilities[3];  // pokemon_abilities
        int cur_genderRate;    // pokemon_species
        int cur_baseStats[6];  // pokemon_stats

        // training based
        int cur_baseExp;
        int cur_onDeathEVs[6]; // pokemon_stats
        int cur_capRate;       // pokemon_species
        int cur_baseHappiness; // pokemon_species
        int cur_growthRate;    // pokemon_species

};


// _Species _species0;
// _dbPokeSpecies _pokeSpecies[MAX_POKEMON];

#endif // DBPARSER_H
