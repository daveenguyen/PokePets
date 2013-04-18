#include <iostream>
#include <string>

using namespace std;

#include "PokemonBuilder.h"
#include "CSVReader.h"
#include "DBParser.h"
#include "Pokemon.h"
#include "Type.h"
#include "Move.h"

void TestPokemon();
void TestParser();
void TestType();

void DamagePokemon(Pokemon* pkmn, int points);
void printPokemonStats(Pokemon* pkmn);
void printPokemonInfo(Pokemon* pkmn);
void printPokemonMoves(Pokemon* pkmn);
void printAttackOptions(Pokemon* pkmn);

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

    while (myPokemon.getCurHP() > 0)
    {
        cout << myPokemon.getNickname() << " Lv." << myPokemon.getLevel() << endl;
        cout << "HP: " << myPokemon.getCurHP() << " / " << myPokemon.getStats(0) << endl << endl;
        int num;
        printAttackOptions(&myPokemon);
        cout << "What would you like to do?" << endl;
        cin >> num;
        myPokemon.useMove(num,&myPokemon);
        // int initialHP = myPokemon.getCurHP();
        // DamagePokemon(&myPokemon, num);
        // int finalHP = myPokemon.getCurHP();
        // cout << myPokemon.getNickname() << " took " << (initialHP - finalHP) << " damage!" << endl;
    }

    cout << myPokemon.getNickname() << " fainted!" << endl;

    myPokemon.adjustExperience(myPokemon.getBaseExp(), myPokemon.getLevel(), false, 1);

    cout << "   LEVEL: " << myPokemon.getLevel()  << endl;
    cout << " CUR EXP: " << myPokemon.getCurExp() << endl;
    // cout << "      HP: " << myPokemon.getCurHP() << " / " << myPokemon.getStats(0) << endl;

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

    cout << " ABILITY: " << pkmn->getAbility() << endl;

    cout << "  NATURE: " << pkmn->getNature() << endl;

    cout << "   LEVEL: " << pkmn->getLevel()  << endl;
    cout << " CUR EXP: " << pkmn->getCurExp() << endl;
    cout << "  CUR HP: " << pkmn->getCurHP()  << endl;
    cout << "  STATUS: " << pkmn->getStatus() << endl << endl;

    // for (int i=0; i < 2 && pkmn->getType(i).getTypeNum() != 0; ++i) {
        // DBParser type(pkmn->getType(i), 1);
        // cout << " TYPE["<< i << "]: " << type.getTypeString() << endl;
    // }
    cout << " TYPE[0]: " << pkmn->getType(0).getIdentifier() << endl;
    if (pkmn->getType(1).getTypeNum() != pkmn->getType(0).getTypeNum())
        cout << " TYPE[0]: " << pkmn->getType(1).getIdentifier() << endl;
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

void printAttackOptions(Pokemon* pkmn)
{
    cout << "___ ATTACK OPTIONS" << endl;
    for (int i=0; i < 4 && pkmn->getMove(i).getMoveNum() != 0; ++i) {
        cout << i << ". ";
        // Move myMove();
        cout << pkmn->getMove(i).getIdentifier() << endl;
    }
}

// void printBattleOptions(Trainer* trainer)
// {
//     cout << "1. Fight" << endl;
//     cout << "2. PokePets" << endl;
//     cout << "3. Run" << endl << endl;
//     cout << "What will " << trainer->curPokemon() << " do? " << endl;
//     int option;
//     cin >> option;

//     switch (option)
//     {
//         case 1:
//         {
//             fight(trainer);
//             break;
//         }
//         case 2:
//         {
//             pokepets(trainer);
//             break;
//         }
//         case 3:
//         {
//             run(trainer);
//             break;
//         }
//         default:
//         {
//             printBattleOptions(trainer);
//             break;
//         }
//     }
// }