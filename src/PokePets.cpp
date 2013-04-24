#include <string>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <string>

//#define WINDOWS_OS // uncomment if using windows
#ifdef WINDOWS_OS
    #include <windows.h>
#endif

using namespace std;

#include "CSVReader.h"
#include "PokemonBuilder.h"
#include "Pokemon.h"

#include "Type.h"
#include "Move.h"
#include "PokemonBattle.h"


#define DIVIDER_LENGTH 120

void TestPokemon();
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
    cin  >> dexNum;
    cout << "Enter level: ";
    int lvl;
    cin  >> lvl;
    cout << endl;

    Pokemon myPokemon(dexNum, lvl);
    CSVReader reader;
    PokemonBuilder builder;

    builder.setReader(&reader);

    builder.setPokemon(&myPokemon);
    builder.initSpecies();
    myPokemon.reset();

    printPokemonInfo(&myPokemon);
    printPokemonMoves(&myPokemon);

    cout << endl;

    printPokemonStats(&myPokemon);

    cout << "How many battles would you like? " ;
    int battleNum;
    cin >> battleNum;

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
        battle.startBattle();
    }

}

void DamagePokemon(Pokemon* pkmn, int points)
{
    pkmn->adjustHP(-points);
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