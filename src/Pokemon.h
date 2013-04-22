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

        void setNickname(string i);
        // void setGender(string i);
        // void setAbility(int i);
        void setNature(string i);
        void setLevel(int i);
        void setCurExp(int i);
        void setIV(int i, int x);
        void setEV(int i, int x);
        void setMove(int i, Move x);
        // void setCurHP(int i);
        void setStatus(int i);
        // void setStats(int i, int x);

        string getNickname();
        string getGender();
        int    getAbility();
        string getNature();
        int    getLevel();
        int    getCurExp();
        int    getIV(int i);
        int    getEV(int i);
        Move   getMove(int i);
        int    getCurHP();
        int    getStatus();
        int    getStats(int i);
        int    getBattleStats(int i);
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
        void doAilment(Pokemon* target, Move* move);

};

#endif // POKEMON_H