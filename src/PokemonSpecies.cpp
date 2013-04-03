#include "PokemonSpecies.h"

PokemonSpecies::PokemonSpecies(int dexNum) {
    /* parse database file based on pokedex number
       then set these variables */
    DBParser species(dexNum) = ;

    _dexNum       = dexNum;
    _name         = ; // pokemon_species

    _types[2]     = ; // pokemon_types
    _abilities[3] = ; // pokemon_abilities
    _genderRate   = ; // pokemon_species
    _baseStats[6] = ; // pokemon_stats

    // training based
    _baseExp       = ;
    _onDeathEVs[6] = ; // pokemon_stats
    _capRate       = ; // pokemon_species
    _baseHappiness = ; // pokemon_species
    _growthRate    = ; // pokemon_species

}