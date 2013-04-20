#include <string>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

#include "PokemonBuilder.h"
#include "CSVReader.h"
#include "DBParser.h"
#include "Pokemon.h"
#include "Type.h"
#include "Move.h"

//#define WINDOWS_OS // uncomment if using windows
#ifdef WINDOWS_OS
#include "windows.h"
#endif

#define DIVIDER_LENGTH 120

// ANSI Color Codes
#define C_RED     "\33[31;49m"
#define C_GREEN   "\33[32;49m"
#define C_YELLOW  "\33[33;49m"
#define C_BLUE    "\33[34;49m"
#define C_MAGENTA "\33[35;49m"
#define C_CYAN    "\33[36;49m"
#define C_WHITE   "\33[37;49m"
#define C_BOLD    "\33[31;1m"
#define C_RESET   "\33[0m"

#define C_NORMAL    "\33[38;5;144m"  // 144 :af/af/87
#define C_FIRE      "\33[38;5;209m"  // 209 :ff/87/5f
#define C_WATER     "\33[38;5;69m"  // 69:  5f/87/ff
#define C_ELECTRIC  "\33[38;5;221m"  // 221 :ff/d7/5f
#define C_GRASS     "\33[38;5;113m"  // 113 :87/d7/5f
#define C_ICE       "\33[38;5;116m"  // 116 :87/d7/d7
#define C_FIGHTING  "\33[38;5;167m"  // 167 :d7/5f/5f
#define C_POISON    "\33[38;5;133m"  // 133 :af/5f/af
#define C_GROUND    "\33[38;5;185m"  // 185 :d7/d7/5f
#define C_FLYING    "\33[38;5;141m"  // 141 :af/87/ff
#define C_PSYCHIC   "\33[38;5;204m"  // 204 :ff/5f/87
#define C_BUG       "\33[38;5;142m"  // 142 :af/af/00
#define C_ROCK      "\33[38;5;143m"  // 143 :af/af/5f
#define C_GHOST     "\33[38;5;96m"  // 96:  87/5f/87
#define C_DRAGON    "\33[38;5;99m"  // 99:  87/5f/ff
#define C_DARK      "\33[38;5;95m"  // 95:  87/5f/5f
#define C_STEEL     "\33[38;5;146m"  // 146 :af/af/d7

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
void drawPokemons(Pokemon* myPkmn, Pokemon* enemyPkmn);
void printTypeWithColor(int i);
void printBattleOptions(Pokemon* pkmn);

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
        Pokemon enemyPkmn(rand()%151+1, myPokemon.getLevel());
        builder.setPokemon(&enemyPkmn);
        builder.initSpecies();

        // reset both pokemon
        enemyPkmn.reset();
        myPokemon.reset();

        // start battle
        // cout << "You are challenged by Dude!" << endl;
        // cout << "Dude sent out " << enemyPkmn.getNickname() << '!' << endl;
        cout << "A wild " << enemyPkmn.getNickname() << " appeared!" << endl;

        cout << "Go! " << myPokemon.getNickname() << '!' << endl;

        while (myPokemon.getCurHP() > 0 && enemyPkmn.getCurHP() > 0)
        {
            delay(1750);
            cout << endl<< endl<< endl<< endl<< endl<< endl<< endl<< endl<< endl<< endl<< endl<< endl<< endl<< endl<< endl<< endl<< endl<< endl<< endl<< endl<< endl<< endl<< endl;
            for(int i = 0; i < DIVIDER_LENGTH; ++i)
                cout << "_";
            cout <<endl;


            for(int i = 32; i < DIVIDER_LENGTH; ++i)
                cout << " ";
            cout <<enemyPkmn.getNickname() << " Lv." << enemyPkmn.getLevel() << endl;

            for(int i = 32; i < DIVIDER_LENGTH; ++i)
                cout << " ";
            printHpBars(&enemyPkmn);

            for(int i = 32; i < DIVIDER_LENGTH; ++i)
                cout << " ";
            cout <<"HP: " << (int)(float(enemyPkmn.getCurHP())/enemyPkmn.getStats(0)*100) << "%";
            switch (enemyPkmn.getStatus())
            {
                case 1: // paralysis (PAR)
                    cout << C_ELECTRIC << " PAR" << C_RESET;
                    break;
                case 2: // sleep (SLP)
                cout << C_NORMAL << " SLP" << C_RESET;
                    break;
                case 3: // freeze (FRZ)
                    cout << C_ICE << " FRZ" << C_RESET;
                    break;
                case 4: // burn (BRN)
                    cout << C_FIRE << " BRN" << C_RESET;
                    break;
                case 5: // poison (PSN)
                    cout << C_POISON << " PSN" << C_RESET;
                    break;
                default:
                    break;

            }
            cout << endl;
            drawPokemons(&myPokemon, &enemyPkmn);

            cout << myPokemon.getNickname() << " Lv." << myPokemon.getLevel() << endl;
            printHpBars(&myPokemon);
            cout << "HP: " << myPokemon.getCurHP() << " / " << myPokemon.getStats(0);
            switch (myPokemon.getStatus())
            {
                case 1: // paralysis (PAR)
                    cout << C_ELECTRIC << " PAR" << C_RESET;
                    break;
                case 2: // sleep (SLP)
                cout << C_NORMAL << " SLP" << C_RESET;
                    break;
                case 3: // freeze (FRZ)
                    cout << C_ICE << " FRZ" << C_RESET;
                    break;
                case 4: // burn (BRN)
                    cout << C_FIRE << " BRN" << C_RESET;
                    break;
                case 5: // poison (PSN)
                    cout << C_POISON << " PSN" << C_RESET;
                    break;
                default:
                    break;

            }
            cout << endl;
            cout << endl << endl;
            int num;
            printBattleOptions(&myPokemon);
            printAttackOptions(&myPokemon);
            cout << "\nWhat will " << myPokemon.getNickname() << " do? ";
            cin >> num;
            num--;

            for(int i = 0; i < DIVIDER_LENGTH; ++i)
                cout << "_";
            cout <<endl;

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

void printAttackOptions(Pokemon* pkmn)
{
    cout << "    ATTACK OPTIONS" << endl;
    for(int i = 0; i < DIVIDER_LENGTH; ++i)
        cout << "-";
    cout <<endl;

    // line 1
    for (int i=0; i < 4 && pkmn->getMove(i).getMoveNum() != 0; ++i) {

        cout << left << setfill(' ');
        cout << "| " << i+1 << ". ";
        cout << setw(DIVIDER_LENGTH/4-5) << pkmn->getMove(i).getIdentifier();
    }
    cout << "|" << endl;

    // line 2
    for (int i=0; i < 4 && pkmn->getMove(i).getMoveNum() != 0; ++i) {
        cout << "|    ";
        printTypeWithColor(pkmn->getMove(i).getType().getTypeNum());
        cout << setw((DIVIDER_LENGTH/4-15)) <<pkmn->getMove(i).getType().getIdentifier() << C_RESET;
        cout << " PP ";
        cout << right << setw(2) << pkmn->getCurPP(i);
        cout << '/';
        cout << left << setw(2) << pkmn->getMove(i).getPP() << ' ';
    }
    cout << "|" << endl;

    // line 3
    for (int i=0; i < 4 && pkmn->getMove(i).getMoveNum() != 0; ++i) {
        cout << "|    ";
        cout << "Power "; //6
        cout << setw(3) << pkmn->getMove(i).getPower();
        cout << setw(DIVIDER_LENGTH/4-18) << right << " Accuracy "; //10
        cout << right << setw(3) << pkmn->getMove(i).getAccuracy() << ' ';
    }
    cout << "|" << endl;

    for(int i = 0; i < DIVIDER_LENGTH; ++i)
        cout << "-";
    cout <<endl;
}

void printBattleOptions(Pokemon* pkmn)
{

    cout << "    BATTLE OPTIONS" << endl;
    cout << "----------------------" << endl;
    cout << " 1. Fight " << endl;
    cout << " 2. PokePets " << endl;
    cout << " 3. Bag " << endl;
    cout << " 4. Run " << endl;
    cout << "\nWhat will " << pkmn->getNickname() << " do? ";

    cout << endl;
}

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

    cout << "[" << C_BOLD;

    if (hpPercent > 0.5)
    {
        cout << C_GREEN;
    }
    else if (hpPercent > 0.2)
    {
        cout << C_YELLOW;
    }
    else
    {
        cout << C_RED;
    }

    for (int i = 0; i < 30; ++i)
    {
        if (hpPercent >= 0)
            cout << '=';
        else
            cout << ' ';

        hpPercent -= 0.03333333333;
    }
    cout << C_RESET;
    cout << "]" << endl;

}

void drawPokemons(Pokemon* myPkmn, Pokemon* enemyPkmn)
{

    int backNum  = myPkmn->getDexNum();
    int frontNum = enemyPkmn->getDexNum();

    string pkmnBack[16];
    string pkmnFront[16];

    stringstream ss;
    ss << frontNum;
    string str = ss.str();

    string filePathStr = "../data/xterm/front/" + str + ".xterm";

    ifstream reader;
    reader.open(filePathStr.c_str());
    for (int i = 0; i < 16; ++i)
    {
        getline(reader,pkmnFront[i]);
    }

    ss.str("");
    ss << backNum;
    str = ss.str();
    filePathStr = "../data/xterm/back/" + str + ".xterm";
    reader.close();
    reader.open(filePathStr.c_str());
    for (int i = 0; i < 16; ++i)
    {
        getline(reader,pkmnBack[i]);
    }

    for (int i = 0; i < 16; i++)
    {
        cout << setw(DIVIDER_LENGTH-32) << ' ' << pkmnFront[i] << endl;
    }

    for (int i = 0; i < 16; i++)
    {
        cout << setw(32) << pkmnBack[i] << endl;
    }
}

void printTypeWithColor(int i)
{
    switch (i)
    {
        case 1:
            cout << C_NORMAL   ;
            break;
        case 2:
            cout << C_FIGHTING ;
            break;
        case 3:
            cout << C_FLYING   ;
            break;
        case 4:
            cout << C_POISON   ;
            break;
        case 5:
            cout << C_GROUND   ;
            break;
        case 6:
            cout << C_ROCK     ;
            break;
        case 7:
            cout << C_BUG      ;
            break;
        case 8:
            cout << C_GHOST    ;
            break;
        case 9:
            cout << C_STEEL    ;
            break;
        case 10:
            cout << C_FIRE     ;
            break;
        case 11:
            cout << C_WATER    ;
            break;
        case 12:
            cout << C_GRASS    ;
            break;
        case 13:
            cout << C_ELECTRIC ;
            break;
        case 14:
            cout << C_PSYCHIC  ;
            break;
        case 15:
            cout << C_ICE      ;
            break;
        case 16:
            cout << C_DRAGON   ;
            break;
        case 17:
            cout << C_DARK     ;
            break;
        default:
            cout << C_RESET;
            break;
    }
}