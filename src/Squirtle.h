#ifndef SQUIRTLE_H
#define SQUIRTLE_H

#include <string>
using namespace std;

#include "Pokemon.h"
#include "PokemonBuilder.h"

class Squirtle : public Pokemon
{
    public:
        Squirtle(PokemonBuilder* builder, int level=5);
        ~Squirtle();

    private:
        PokemonBuilder* _builder;
        bool cureFrozen(int item);
        void evolve();
};

#endif // SQUIRTLE_H