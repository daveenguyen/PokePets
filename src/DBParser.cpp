#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
using namespace std;

#include "DBParser.h"

#define POKEMON_SPECIES_CSV "../data/csv/pokemon_species.csv"
#define DEBUG

#define MAX_POKES 151

DBParser::DBParser(int dexNum) {
    int maxPoke = 1;
    if (dexNum == 0) maxPoke = MAX_POKES;
    _dbPokeSpecies _pokeSpecies[maxPoke];
    parsePokeSpecies(_pokeSpecies, dexNum);
}

DBParser::~DBParser(){}

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
            cout << _pokeSpecies[i]._id << endl;
            cout << _pokeSpecies[i]._identifier << endl;
            cout << _pokeSpecies[i]._generation_id << endl;
            cout << _pokeSpecies[i]._evolves_from_species_id << endl;
            cout << _pokeSpecies[i]._evolution_chain_id << endl;
            cout << _pokeSpecies[i]._color_id << endl;
            cout << _pokeSpecies[i]._shape_id << endl;
            cout << _pokeSpecies[i]._habitat_id << endl;
            cout << _pokeSpecies[i]._gender_rate << endl;
            cout << _pokeSpecies[i]._capture_rate << endl;
            cout << _pokeSpecies[i]._base_happiness << endl;
            cout << _pokeSpecies[i]._is_baby << endl;
            cout << _pokeSpecies[i]._hatch_counter << endl;
            cout << _pokeSpecies[i]._has_gender_differences << endl;
            cout << _pokeSpecies[i]._growth_rate_id << endl;
            cout << _pokeSpecies[i]._forms_switchable << endl;
            cout << _pokeSpecies[i]._order << endl;
            cout << _pokeSpecies[i]._conquest_order << endl;
        #endif

        if (dexNum != 0) break; // break out if not doing all pokemons
    }
}

void DBParser::clearStruct(_dbPokeSpecies* _pokeSpecies){
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


// testing
int main() {
    cout << "Enter a pokedex number or 0 for all: ";
    int dexNum;
    cin  >> dexNum;
    cout << endl;
    DBParser db(dexNum);
    return 0;
}