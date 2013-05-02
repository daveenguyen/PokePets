#include <iostream>
using namespace std;

#include "Squirtle.h"

Squirtle::Squirtle(PokemonBuilder* builder, int level):
    _builder(builder),
    Pokemon(7,level)
{
    _builder->setPokemon(this);
    _builder->initSpecies();
    reset();
}

// can cure frozen without any item
bool Squirtle::cureFrozen(int item)
{
    setStatus(0);
    return true;
}

void Squirtle::evolve()
{
    bool evolving = false;

    // evolve into wartortle at 16
    if (getDexNum()==7 && getLevel() >= 16)
    {
        setDexNum(8);
        evolving = true;
    }
    // evolve into blastoise at 36
    else if (getDexNum()==8 && getLevel() >= 36)
    {
        setDexNum(9);
        evolving = true;
    }

    if (evolving)
    {
        cout << endl << getNickname();
        _builder->setPokemon(this);
        _builder->initSpecies();
        cout << " evolved into " << getName() << "!\n\n";
        reset();
    }
}