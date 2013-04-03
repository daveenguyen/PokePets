#ifndef DBPARSER_H
#define DBPARSER_H

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
    int _id;
    int _base_stat[6];
    int _effort[6];
};

class DBParser
{
    public:
        DBParser(int dexNum=0);
        ~DBParser();
        string getName();

    private:

        template <class T>
        void parseLine(stringstream &ss, T &t);

        // void parseLine(stringstream &ss, int &t);
        // void parseLine(stringstream &ss, string &t);

        // void parseSpecies(ifstream &ifs);
        // void parseSpecies(ifstream &ifs, int dexNum);
        void parsePokeSpecies(_dbPokeSpecies* _pokeSpecies, int dexNum=0);
        void parsePokeStats(_dbPokeStats* _pokeStats, int dexNum=0);

        void clearStruct(_dbPokeSpecies* _pokeSpecies);
        void clearStruct(_dbPokeStats* _pokeStats);

};


// _Species _species0;
// _dbPokeSpecies _pokeSpecies[MAX_POKEMON];

#endif // DBPARSER_H
