#include <string>
#include <iostream>
using namespace std;

#include "PokemonSpecies.h"
#include "DBParser.h"

PokemonSpecies::PokemonSpecies(int dexNum) {
    /* parse database file based on pokedex number
       then set these variables */
    DBParser species(dexNum);

    _dexNum       = dexNum;
    _name         = species.getName(); // pokemon_species

    _types[0]     = species.getTypes(0); // pokemon_types
    _types[1]     = species.getTypes(1); // pokemon_types

    _abilities[0] = species.getAbilities(0); // pokemon_abilities
    _abilities[1] = species.getAbilities(1); // pokemon_abilities
    _abilities[2] = species.getAbilities(2); // pokemon_abilities

    _genderRate   = species.getGenderRate(); // pokemon_species

    _baseStats[0] = species.getBaseStats(0); // pokemon_stats
    _baseStats[1] = species.getBaseStats(1); // pokemon_stats
    _baseStats[2] = species.getBaseStats(2); // pokemon_stats
    _baseStats[3] = species.getBaseStats(3); // pokemon_stats
    _baseStats[4] = species.getBaseStats(4); // pokemon_stats
    _baseStats[5] = species.getBaseStats(5); // pokemon_stats

    // training based
    _baseExp       = species.getBaseExp();       // pokemon
    _onDeathEVs[0] = species.getOnDeathEVs(0);   // pokemon_stats
    _onDeathEVs[1] = species.getOnDeathEVs(1);   // pokemon_stats
    _onDeathEVs[2] = species.getOnDeathEVs(2);   // pokemon_stats
    _onDeathEVs[3] = species.getOnDeathEVs(3);   // pokemon_stats
    _onDeathEVs[4] = species.getOnDeathEVs(4);   // pokemon_stats
    _onDeathEVs[5] = species.getOnDeathEVs(5);   // pokemon_stats
    _capRate       = species.getCapRate();       // pokemon_species
    _baseHappiness = species.getBaseHappiness(); // pokemon_species
    _growthRate    = species.getGrowthRate();    // pokemon_species
}

PokemonSpecies::~PokemonSpecies() {}


int PokemonSpecies::getDexNum() {
    return _dexNum;
}

string PokemonSpecies::getName() {
    return _name;
}

int PokemonSpecies::getTypes(int i) {
    if (i != 0 && i != 1) {
        cout << "ERROR ON getTypes" << endl;
        cout << "index: " << i << endl;
        exit(1);
    }
    return _types[i];
}
int PokemonSpecies::getAbilities(int i) {
    if (i < 0 || i > 2) {
        cout << "ERROR ON getAbilities" << endl;
        cout << "index: " << i << endl;
        exit(1);
    }
    return _abilities[i];
}
int PokemonSpecies::getGenderRate() {
    return _genderRate;
}
int PokemonSpecies::getBaseStats(int i) {
    if (i < 0 || i > 5) {
        cout << "ERROR ON getBaseStats" << endl;
        cout << "index: " << i << endl;
        exit(1);
    }
    return _baseStats[i];
}
int PokemonSpecies::getBaseExp() {
    return _baseExp;
}
int PokemonSpecies::getOnDeathEVs(int i) {
    if (i < 0 || i > 5) {
        cout << "ERROR ON getOnDeathEVs" << endl;
        cout << "index: " << i << endl;
        exit(1);
    }
    return _onDeathEVs[i];
}
int PokemonSpecies::getCapRate() {
    return _capRate;
}
int PokemonSpecies::getBaseHappiness() {
    return _baseHappiness;
}
int PokemonSpecies::getGrowthRate() {
    return _growthRate;
}

// // testing
// int main() {
//     cout << "Enter a pokedex number or 0 for all: ";
//     int dexNum;
//     cin  >> dexNum;
//     cout << endl;
//     PokemonSpecies myPokemon(dexNum);

//     cout << "myPokemon_dexNum       : " << myPokemon.getDexNum() << endl;
//     cout << "myPokemon_name         : " << myPokemon.getName() << endl;
//     cout << "myPokemon_types[0]     : " << myPokemon.getTypes(0) << endl;
//     cout << "myPokemon_types[1]     : " << myPokemon.getTypes(1) << endl;
//     cout << "myPokemon_abilities[0] : " << myPokemon.getAbilities(0) << endl;
//     cout << "myPokemon_abilities[1] : " << myPokemon.getAbilities(1) << endl;
//     cout << "myPokemon_abilities[2] : " << myPokemon.getAbilities(2) << endl;
//     cout << "myPokemon_genderRate   : " << myPokemon.getGenderRate() << endl;
//     cout << "myPokemon_baseStats[0] : " << myPokemon.getBaseStats(0) << endl;
//     cout << "myPokemon_baseStats[1] : " << myPokemon.getBaseStats(1) << endl;
//     cout << "myPokemon_baseStats[2] : " << myPokemon.getBaseStats(2) << endl;
//     cout << "myPokemon_baseStats[3] : " << myPokemon.getBaseStats(3) << endl;
//     cout << "myPokemon_baseStats[4] : " << myPokemon.getBaseStats(4) << endl;
//     cout << "myPokemon_baseStats[5] : " << myPokemon.getBaseStats(5) << endl;
//     cout << "myPokemon_baseExp      : " << myPokemon.getBaseExp() << endl;
//     cout << "myPokemon_onDeathEVs[0]: " << myPokemon.getOnDeathEVs(0) << endl;
//     cout << "myPokemon_onDeathEVs[1]: " << myPokemon.getOnDeathEVs(1) << endl;
//     cout << "myPokemon_onDeathEVs[2]: " << myPokemon.getOnDeathEVs(2) << endl;
//     cout << "myPokemon_onDeathEVs[3]: " << myPokemon.getOnDeathEVs(3) << endl;
//     cout << "myPokemon_onDeathEVs[4]: " << myPokemon.getOnDeathEVs(4) << endl;
//     cout << "myPokemon_onDeathEVs[5]: " << myPokemon.getOnDeathEVs(5) << endl;
//     cout << "myPokemon_capRate      : " << myPokemon.getCapRate() << endl;
//     cout << "myPokemon_baseHappiness: " << myPokemon.getBaseHappiness() << endl;
//     cout << "myPokemon_growthRate   : " << myPokemon.getGrowthRate() << endl;
//     return 0;
// }