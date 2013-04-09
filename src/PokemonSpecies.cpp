#include <string>
#include <iostream>
using namespace std;

#include "PokemonSpecies.h"
#include "DBParser.h"

PokemonSpecies::PokemonSpecies(int dexNum) {
    /* parse database file based on pokedex number
       then set these variables */
    initFromParser(dexNum);
}

PokemonSpecies::~PokemonSpecies() {}

void PokemonSpecies::initFromParser(int dexNum) {
    DBParser species(dexNum, 0);

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

    // moves
    levelUpMoves.clear();
    machineMoves.clear();
    tutorMoves.clear();
    eggMoves.clear();

    for (int i = 0; i < species.moves.size(); ++i) {
        switch (species.moves[i]._pokemon_move_method_id) {
            case 1: {
                levelUpMoves.push_back(LevelUpMoves(species.moves[i]._level, species.moves[i]._move_id, species.moves[i]._order));
                break;
            }
            case 2: {
                eggMoves.push_back(species.moves[i]._move_id);
                break;
            }
            case 3: {
                tutorMoves.push_back(species.moves[i]._move_id);
                break;
            }
            case 4: {
                machineMoves.push_back(species.moves[i]._move_id);
                break;
            }
        }
    }
    sort(levelUpMoves.begin(), levelUpMoves.end());
}

int PokemonSpecies::getDexNum() {
    return _dexNum;
}

string PokemonSpecies::getName() {
    return _name;
}

int PokemonSpecies::getTypes(int i) {
    if (i != 0 && i != 1) {
        cerr << "ERROR - getTypes(" << i << ")" << endl;
        exit(1);
    }
    return _types[i];
}
int PokemonSpecies::getAbilities(int i) {
    if (i < 0 || i > 2) {
        cerr << "ERROR - getAbilities(" << i << ")" << endl;
        exit(1);
    }
    return _abilities[i];
}
int PokemonSpecies::getGenderRate() {
    return _genderRate;
}
int PokemonSpecies::getBaseStats(int i) {
    if (i < 0 || i > 5) {
        cerr << "ERROR - getBaseStats(" << i << ")" << endl;
        exit(1);
    }
    return _baseStats[i];
}
int PokemonSpecies::getBaseExp() {
    return _baseExp;
}
int PokemonSpecies::getOnDeathEVs(int i) {
    if (i < 0 || i > 5) {
        cerr << "ERROR - getOnDeathEVs(" << i << ")" << endl;
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

vector<LevelUpMoves> PokemonSpecies::getLevelUpMoves(){
    return levelUpMoves;
}

vector<int> PokemonSpecies::getEggMoves(){
    return eggMoves;
}

vector<int> PokemonSpecies::getTutorMoves(){
    return tutorMoves;
}

vector<int> PokemonSpecies::getMachineMoves(){
    return machineMoves;
}