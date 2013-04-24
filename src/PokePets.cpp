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
void printAllInfo(Pokemon* pkmn);
void printPokemonStats(Pokemon* pkmn);
void printPokemonInfo(Pokemon* pkmn);
void printPokemonMoves(Pokemon* pkmn);

int main() {
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

    printAllInfo(&myPokemon);

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

void DamagePokemon(Pokemon* pkmn, int points)
{
    pkmn->adjustHP(-points);
}

void printAllInfo(Pokemon* pkmn)
{
    printPokemonInfo(pkmn);
    printPokemonMoves(pkmn);
    printPokemonStats(pkmn);
}

void printPokemonInfo(Pokemon* pkmn)
{

    cout << "___ POKEMON INFO" << endl;
    cout << "NICKNAME: " << pkmn->getNickname() << endl;
    cout << "  GENDER: " << pkmn->getGender() << endl;

    // cout << " ABILITY: " << pkmn->getAbility() << endl;

    cout << "  NATURE: " << pkmn->getNature() << endl;

    cout << "   LEVEL: " << pkmn->getLevel()  << endl;
    cout << " CUR EXP: " << pkmn->getCurExp() << endl;
    cout << "  CUR HP: " << pkmn->getCurHP()  << endl;
    cout << "  STATUS: " << pkmn->getStatus() << endl << endl;

    cout << " TYPE[0]: " << pkmn->getType(0).getIdentifier() << endl;
    if (pkmn->getType(1).getTypeNum() != pkmn->getType(0).getTypeNum())
        cout << " TYPE[1]: " << pkmn->getType(1).getIdentifier() << endl;
    cout << endl;
}

void printPokemonStats(Pokemon* pkmn)
{
    cout << "___ STATS" << endl;
    cout << "      HP: " << pkmn->getStats(0) << endl;
    cout << "     ATK: " << pkmn->getStats(1) << endl;
    cout << "     DEF: " << pkmn->getStats(2) << endl;
    cout << "   S.ATK: " << pkmn->getStats(3) << endl;
    cout << "   S.DEF: " << pkmn->getStats(4) << endl;
    cout << "   SPEED: " << pkmn->getStats(5) << endl << endl;
}
void printPokemonMoves(Pokemon* pkmn)
{
    for (int i=0; i < 4 && pkmn->getMove(i).getMoveNum() != 0; ++i) {
        cout << "___ ";
        // Move myMove();
        cout << pkmn->getMove(i).getIdentifier() << endl;
        cout << "    TYPE: " << pkmn->getMove(i).getType().getIdentifier() << endl;
        cout << "   POWER: " << pkmn->getMove(i).getPower() << endl;
        cout << "      PP: " << pkmn->getMove(i).getPP() << endl;
        cout << "Accuracy: " << pkmn->getMove(i).getAccuracy() << endl << endl;
    }
}