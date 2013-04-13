#ifndef POKEMONSPECIES_H
#define POKEMONSPECIES_H

#include <string>
#include <vector>
#include <algorithm>    // sort
using namespace std;

struct LevelUpMoves {
    int _level;
    int _move_id;
    int _order;

    LevelUpMoves(int _level, int _move_id, int _order) :
            _level(_level),
            _move_id(_move_id),
            _order(_order) {}

    bool operator<(const LevelUpMoves& other)const{
        bool result;

        if (_level != other._level) {
            result = (_level < other._level);
        } else if (_order != other._order) {
            result = (_order < other._order);
        } else {
            result = (_move_id < other._move_id);
        }

        return result;
    }
};

class CSVReader;

/* Stuff that every Pokemon of the same pokemon species share */
class PokemonSpecies
{
    public:

        PokemonSpecies(CSVReader* reader, int dexNum=0);

        ~PokemonSpecies();

        void    clear();
        void    initFromParser();
        int     getDexNum();
        string  getName();
        int     getTypes(int i);
        int     getAbilities(int i);
        int     getGenderRate();
        int     getBaseStats(int i);
        int     getBaseExp();
        int     getEffortYield(int i);
        int     getCapRate();
        int     getBaseHappiness();
        int     getGrowthRate();
        int     getExpToLvl(int i);

        void    setDexNum(int i);

        vector<LevelUpMoves> getLevelUpMoves();
        vector<int>          getEggMoves();
        vector<int>          getTutorMoves();
        vector<int>          getMachineMoves();

    private:

        CSVReader* _reader;

        int     _dexNum;            // pokedex number
        string  _name;              // species name

        int     _types[2];          // types
        int     _abilities[3];      // abilities
        int     _genderRate;        // gender ratio id
        int     _baseStats[6];      // base stats

        // training based
        int     _baseExp;           // base experience yield
        int     _effortYield[6];    // effort yield
        int     _capRate;           // capture rate
        int     _baseHappiness;     // base happiness
        int     _growthRate;        // level up rate
        int     _expToLvl[100];     // level up table

        // move set
        // from 1: level-up
        vector<LevelUpMoves> levelMoves;

        // from 2: egg
        vector<int> eggMoves;

        // from 3: tutor
        vector<int> tutorMoves;

        // from 4: machine
        vector<int> machineMoves;

        // wild held items
        // possible for multiple items
        // has item and rate for item
        // example garbodor with 3 items

};

#endif // POKEMONSPECIES_H