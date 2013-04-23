#include <iostream>
#include <iomanip>
#include <cstdlib>

using namespace std;

#include "PokemonBattle.h"


//#define WINDOWS_OS // uncomment if using windows
#ifdef WINDOWS_OS
    #include <windows.h>
#else
    #include <unistd.h>
#endif

#define DIVIDER_LENGTH 120


#define C_RED     "\33[31;49m"
#define C_GREEN   "\33[32;49m"
#define C_YELLOW  "\33[33;49m"
#define C_BLUE    "\33[34;49m"
#define C_MAGENTA "\33[35;49m"
#define C_CYAN    "\33[36;49m"
#define C_WHITE   "\33[37;49m"
#define C_BOLD    "\33[31;1m"
#define C_RESET   "\33[0m"

#define C_NORMAL    "\33[38;5;144m"  // 144: af/af/87
#define C_FIRE      "\33[38;5;209m"  // 209: ff/87/5f
#define C_WATER     "\33[38;5;69m"   // 69:  5f/87/ff
#define C_ELECTRIC  "\33[38;5;221m"  // 221: ff/d7/5f
#define C_GRASS     "\33[38;5;113m"  // 113: 87/d7/5f
#define C_ICE       "\33[38;5;116m"  // 116: 87/d7/d7
#define C_FIGHTING  "\33[38;5;167m"  // 167: d7/5f/5f
#define C_POISON    "\33[38;5;133m"  // 133: af/5f/af
#define C_GROUND    "\33[38;5;185m"  // 185: d7/d7/5f
#define C_FLYING    "\33[38;5;141m"  // 141: af/87/ff
#define C_PSYCHIC   "\33[38;5;204m"  // 204: ff/5f/87
#define C_BUG       "\33[38;5;142m"  // 142: af/af/00
#define C_ROCK      "\33[38;5;143m"  // 143: af/af/5f
#define C_GHOST     "\33[38;5;96m"   // 96:  87/5f/87
#define C_DRAGON    "\33[38;5;99m"   // 99:  87/5f/ff
#define C_DARK      "\33[38;5;95m"   // 95:  87/5f/5f
#define C_STEEL     "\33[38;5;146m"  // 146: af/af/d7


PokemonBattle::PokemonBattle(Pokemon* myPkmn, Pokemon* enemyPkmn):myPkmn(myPkmn), enemyPkmn(enemyPkmn)
{
}

void PokemonBattle::startBattle()
{
    printBattleInit();
    _state = 0;

    bool battleDone = false;
    // while (myPkmn->getCurHP() > 0 && enemyPkmn->getCurHP() > 0 && _state != -1)
    while (!battleDone)
    {
        printCommon();
        if (isDead(myPkmn))
        {
            _state = -2;
        }
        else if (isDead(enemyPkmn))
        {
            _state = -3;
        }

        switch(_state)
        {
            case -3:
                // enemy dead
                if (enemyPkmn->isWild())
                {
                    cout << "Wild ";
                }
                else
                {
                    cout << "The foe's ";
                }
                cout << enemyPkmn->getNickname() << " fainted!" << endl;
                battleDone = true;
                delay(1750);
                break;
            case -2:
                // you dead
                cout << myPkmn->getNickname() << " fainted!" << endl;
                battleDone = true;
                delay(1750);
                break;
            case -1:
                cout << "You run away!";
                battleDone = true;
                delay(1750);
                break;
            case 0:
                printBattleOptions();
                break;
            case 1:
                // fight
                printAttackOptions(myPkmn);
                break;
            case 2:
                doMove();
                break;
            case 3:
                break;
            case 4:
                break;
            default:

                break;
        }
    }

}

void PokemonBattle::printBattleInit()
{
    // clear screen
    for (int i = 0; i < 60; ++i)
    {
        cout << endl;
    }

    if (!enemyPkmn->isWild())
    {
        cout << "You are challenged by Dude!" << endl;
        cout << "Dude sent out " << enemyPkmn->getNickname() << '!' << endl;
    }
    else
    {
        cout << "A wild " << enemyPkmn->getNickname() << " appeared!" << endl;
    }

    cout << "Go! " << myPkmn->getNickname() << '!' << endl;
}


void PokemonBattle::printBattleOptions()
{
    cout << "    BATTLE OPTIONS" << endl;
    cout << "----------------------" << endl;
    cout << " 1. Fight " << endl;
    cout << " 2. PokePets " << endl;
    cout << " 3. Bag " << endl;
    cout << " 4. Run " << endl;
    cout << "\nWhat will " << myPkmn->getNickname() << " do? ";
    cout << endl;

    int userInput;
    cin >> userInput;

    switch (userInput)
    {
        case 1:
            // fight
            _state = 1;
            break;
        case 2:
            // pokepets
            _state = 2;
            break;
        case 3:
            // bag
            _state = 3;
            break;
        case 4:
            // run
            //http://bulbapedia.bulbagarden.net/wiki/Escape
            _state = -1;
            break;
        default:
            break;
    }
}

void PokemonBattle::printCommon()
{
    // clear a bit of screen
    for (int i = 0; i < 15; ++i)
    {
        cout << endl;
    }

    for(int i = 0; i < DIVIDER_LENGTH; ++i)
    {
        cout << "_";
    }
    cout <<endl;

    // print enemy info
    for(int i = 32; i < DIVIDER_LENGTH; ++i)
    {
        cout << " ";
    }
    cout << enemyPkmn->getNickname() << " Lv." << enemyPkmn->getLevel() << endl;


    for(int i = 32; i < DIVIDER_LENGTH; ++i)
    {
        cout << " ";
    }
    printHpBars(enemyPkmn);

    for(int i = 32; i < DIVIDER_LENGTH; ++i)
        cout << " ";
    cout <<"HP: " << (int)(float(enemyPkmn->getCurHP())/enemyPkmn->getStats(0)*100) << "%";

    switch (enemyPkmn->getStatus())
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

    drawPokemons();


    // print my info
    cout << myPkmn->getNickname() << " Lv." << myPkmn->getLevel() << endl;
    printHpBars(myPkmn);

    cout << "HP: " << myPkmn->getCurHP() << " / " << myPkmn->getStats(0);
    switch (myPkmn->getStatus())
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
}

void PokemonBattle::printAttackOptions(Pokemon* pkmn)
{
    int moveCount = 0;

    for (int i = 0; i < 4 && pkmn->getMove(i).getMoveNum() != 0; ++i)
    {
        ++moveCount;
    }

    cout << "    ATTACK OPTIONS" << endl;
    for(int i = 0; i < (int)(moveCount*DIVIDER_LENGTH/4.0); ++i)
        cout << "-";
    cout << endl;

    // line 1
    for (int i=0; i < moveCount; ++i) {

        cout << left << setfill(' ');
        cout << "| " << i+1 << ". ";
        cout << setw(DIVIDER_LENGTH/4-5) << pkmn->getMove(i).getIdentifier();
    }
    cout << "|" << endl;

    // line 2
    for (int i=0; i < moveCount; ++i) {
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
    for (int i=0; i < moveCount; ++i) {
        cout << "|    ";
        cout << "Power "; //6
        cout << setw(3) << pkmn->getMove(i).getPower();
        cout << setw(DIVIDER_LENGTH/4-18) << right << " Accuracy "; //10
        cout << right << setw(3) << pkmn->getMove(i).getAccuracy() << ' ';
    }
    cout << "|" << endl;

    for(int i = 0; i < (int)(moveCount*DIVIDER_LENGTH/4.0); ++i)
        cout << "-";
    cout << endl;
    cout << "5. Go back" << endl;

    cout << "\nWhat will " << myPkmn->getNickname() << " do? ";
    cout << endl;

    int userInput;
    cin >> userInput;

    switch (userInput)
    {
        case 1:
        case 2:
        case 3:
        case 4:
            // moves
            if (userInput <= moveCount)
            {
                checkPP(userInput);
            }
            break;
        case 5:
            _state = 0;
            break;
        default:
            break;
    }
}

void PokemonBattle::printHpBars(Pokemon* pkmn)
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
        if (hpPercent > 0)
            cout << '=';
        else
            cout << ' ';

        hpPercent -= 0.03333333333;
    }
    cout << C_RESET;
    cout << "]" << endl;
}

void PokemonBattle::drawPokemons()
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

void PokemonBattle::printTypeWithColor(int i)
{
    switch (i)
    {
        case 1:
            cout << C_NORMAL;
            break;
        case 2:
            cout << C_FIGHTING;
            break;
        case 3:
            cout << C_FLYING;
            break;
        case 4:
            cout << C_POISON;
            break;
        case 5:
            cout << C_GROUND;
            break;
        case 6:
            cout << C_ROCK;
            break;
        case 7:
            cout << C_BUG;
            break;
        case 8:
            cout << C_GHOST;
            break;
        case 9:
            cout << C_STEEL;
            break;
        case 10:
            cout << C_FIRE;
            break;
        case 11:
            cout << C_WATER;
            break;
        case 12:
            cout << C_GRASS;
            break;
        case 13:
            cout << C_ELECTRIC;
            break;
        case 14:
            cout << C_PSYCHIC;
            break;
        case 15:
            cout << C_ICE;
            break;
        case 16:
            cout << C_DRAGON;
            break;
        case 17:
            cout << C_DARK;
            break;
        default:
            cout << C_RESET;
            break;
    }
}

void PokemonBattle::checkPP(int move)
{
    if (myPkmn->getMove(move-1).getPP() > 0)
    {
        // do move
        _state = 2;
        _playerMove = move-1;
    }
    else
    {
        // check all moves PP
        int moveCount = 0;

        for (int i = 0; i < 4 && myPkmn->getMove(i).getMoveNum() != 0; ++i)
        {
            ++moveCount;
        }

        bool noPPall = true;
        for(int i = 0; i < moveCount; ++i)
        {
            if (myPkmn->getMove(i).getPP() > 0)
            {
                noPPall = false;
                break;
            }
        }

        if (noPPall)
        {
            // use struggle
            _playerMove = -1;
        }
        else
        {
            // not enough PP
            cout << "No more PP!" << endl;
        }
    }
}

void PokemonBattle::doPlayerMove()
{
        if (_playerMove!=-1)
        {
            myPkmn->useMove(_playerMove,enemyPkmn);
        }
        else
        {
            // struggle
        }
}

void PokemonBattle::doEnemyMove()
{
    int moveCount = 0;
    for (int i = 0; i < 4 && enemyPkmn->getMove(i).getMoveNum() != 0; ++i)
    {
        moveCount++;
    }
    enemyPkmn->useMove(rand()%moveCount,myPkmn);
}

void PokemonBattle::doMove()
{
    // me first
    if (meFirst())
    {
        doPlayerMove();

        if(!isDead(enemyPkmn))
        {
            doEnemyMove();
        }
    }
    // enemy first
    else
    {
        doEnemyMove();

        if(!isDead(myPkmn))
        {
            doPlayerMove();
        }
    }

    doEndTurn();
    _state = 0;
}

bool PokemonBattle::meFirst()
{
    bool meFirst;

    if (enemyPkmn->getStats(5) > myPkmn->getStats(5))
    {
        meFirst = false;
    }
    else if (enemyPkmn->getStats(5) < myPkmn->getStats(5))
    {
        meFirst = true;
    }
    else
    {
        meFirst = true; // favor player for now
    }

    return meFirst;
}

bool PokemonBattle::isDead(Pokemon* pkmn)
{
    return (pkmn->getCurHP()==0);
}

void PokemonBattle::doEndTurn()
{
    if(!isDead(myPkmn) && !isDead(enemyPkmn))
    {
        // check for burn or poison
        if (meFirst())
        {
            if (myPkmn->getStatus() == 2)
            {
            // 2 sleep
                //dec sleepcounter
            }
            else if (myPkmn->getStatus() == 4)
            {
                // 4 burn
                myPkmn->adjustHP((int)(-myPkmn->getStats(0)/8.0));
                cout << myPkmn->getNickname() << " was hurt by burn." << endl;
            }
            else if (myPkmn->getStatus() == 5)
            {
            // 5 poison
                myPkmn->adjustHP((int)(-myPkmn->getStats(0)/8.0));
                cout << myPkmn->getNickname() << " was hurt by poison." << endl;
            }

            if (enemyPkmn->getStatus() == 2)
            {
            // 2 sleep
                //dec sleepcounter
            }
            else if (enemyPkmn->getStatus() == 4)
            {
                // 4 burn
                enemyPkmn->adjustHP((int)(-enemyPkmn->getStats(0)/8.0));

                if (enemyPkmn->isWild())
                {
                    cout << "Wild ";
                }
                else
                {
                    cout << "The foe's ";
                }
                cout << enemyPkmn->getNickname() << " was hurt by burn." << endl;
            }
            else if (enemyPkmn->getStatus() == 5)
            {
            // 5 poison
                enemyPkmn->adjustHP((int)(-enemyPkmn->getStats(0)/8.0));

                if (enemyPkmn->isWild())
                {
                    cout << "Wild ";
                }
                else
                {
                    cout << "The foe's ";
                }
                cout << enemyPkmn->getNickname() << " was hurt by poison." << endl;
            }
        }
        // enemy first
        else
        {
            if (enemyPkmn->getStatus() == 2)
            {
            // 2 sleep
                //dec sleepcounter
            }
            else if (enemyPkmn->getStatus() == 4)
            {
                // 4 burn
                enemyPkmn->adjustHP((int)(-enemyPkmn->getStats(0)/8.0));
                if (enemyPkmn->isWild())
                {
                    cout << "Wild ";
                }
                else
                {
                    cout << "The foe's ";
                }
                cout << enemyPkmn->getNickname() << " was hurt by burn." << endl;
            }
            else if (enemyPkmn->getStatus() == 5)
            {
            // 5 poison
                enemyPkmn->adjustHP((int)(-enemyPkmn->getStats(0)/8.0));
                if (enemyPkmn->isWild())
                {
                    cout << "Wild ";
                }
                else
                {
                    cout << "The foe's ";
                }
                cout << enemyPkmn->getNickname() << " was hurt by poison." << endl;
            }


            if (myPkmn->getStatus() == 2)
            {
            // 2 sleep
                //dec sleepcounter
            }
            else if (myPkmn->getStatus() == 4)
            {
                // 4 burn
                myPkmn->adjustHP((int)(-myPkmn->getStats(0)/8.0));
                cout << myPkmn->getNickname() << " was hurt by burn." << endl;
            }
            else if (myPkmn->getStatus() == 5)
            {
            // 5 poison
                myPkmn->adjustHP((int)(-myPkmn->getStats(0)/8.0));
                cout << myPkmn->getNickname() << " was hurt by poison." << endl;
            }
        }
    }

    delay(1750);
}

void PokemonBattle::delay(int ms)
{
    #ifdef WINDOWS_OS
        Sleep(ms);
    #else
        usleep(ms*1000);
    #endif
}