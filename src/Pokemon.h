#ifndef POKEMON_H
#define POKEMON_H

#include <string>
using namespace std;

#include "PokemonSpecies.h" // parent class
#include "Nature.h"         // pokemon has a nature
#include "Move.h"

class Pokemon : public PokemonSpecies
{
    public:

        Pokemon(int dexNum, int level=1);
        ~Pokemon();

        void reset();

        void   setLevel(int i);

        string getNickname();
        string getGender();
        string getNature();
        int    getAbility();
        int    getLevel();
        int    getCurExp();
        int    getIVs(int i);
        int    getEVs(int i);
        Move   getMove(int i);
        int    getCurHP();
        int    getStatus();
        int    getStats(int i);
        int    getCurPP(int i);
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

        //int _moves[4];
        Move _moves[4];
        int  _curPP[4];
        int  _curHP;

        int  _status;

        bool _isWild;

        // battle stats/boosts
        int _atkStage;
        int _defStage;
        int _sAtkStage;
        int _sDefStage;
        int _speedStage;
        int _evasionStage;
        int _accuracyStage;
        // int _critStage;


        void initMoves();
        void doDamage(Pokemon* target, Move* move);


};

#endif // POKEMON_H