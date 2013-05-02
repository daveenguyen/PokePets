#ifndef BULBASAUR_H
#define BULBASAUR_H

#include <string>
using namespace std;

#include "Pokemon.h"
#include "PokemonBuilder.h"

class Bulbasaur : public Pokemon
{
    public:
        Bulbasaur(PokemonBuilder* builder, int level=5);
        ~Bulbasaur();

    private:
        PokemonBuilder* _builder;
        bool curePoison(int item);
        void evolve();
};

#endif // BULBASAUR_H