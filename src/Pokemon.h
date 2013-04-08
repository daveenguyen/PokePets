#ifndef POKEMON_H
#define POKEMON_H

#include <string>

class Pokemon : public PokemonSpecies
{
    public:

        Pokemon(int dexNum, int level=1);
        ~Pokemon();

        void getNickname();
        void getGender();
        void getAbility();
        void getNature();
        void getLevel();
        void getCurExp();
        void getIVs(int i);
        void getEVs(int i);
        void getMoves(int i);
        void getCurHP();
        void getStatus();
        int  getStats(int i);

    private:

        string  _nickname;

        int _genderValue;
        int _abilityIndex;
        int _nature;

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