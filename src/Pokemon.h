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

        void reset();

        string getNickname();
        string getGender();
        string getNature();
        int    getAbility();
        int    getLevel();
        int    getCurExp();
        int    getIVs(int i);
        int    getEVs(int i);
        int    getMoves(int i);
        int    getCurHP();
        int    getStatus();
        int    getStats(int i);
        void   adjustHP(int i);
        void   adjustExperience(int baseExp, int faintLvl, bool isWild, int participated=1);
        void   checkExperience();
        void   useMove(int i, Pokemon* target);

    private:

        string  _nickname;

        int _genderValue;
        int _abilityIndex;

        Nature _nature;
        //int _nature;

        int _level;
        int _curExp;
        int _IVs[6];
        int _EVs[6];

        int _moves[4];
        int _curHP;

        int _status;

        bool _isWild;

        void initMoves();


};

#endif // POKEMON_H