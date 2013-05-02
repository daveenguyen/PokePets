#include <iostream>
using namespace std;

#include "Bulbasaur.h"

Bulbasaur::Bulbasaur(PokemonBuilder* builder, int level):
    _builder(builder),
    Pokemon(1,level)
{
    _builder->setPokemon(this);
    _builder->initSpecies();
    reset();
}

// can cure poison without any item
bool Bulbasaur::curePoison(int item)
{
    setStatus(0);
    return true;
}

void Bulbasaur::evolve()
{
    bool evolving = false;

    // evolve into wartortle at 16
    if (getDexNum()==1 && getLevel() >= 16)
    {
        setDexNum(2);
        evolving = true;
    }
    // evolve into blastoise at 36
    else if (getDexNum()==2 && getLevel() >= 33)
    {
        setDexNum(3);
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