#ifndef POKEMON_H
#define POKEMON_H

#include "PokemonSpecies.h" // parent class
#include "Nature.h"         // pokemon has a nature
#include <string>

class Pokemon : public PokemonSpecies
{
    public:

        Pokemon(int dexNum, int level=1);
        ~Pokemon();

        string getNickname();
        int    getGender();
        int    getAbility();
        string getNature();
        int    getLevel();
        int    getCurExp();
        int    getIVs(int i);
        int    getEVs(int i);
        int    getMoves(int i);
        int    getCurHP();
        int    getStatus();
        int    getStats(int i);

    private:

        string  _nickname;

        int _genderValue;
        int _abilityIndex;

        // int _nature;
        Nature _nature;

        int _level;
        int _curExp;
        int _IVs[6];
        int _EVs[6];

        int _moves[4];
        int _curHP;

        int _status;

        void initMoves();


};

#endif // POKEMON_H