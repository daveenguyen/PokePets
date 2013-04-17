#ifndef POKEMONBUILDER_H
#define POKEMONBUILDER_H

#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class CSVReader;
class Pokemon;

/* Stuff that every Pokemon of the same pokemon species share */
class PokemonBuilder
{
    public:

        //PokemonBuilder(CSVReader* reader, int dexNum);

        //~PokemonBuilder();

        void initSpecies();
        void setReader(CSVReader* myReader);
        void setPokemon(Pokemon* myPkmn);

    private:

        CSVReader*  _reader;
        Pokemon*    _pkmn;
        int         _dexNum;

};

#endif // POKEMONBUILDER_H