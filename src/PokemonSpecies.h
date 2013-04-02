#ifndef POKEMONSPECIES_H
#define POKEMONSPECIES_H

#include <string>
using namespace std;

/* Stuff that every Pokemon of the same species share */
class PokemonSpecies
{
    public:

        Pokemon(int dexNum);

        ~Pokemon();

        string  getName();
        Type    getType(int index); // or gettypes?
        Type[]  getTypes();
        Ability getAbilities(int index);
        double  getGenderRatio();
        int     getBaseStat(int index);
        int[]   getBaseStats();

    private:

        int     _dexNum;
        string  _name;

        Types   _types[2];
        Ability _abilities[2];
        double  _genderRatio;
        int     _baseStats[6];

        // move set

        // training based
        int    _baseExp;
        int    _onDeathEVs[6];
        double _capRate;
        int    _baseHappiness;
        Growth _rate;

        // wild held items
        // possible for multiple items
        // has item and rate for item
        // example garbodor with 3 items

};

#endif // POKEMONSPECIES_H