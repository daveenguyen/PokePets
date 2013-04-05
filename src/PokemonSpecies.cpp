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

    cout << "_dexNum       : " << _dexNum << endl;
    cout << "_name         : " << _name << endl;
    cout << "_types[0]     : " << _types[0] << endl;
    cout << "_types[1]     : " << _types[1] << endl;
    cout << "_abilities[0] : " << _abilities[0] << endl;
    cout << "_abilities[1] : " << _abilities[1] << endl;
    cout << "_abilities[2] : " << _abilities[2] << endl;
    cout << "_genderRate   : " << _genderRate << endl;
    cout << "_baseStats[0] : " << _baseStats[0] << endl;
    cout << "_baseStats[1] : " << _baseStats[1] << endl;
    cout << "_baseStats[2] : " << _baseStats[2] << endl;
    cout << "_baseStats[3] : " << _baseStats[3] << endl;
    cout << "_baseStats[4] : " << _baseStats[4] << endl;
    cout << "_baseStats[5] : " << _baseStats[5] << endl;
    cout << "_baseExp      : " << _baseExp << endl;
    cout << "_onDeathEVs[0]: " << _onDeathEVs[0] << endl;
    cout << "_onDeathEVs[1]: " << _onDeathEVs[1] << endl;
    cout << "_onDeathEVs[2]: " << _onDeathEVs[2] << endl;
    cout << "_onDeathEVs[3]: " << _onDeathEVs[3] << endl;
    cout << "_onDeathEVs[4]: " << _onDeathEVs[4] << endl;
    cout << "_onDeathEVs[5]: " << _onDeathEVs[5] << endl;
    cout << "_capRate      : " << _capRate << endl;
    cout << "_baseHappiness: " << _baseHappiness << endl;
    cout << "_growthRate   : " << _growthRate << endl;

}

PokemonSpecies::~PokemonSpecies() {}

// testing
int main() {
    cout << "Enter a pokedex number or 0 for all: ";
    int dexNum;
    cin  >> dexNum;
    cout << endl;
    PokemonSpecies myPokemon(dexNum);
    return 0;
}