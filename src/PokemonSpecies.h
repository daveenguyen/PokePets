#ifndef POKEMONSPECIES_H
#define POKEMONSPECIES_H

#include <string>
#include <vector>
using namespace std;

#include "Type.h"       // Pokemon species has types

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

/* Stuff that every Pokemon of the same pokemon species share */
class PokemonSpecies
{
    public:

        PokemonSpecies(int dexNum=0);

        PokemonSpecies(int _dexNum,
                string _name,
                Type _types[2],
                int _abilities[3],
                int _genderRate,
                int _baseStats[6],
                int _baseExp,
                int _effortYield[6],
                int _capRate,
                int _baseHappiness,
                int _growthRate,
                int _expToLvl[100]);

        ~PokemonSpecies();

        void    clear();
        int     getDexNum();
        string  getName();
        Type    getType(int i);
        int     getSpeciesAbility(int i);
        int     getGenderRate();
        int     getBaseStats(int i);
        int     getBaseExp();
        int     getEffortYield(int i);
        int     getCapRate();
        int     getBaseHappiness();
        int     getGrowthRate();
        int     getExpToLvl(int i);

        void    setDexNum(int num);
        void    setName(string name);
        void    setType(int index, int typeId);
        void    setSpeciesAbility(int index, int abilityId);
        void    setGenderRate(int value);
        void    setBaseStat(int statId, int value);
        void    setBaseExp(int num);
        void    setEffortYield(int statId, int value);
        void    setCapRate(int value);
        void    setBaseHappiness(int value);
        void    setGrowthRate(int value);
        void    setExpToLvl(int level, int value);

        void    addLevelUpMoves(int level, int move_id, int order);
        void    addEggMove(int moveId);
        void    addTutorMove(int moveId);
        void    addMachineMove(int moveId);

        vector<LevelUpMoves> getLevelUpMoves();
        vector<int>          getEggMoves();
        vector<int>          getTutorMoves();
        vector<int>          getMachineMoves();


    private:

        int     _dexNum;            // pokedex number
        string  _name;              // species name

        Type    _types[2];
        // int     _types[2];          // types
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