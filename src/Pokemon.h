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
        Types   _types[2];
        Gender  _gender;
        Ability _ability;
        int     _level;
        Nature  _nature;
        int     _stats[6];
        int     _IVs[6];
        int     _EVs[6];
        Move    _moves[4];
        int     _curHP;

        };

#endif // POKEMON_H