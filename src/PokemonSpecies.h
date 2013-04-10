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

    LevelUpMoves(int _level, int _move_id, int _order) : _level(_level), _move_id(_move_id), _order(_order) {}

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

/* Stuff that every Pokemon of the same pokemon species share */
class PokemonSpecies
{
    public:

        PokemonSpecies(int dexNum);

        ~PokemonSpecies();

        void   initFromParser(int dexNum);
        int    getDexNum();
        string getName();
        int    getTypes(int i);
        int    getAbilities(int i);
        int    getGenderRate();
        int    getBaseStats(int i);
        int    getBaseExp();
        int    getOnDeathEVs(int i);
        int    getCapRate();
        int    getBaseHappiness();
        int    getGrowthRate();
        int    getExpToLvl(int i);


        vector<LevelUpMoves> getLevelUpMoves();
        vector<int>          getEggMoves();
        vector<int>          getTutorMoves();
        vector<int>          getMachineMoves();

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
        int    _expToLvl[100];

        // move set
        // from 1: level-up
        vector<LevelUpMoves> levelUpMoves;

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