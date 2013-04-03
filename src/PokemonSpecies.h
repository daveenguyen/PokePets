#ifndef POKEMONSPECIES_H
#define POKEMONSPECIES_H

#include <string>
using namespace std;

/* Stuff that every Pokemon of the same pokemon species share */
class PokemonSpecies
{
    public:

        Pokemon(int dexNum);

        ~Pokemon();

    private:

        int     _dexNum;
        string  _name;

        int     _types[2];
        int     _abilities[3];
        int     _genderRate;
        int     _baseStats[6];

        // training based
        int    _baseExp;
        int    _onDeathEVs[6];
        double _capRate;
        int    _baseHappiness;
        int    _growthRate;

        // move set
        // wild held items
        // possible for multiple items
        // has item and rate for item
        // example garbodor with 3 items

};

#endif // POKEMONSPECIES_H