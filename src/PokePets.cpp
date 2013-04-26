#include <string>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

//#define WINDOWS_OS // uncomment if using windows
#ifdef WINDOWS_OS
    #include <windows.h>
#endif

#include "CSVReader.h"
#include "Pokemon.h"
#include "PokemonBattle.h"
#include "PokemonBuilder.h"

#define DIVIDER_LENGTH 120

void TestPokemon();

int main() {
// so the game starts with the intro dialogue
// then when you can actually do actions
// you go choose your starter
// and then battle your rival
// then from there on you go get badge
    TestPokemon();
    return 0;
}

void TestPokemon() {
    cout << "Enter a pokedex number: ";
    int dexNum;
    while ( ! (cin >> dexNum))
    {
        cout << "Invalid input!  Try again: ";
        cin.clear ();   // reset fail flag

        // skip past invalid input
        cin.ignore (1000, '\n');  // Skip to next newline or 1000 chars
    }

    cout << "Enter level: ";
    int lvl;
    while ( ! (cin >> lvl))
    {
        cout << "Invalid input!  Try again: ";
        cin.clear ();   // reset fail flag

        // skip past invalid input
        cin.ignore (1000, '\n');  // Skip to next newline or 1000 chars
    }

    cout << endl;

    Pokemon myPokemon(dexNum, lvl);
    CSVReader reader;
    PokemonBuilder builder;

    builder.setReader(&reader);

    builder.setPokemon(&myPokemon);
    builder.initSpecies();
    myPokemon.reset();
    myPokemon.setIsWild(false);


    cout << "How many battles would you like? " ;
    int battleNum;

    while ( ! (cin >> battleNum))
    {
        cout << "Invalid input!  Try again: ";
        cin.clear ();   // reset fail flag

        // skip past invalid input
        cin.ignore (1000, '\n');  // Skip to next newline or 1000 chars
    }

    // battle loop
    for (int i = 0; i < battleNum; ++i)
    {
        // generate random pokemon
        Pokemon enemyPkmn(rand()%151+1, myPokemon.getLevel());
        builder.setPokemon(&enemyPkmn);
        builder.initSpecies();

        // reset both pokemon
        enemyPkmn.reset();
        myPokemon.reset();

        // start battle
        PokemonBattle battle(&myPokemon, &enemyPkmn);
        battle.start();
    }

}
