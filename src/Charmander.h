#ifndef CHARMANDER_H
#define CHARMANDER_H

#include <string>
using namespace std;

#include "Pokemon.h"
#include "PokemonBuilder.h"

class Charmander : public Pokemon
{
    public:
        Charmander(PokemonBuilder* builder, int level=5);
        ~Charmander();

    private:
        PokemonBuilder* _builder;
        bool cureBurn(int item);
        void evolve();
};

#endif // CHARMANDER_H