#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
using namespace std;

#include "DBParser.h"

#define POKEMON_SPECIES_CSV "../data/csv/pokemon_species.csv"
#define DEBUG

DBParser::DBParser() {

    // open file for parsing
    ifstream ifs(POKEMON_SPECIES_CSV);
    if(!ifs.is_open())
    {
        cout << "Could not open " << POKEMON_SPECIES_CSV;
        exit(1);
    }

    __id = 0;
    __identifier = "";
    __generation_id = 0;
    __evolves_from_species_id = 0;
    __evolution_chain_id = 0;
    __color_id = 0;
    __shape_id = 0;
    __habitat_id = 0;
    __gender_rate = 0;
    __capture_rate = 0;
    __base_happiness = 0;
    __is_baby = 0;
    __hatch_counter = 0;
    __has_gender_differences = 0;
    __growth_rate_id = 0;
    __forms_switchable = 0;
    __order = 0;
    __conquest_order = 0;

    parseSpecies(ifs);
}

DBParser::DBParser(int dexNum) {

    // open file for parsing
    ifstream ifs(POKEMON_SPECIES_CSV);
    if(!ifs.is_open())
    {
        cout << "Could not open " << POKEMON_SPECIES_CSV;
        exit(1);
    }

    __id = 0;
    __identifier = "";
    __generation_id = 0;
    __evolves_from_species_id = 0;
    __evolution_chain_id = 0;
    __color_id = 0;
    __shape_id = 0;
    __habitat_id = 0;
    __gender_rate = 0;
    __capture_rate = 0;
    __base_happiness = 0;
    __is_baby = 0;
    __hatch_counter = 0;
    __has_gender_differences = 0;
    __growth_rate_id = 0;
    __forms_switchable = 0;
    __order = 0;
    __conquest_order = 0;

    parseSpecies(ifs, dexNum);
}

DBParser::~DBParser(){}

string DBParser::getName() {
    return __identifier;
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
// template <class T>
// void DBParser::parseLine(stringstream &ss, int &t) {
//     if (ss.peek() == ',') {
//         ss.ignore();
//     }
//     else {
//         string field;
//         getline(ss, field, ',');
//         stringstream fs(field);
//         fs >> t;
//     }
//         // cout << t << endl;;
// }

// void DBParser::parseLine(stringstream &ss, string &t) {
//     if (ss.peek() == ',') {
//         ss.ignore();
//     }
//     else {
//         string field;
//         getline(ss, field, ',');
//         stringstream fs(field);
//         fs >> t;
//     }
// }

void DBParser::parseSpecies(ifstream &ifs){

    int count = 0;

    // read a line
    string line;           // string to store line

    // for (int i = 0; i < dexNum; ++i)
    getline(ifs, line);    // discard first line

    for (int i=0; i < 151; ++i) {
        getline(ifs, line);    // get line

        // use stringstream to tokenize line
        stringstream ss(line);

        // parse the line by commas
        parseLine(ss, _species[count]._id);
        parseLine(ss, _species[count]._identifier);
        parseLine(ss, _species[count]._generation_id);
        parseLine(ss, _species[count]._evolves_from_species_id);
        parseLine(ss, _species[count]._evolution_chain_id);
        parseLine(ss, _species[count]._color_id);
        parseLine(ss, _species[count]._shape_id);
        parseLine(ss, _species[count]._habitat_id);
        parseLine(ss, _species[count]._gender_rate);
        parseLine(ss, _species[count]._capture_rate);
        parseLine(ss, _species[count]._base_happiness);
        parseLine(ss, _species[count]._is_baby);
        parseLine(ss, _species[count]._hatch_counter);
        parseLine(ss, _species[count]._has_gender_differences);
        parseLine(ss, _species[count]._growth_rate_id);
        parseLine(ss, _species[count]._forms_switchable);
        parseLine(ss, _species[count]._order);
        parseLine(ss, _species[count]._conquest_order);

        /* for debugging */
        #ifdef DEBUG
            cout << _species[count]._id << endl;
            cout << _species[count]._identifier << endl;
            cout << _species[count]._generation_id << endl;
            cout << _species[count]._evolves_from_species_id << endl;
            cout << _species[count]._evolution_chain_id << endl;
            cout << _species[count]._color_id << endl;
            cout << _species[count]._shape_id << endl;
            cout << _species[count]._habitat_id << endl;
            cout << _species[count]._gender_rate << endl;
            cout << _species[count]._capture_rate << endl;
            cout << _species[count]._base_happiness << endl;
            cout << _species[count]._is_baby << endl;
            cout << _species[count]._hatch_counter << endl;
            cout << _species[count]._has_gender_differences << endl;
            cout << _species[count]._growth_rate_id << endl;
            cout << _species[count]._forms_switchable << endl;
            cout << _species[count]._order << endl;
            cout << _species[count]._conquest_order << endl;
        #endif

        ++count;
    }

}
void DBParser::parseSpecies(ifstream &ifs, int dexNum){

    // read a line
    string line;           // string to store line

    // discards line before dexNum
    for (int i = 0; i < dexNum; ++i)
        getline(ifs, line);


    getline(ifs, line);    // get line

    // use stringstream to tokenize line
    stringstream ss(line);

    // parse the line by commas
    parseLine(ss, __id);
    parseLine(ss, __identifier);
    parseLine(ss, __generation_id);
    parseLine(ss, __evolves_from_species_id);
    parseLine(ss, __evolution_chain_id);
    parseLine(ss, __color_id);
    parseLine(ss, __shape_id);
    parseLine(ss, __habitat_id);
    parseLine(ss, __gender_rate);
    parseLine(ss, __capture_rate);
    parseLine(ss, __base_happiness);
    parseLine(ss, __is_baby);
    parseLine(ss, __hatch_counter);
    parseLine(ss, __has_gender_differences);
    parseLine(ss, __growth_rate_id);
    parseLine(ss, __forms_switchable);
    parseLine(ss, __order);
    parseLine(ss, __conquest_order);

    /* for debugging */
    #ifdef DEBUG
        cout << __id << endl;
        cout << __identifier << endl;
        cout << __generation_id << endl;
        cout << __evolves_from_species_id << endl;
        cout << __evolution_chain_id << endl;
        cout << __color_id << endl;
        cout << __shape_id << endl;
        cout << __habitat_id << endl;
        cout << __gender_rate << endl;
        cout << __capture_rate << endl;
        cout << __base_happiness << endl;
        cout << __is_baby << endl;
        cout << __hatch_counter << endl;
        cout << __has_gender_differences << endl;
        cout << __growth_rate_id << endl;
        cout << __forms_switchable << endl;
        cout << __order << endl;
        cout << __conquest_order << endl;
    #endif
}


int main() {
    DBParser db(1);
    return 0;
}