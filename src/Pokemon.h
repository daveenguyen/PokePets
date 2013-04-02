#ifndef POKEMON_H
#define POKEMON_H

#include <string>

class Pokemon
{
    public:

        Pokemon(Species species);

        ~Pokemon();

    private:

        string  _nickname;

        Species _species;
        Gender  _gender;
        Ability _ability;
        Nature  _nature;

        int     _level;
        int     _stats[6];
        int     _IVs[6];
        int     _EVs[6];

        Move    _moves[4];
        int     _curHP;

        Status _status;

        };

#endif // POKEMON_H