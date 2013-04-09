#ifndef DBPARSER_H
#define DBPARSER_H

#include <sstream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

// POKEMON_SPECIES_CSV values
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

// POKEMON_STATS_CSV values
struct _dbPokeStats {
    int _pokemon_id;
    int _base_stat[6];
    int _effort[6];
};

// POKEMON_ABILITIES_CSV values
struct _dbPokeAbilities {
    int _pokemon_id;
    int _abilities[3];
};

// POKEMON_TYPES_CSV values
struct _dbPokeTypes {
    int _pokemon_id;
    int _types[2];
};

// POKEMON_CSV values
struct _dbPoke {
    int _id;
    int _species_id;
    int _height;
    int _weight;
    int _base_experience;
    int _order;
    int _is_default;
};

// POKEMON_MOVES_CSV values
struct _dbPokeMoves {
    int _pokemon_id;
    int _version_group_id;
    int _move_id;
    int _pokemon_move_method_id;
    int _level;
    int _order;
};

struct _type {
    string _identifier;
    vector<int> _damage_factor;
};

class DBParser
{
    public:
        DBParser();
        DBParser(int num, int mode);
        ~DBParser(){};

        // getters for pokemon species class
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
        int    getTypeEfficacy(int typeNum);
        string getTypeString();

        void initPokemonSpecies(int dexNum);

        vector<_dbPokeMoves> moves;

    private:

        void openFile(const char* file);

        // tokenizes the line in stringstream ss by ','
        // and store the token it into t
        template <class T>
        void parseLine(stringstream &ss, T &t);

        // function to read from csv file and store into struct
        void parsePokeSpecies(_dbPokeSpecies* _pokeSpecies, int dexNum=0);
        void parsePokeStats(_dbPokeStats* _pokeStats, int dexNum=0);
        void parsePokeAbilities(_dbPokeAbilities* _pokeAbilities, int dexNum=0);
        void parsePokeTypes(_dbPokeTypes* _pokeTypes, int dexNum=0);
        void parsePoke(_dbPoke* _poke, int dexNum=0);
        void parsePokeMoves(vector<_dbPokeMoves>* moves, int dexNum=0);


        void parseType(_type* type, int typeNum=0);

        // set all variables in struct to 0 or ""
        void clearStruct(_dbPokeSpecies* _pokeSpecies);
        void clearStruct(_dbPokeStats* _pokeStats);
        void clearStruct(_dbPokeAbilities* _pokeAbilities);
        void clearStruct(_dbPokeTypes* _pokeTypes);
        void clearStruct(_dbPoke* _poke);
        void clearStruct(_dbPokeMoves* _pokeMoves);
        void clearStruct(_type* _t);

        // for parsing
        ifstream     my_ifs;       // file to parse
        stringstream my_ss;        // stringstream for tokenizing current line
        string       cur_line;  // current line being read in parsing


        // variables for pokemon species class
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

        // type
        _type cur_type;

};

#endif // DBPARSER_H
