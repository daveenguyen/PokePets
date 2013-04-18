#include <iostream>
#include <string>

using namespace std;

#include "PokemonBuilder.h"
#include "CSVReader.h"
#include "DBParser.h"
#include "Pokemon.h"
#include "Type.h"
#include "Move.h"

// #define WINDOWS_OS // uncomment if using windows

void TestPokemon();
void TestParser();
void TestType();

void delay(int i);
void DamagePokemon(Pokemon* pkmn, int points);
void printPokemonStats(Pokemon* pkmn);
void printPokemonInfo(Pokemon* pkmn);
void printPokemonMoves(Pokemon* pkmn);
void printAttackOptions(Pokemon* pkmn);
void printHpBars(Pokemon* pkmn);

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

    for (int i = 0; i < battleNum; ++i)
    {
        Pokemon enemyPkmn(rand()%151+1, myPokemon.getLevel());
        builder.setPokemon(&enemyPkmn);
        builder.initSpecies();
        enemyPkmn.reset();
        myPokemon.reset();

        // cout << "You are challenged by Dude!" << endl;
        // cout << "Dude sent out " << enemyPkmn.getNickname() << '!' << endl;
        cout << "A wild " << enemyPkmn.getNickname() << " appeared!" << endl;

        cout << "Go! " << myPokemon.getNickname() << '!' << endl;

        while (myPokemon.getCurHP() > 0 && enemyPkmn.getCurHP() > 0)
        {
            delay(1750);
            cout << endl<< endl<< endl<< endl<< endl<< endl<< endl<< endl<< endl<< endl<< endl<< endl<< endl<< endl<< endl<< endl<< endl<< endl<< endl<< endl<< endl<< endl<< endl;
            cout << "______________________________________________"<<endl;
            cout << "\t\t\t" <<enemyPkmn.getNickname() << " Lv." << enemyPkmn.getLevel() << endl;

            cout << "\t\t\t";
            printHpBars(&enemyPkmn);

            cout << "\t\t\t" <<"HP: " << (int)(float(enemyPkmn.getCurHP())/enemyPkmn.getStats(0)*100) << "\%" << endl;

            cout << myPokemon.getNickname() << " Lv." << myPokemon.getLevel() << endl;
            printHpBars(&myPokemon);
            cout << "HP: " << myPokemon.getCurHP() << " / " << myPokemon.getStats(0) << endl << endl;
            int num;
            printAttackOptions(&myPokemon);
            cout << "\nWhat would " << myPokemon.getNickname() << " do? ";
            cin >> num;
            num--;

            cout << "______________________________________________"<<endl;

            myPokemon.useMove(num,&enemyPkmn);
            int moveCount = 0;
            for (int i = 0; i < 4; ++i)
            {
                if (enemyPkmn.getMove(i).getMoveNum() != 0) moveCount++;
            }
            enemyPkmn.useMove(rand()%moveCount,&myPokemon);
            // int initialHP = myPokemon.getCurHP();
            // DamagePokemon(&myPokemon, num);
            // int finalHP = myPokemon.getCurHP();
            // cout << myPokemon.getNickname() << " took " << (initialHP - finalHP) << " damage!" << endl;
        }

        if (myPokemon.getCurHP() <= 0)
        {
            cout << myPokemon.getNickname() << " fainted!" << endl;
        }
        else
        {
            cout << enemyPkmn.getNickname() << " fainted!" << endl;
            myPokemon.adjustExperience(enemyPkmn.getBaseExp(), enemyPkmn.getLevel(), false, 1);
        }

        cout << "   LEVEL: " << myPokemon.getLevel()  << endl;
        cout << " CUR EXP: " << myPokemon.getCurExp() << endl;
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
        cout << i+1 << ". ";
        // Move myMove();
        cout << pkmn->getMove(i).getIdentifier() << endl;
        cout << "   " << pkmn->getMove(i).getType().getIdentifier() << "  PP " << pkmn->getCurPP(i) << '/' << pkmn->getMove(i).getPP() << endl;
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

void delay(int ms)
{
    #ifdef WINDOWS_OS
        Sleep(ms);
    #else
        usleep(ms*1000);
    #endif
}

void printHpBars(Pokemon* pkmn)
{
    double hpPercent = pkmn->getCurHP()/(double)pkmn->getStats(0);

    cout << "[" ;
    for (int i = 0; i < 20; ++i)
    {
        if (hpPercent >= 0)
            cout << '-';
        else
            cout << ' ';

        hpPercent -= 0.05;
    }
    cout << "]" << endl;

}