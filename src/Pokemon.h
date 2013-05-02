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

        void   reset();

        void   setNickname(string i);
        string getNickname();

        void   setNature(string i);
        string getNature();

        void   setLevel(int i);
        int    getLevel();

        void   setCurExp(int i);
        int    getCurExp();

        void   setIV(int i, int x);
        int    getIV(int i);

        void   setEV(int i, int x);
        int    getEV(int i);

        void   setMove(int i, Move x);
        Move   getMove(int i);

        void   setStatus(int i);
        int    getStatus();

        int    getStatStage(int i);
        void   setStatStage(int i, int value);

        void   setIsWild(bool value);
        bool   isWild();

        void   setAilmentCounter(int i);

        void   checkAilment();

        void   checkExperience();

        void   adjustExperience(int baseExp, int faintLvl, bool isWild, int participated=1);

        void   adjustEffort(int hp, int atk, int def, int satk, int sdef, int spd);

        void   adjustHP(int i);

        int    getStats(int i);

        int    getBattleStats(int i);

        int    getCurHP();

        int    getCurPP(int i);

        string getGender();

        int    getAbility();

        void   useMove(int i, Pokemon* target);

        bool   cureStatus(int item);

    private:

        string  _nickname;

        int _genderValue;
        int _abilityIndex;

        Nature _nature;

        int _level;
        int _curExp;
        int _IVs[6];
        int _EVs[6];

        Move _moves[4];
        int  _curPP[4];
        int  _curHP;

        int  _status;
        int _ailmentCounter;

        bool _isWild;

        // battle stat boosts
        int _statStage[8];

        void initMoves();
        void doDamage(Pokemon* target, Move* move);
        void doAilment(Pokemon* target, Move* move);
        void doHealUser(Move* move);
        void doLowersTargetStat(Pokemon* target, Move* move);
        void doRaiseUserStat(Move* move);
        void doRaiseTargetStat(Pokemon* target, Move* move);

        // curing status by items
        // returns true if status was cured
        virtual bool cureParalysis(int item);
        virtual bool cureSleep(int item);
        virtual bool cureFrozen(int item);
        virtual bool cureBurn(int item);
        virtual bool curePoison(int item);

        virtual void evolve();
};

#endif // POKEMON_H