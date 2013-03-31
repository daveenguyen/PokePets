#ifndef DBPARSER_H
#define DBPARSER_H

#include <string>
using namespace std;

const int MAX_POKEMON = 151;

class DBParser
{
    public:

        DBParser();
        DBParser(int dexNum);
        ~DBParser();
        string getName();

    private:

        template <class T>
        void parseLine(stringstream &ss, T &t);

        // void parseLine(stringstream &ss, int &t);
        // void parseLine(stringstream &ss, string &t);

        void parseSpecies(ifstream &ifs);
        void parseSpecies(ifstream &ifs, int dexNum);

        int    __id;
        string __identifier;
        int    __generation_id;
        int    __evolves_from_species_id;
        int    __evolution_chain_id;
        int    __color_id;
        int    __shape_id;
        int    __habitat_id;
        int    __gender_rate;
        int    __capture_rate;
        int    __base_happiness;
        int    __is_baby;
        int    __hatch_counter;
        int    __has_gender_differences;
        int    __growth_rate_id;
        int    __forms_switchable;
        int    __order;
        int    __conquest_order;
};

struct _Species {
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

        // _Species _species0;
        _Species _species[MAX_POKEMON];

#endif // DBPARSER_H
