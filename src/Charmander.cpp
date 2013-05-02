#include <iostream>
using namespace std;

#include "Charmander.h"

Charmander::Charmander(PokemonBuilder* builder, int level):
    _builder(builder),
    Pokemon(4,level)
{
    _builder->setPokemon(this);
    _builder->initSpecies();
    reset();
}

// can cure burn without any item
bool Charmander::cureBurn(int item)
{
    setStatus(0);
    return true;
}

void Charmander::evolve()
{
    bool evolving = false;

    // evolve into wartortle at 16
    if (getDexNum()==4 && getLevel() >= 16)
    {
        setDexNum(5);
        evolving = true;
    }
    // evolve into blastoise at 36
    else if (getDexNum()==5 && getLevel() >= 36)
    {
        setDexNum(6);
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