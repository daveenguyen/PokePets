#include <iostream>
#include <iomanip>
#include <cstdlib>

using namespace std;

#include "PokemonBattle.h"

//#define WINDOWS_OS // uncomment if using windows

// #ifdef WINDOWS_OS
//     #include <windows.h>
// #else
//     #include <unistd.h>
// #endif

#define DIVIDER_LENGTH 120


PokemonBattle::PokemonBattle(Pokemon* myPkmn, Pokemon* enemyPkmn, string enemyName):
    myPkmn(myPkmn), enemyPkmn(enemyPkmn), enemyName(enemyName)
{
}

void PokemonBattle::start()
{
    printBattleInit();
    delay(1750);
    while (!_battleDone)
    {
        printCommon();

        switch(_state)
        {
            case -1:
                cout << "You ran away!" << endl;
                cout.flush();
                _battleDone = true;
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
    // for (int i = 0; i < 60; ++i)
    // {
    //     cout << endl;
    // }

    if (!enemyPkmn->isWild())
    {
        cout << "You are challenged by " << enemyName << "!" << endl;
        cout << enemyName << " sent out " << enemyPkmn->getNickname() << '!' << endl;
    }
    else
    {
        cout << "A wild " << enemyPkmn->getNickname() << " appeared!" << endl;
    }

    cout << "Go! " << myPkmn->getNickname() << '!' << endl;

    _state = 0;
    _battleDone = false;
}


void PokemonBattle::printBattleOptions()
{
    cout << "    BATTLE OPTIONS" << endl;
    cout << "----------------------" << endl;
    cout << " 1. Fight" << endl;
    // cout << " 2. PokePets" << endl;
    // cout << " 3. Bag" << endl;
    cout << " 4. Run" << endl;
    cout << "\nWhat will " << myPkmn->getNickname() << " do? ";
    cout << endl;

    int userInput;
    while ( ! (cin >> userInput))
    {
        cout << "Invalid input!  Try again: ";
        cin.clear ();   // reset fail flag

        // skip past invalid input
        cin.ignore (1000, '\n');  // Skip to next newline or 1000 chars
    }


    switch (userInput)
    {
        case 1:
            // fight
            _state = 1;
            break;
        case 2:
            // pokepets
            // _state = 2;
            break;
        case 3:
            // bag
            // _state = 3;
            break;
        case 4:
            // run
            //http://bulbapedia.bulbagarden.net/wiki/Escape
            if (enemyPkmn->isWild())
            {
                _state = -1;
            }
            else
            {
                cout << "You cannot run away from a trainer battle!" << endl;
                cout.flush();
                delay(1750);
            }
            break;
        default:
            break;
    }
}

void PokemonBattle::printCommon()
{
    // clear a bit of screen
    // for (int i = 0; i < 15; ++i)
    // {
    //     cout << endl;
    // }

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

    // print status
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
    cout << "EXP: " << myPkmn->getCurExp() << " / " << myPkmn->getExpToLvl(myPkmn->getLevel()) << endl;
    for(int i = 0; i < DIVIDER_LENGTH; ++i)
    {
        cout << "_";
    }
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
        printTypeColor(pkmn->getMove(i).getType().getTypeNum());
        cout << setw((DIVIDER_LENGTH/4-15)) << pkmn->getMove(i).getType().getIdentifier();
        printTypeColor(0); // reset color
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

    while ( ! (cin >> userInput))
    {
        cout << "Invalid input!  Try again: ";
        cin.clear ();   // reset fail flag

        // skip past invalid input
        cin.ignore (1000, '\n');  // Skip to next newline or 1000 chars
    }

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
    if (myPkmn->getStatus() == 1 && rand()%100 < 25)
    {
        // paralyzed
        cout << C_ELECTRIC;
        cout << myPkmn->getNickname() << " is paralyzed! \nIt can't move!\n";
        cout << C_RESET;
    }
    else if (myPkmn->getStatus() == 2 || myPkmn->getStatus() == 3)
    {
        if (myPkmn->getStatus() == 3)
            cout << C_ICE;
        myPkmn->checkAilment();
        cout << C_RESET;
        if (myPkmn->getStatus() == 0)
            doPlayerMove();
    }
    else if (_playerMove!=-1)
    {
        myPkmn->useMove(_playerMove,enemyPkmn);
    }
    else
    {
        // struggle
        myPkmn->useMove(165, enemyPkmn);
    }
}

void PokemonBattle::doEnemyMove()
{
    if (enemyPkmn->getStatus() == 1 && rand()%100 < 25)
    {
        // paralyzed
        cout << C_ELECTRIC;
        if (enemyPkmn->isWild())
            cout << "Wild ";
        cout << enemyPkmn->getNickname() << " is paralyzed! \nIt can't move!\n";
        cout << C_RESET;
    }
    else if (enemyPkmn->getStatus() == 2 || enemyPkmn->getStatus() == 3)
    {
        if (enemyPkmn->getStatus() == 3)
            cout << C_ICE;
        enemyPkmn->checkAilment();
        cout << C_RESET;
        if (enemyPkmn->getStatus() == 0)
            doEnemyMove();
    }
    else
    {
        int moveCount = 0;
        for (int i = 0; i < 4 && enemyPkmn->getMove(i).getMoveNum() != 0; ++i)
        {
            moveCount++;
        }
        enemyPkmn->useMove(rand()%moveCount,myPkmn);
    }
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

    checkPrintFaint();

    if(!isDead(myPkmn)&&!isDead(enemyPkmn))
    {
        doEndTurn();
        _state = 0;
    }
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
    return (pkmn->getCurHP()<=0);
}

void PokemonBattle::doEndTurn()
{
    if(!isDead(myPkmn) && !isDead(enemyPkmn))
    {
        // check for burn or poison
        if (meFirst())
        {
            if (myPkmn->getStatus() == 4)
            {
                // 4 burn
                myPkmn->adjustHP((int)(-myPkmn->getStats(0)/8.0));
                cout << C_FIRE;
                cout << myPkmn->getNickname() << " was hurt by burn." << endl;
                cout << C_RESET;
            }
            else if (myPkmn->getStatus() == 5)
            {
                // 5 poison
                myPkmn->adjustHP((int)(-myPkmn->getStats(0)/8.0));
                cout << C_POISON;
                cout << myPkmn->getNickname() << " was hurt by poison." << endl;
                cout << C_RESET;
            }

            if (enemyPkmn->getStatus() == 4 && !isDead(myPkmn))
            {
                // 4 burn
                enemyPkmn->adjustHP((int)(-enemyPkmn->getStats(0)/8.0));

                cout << C_FIRE;
                if (enemyPkmn->isWild())
                {
                    cout << "Wild ";
                }
                else
                {
                    cout << enemyName << "'s ";
                }
                cout << enemyPkmn->getNickname() << " was hurt by burn." << endl;
                cout << C_RESET;
            }
            else if (enemyPkmn->getStatus() == 5 && !isDead(myPkmn))
            {
            // 5 poison
                enemyPkmn->adjustHP((int)(-enemyPkmn->getStats(0)/8.0));

                cout << C_POISON;
                if (enemyPkmn->isWild())
                {
                    cout << "Wild ";
                }
                else
                {
                    cout << enemyName << "'s ";
                }
                cout << enemyPkmn->getNickname() << " was hurt by poison." << endl;
                cout << C_RESET;
            }
        }
        // enemy first
        else
        {
            if (enemyPkmn->getStatus() == 4)
            {
                // 4 burn
                enemyPkmn->adjustHP((int)(-enemyPkmn->getStats(0)/8.0));
                cout << C_FIRE;
                if (enemyPkmn->isWild())
                {
                    cout << "Wild ";
                }
                else
                {
                    cout << enemyName << "'s ";
                }
                cout << enemyPkmn->getNickname() << " was hurt by burn." << endl;
                cout << C_RESET;
            }
            else if (enemyPkmn->getStatus() == 5)
            {
            // 5 poison
                enemyPkmn->adjustHP((int)(-enemyPkmn->getStats(0)/8.0));
                cout << C_POISON;
                if (enemyPkmn->isWild())
                {
                    cout << "Wild ";
                }
                else
                {
                    cout << enemyName << "'s ";
                }
                cout << enemyPkmn->getNickname() << " was hurt by poison." << endl;
                cout << C_RESET;
            }


            if (myPkmn->getStatus() == 4 && !isDead(enemyPkmn))
            {
                // 4 burn
                myPkmn->adjustHP((int)(-myPkmn->getStats(0)/8.0));
                cout << C_FIRE;
                cout << myPkmn->getNickname() << " was hurt by burn." << endl;
                cout << C_RESET;
            }
            else if (myPkmn->getStatus() == 5 && !isDead(enemyPkmn))
            {
            // 5 poison
                myPkmn->adjustHP((int)(-myPkmn->getStats(0)/8.0));
                cout << C_POISON;
                cout << myPkmn->getNickname() << " was hurt by poison." << endl;
                cout << C_RESET;
            }
        }
        checkPrintFaint();
    }

    delay(1750);
}

void PokemonBattle::delay(int ms)
{
    char userInput;
    cout << "\n** Input a character to continue ** ";
    if ( ! (cin >> userInput))
    {
        cin.clear ();   // reset fail flag

        // skip past invalid input
        cin.ignore (1000, '\n');  // Skip to next newline or 1000 chars
    }
    cout << endl;
}


void PokemonBattle::printTypeColor(int i)
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

void PokemonBattle::checkPrintFaint()
{
    if (isDead(enemyPkmn))
    {
        // enemy dead
        if (enemyPkmn->isWild())
        {
            cout << "Wild ";
        }
        else
        {
            cout << enemyName << "'s ";
        }
        cout << enemyPkmn->getNickname() << " fainted!" << endl;
        _battleDone = true;

        myPkmn->adjustExperience(enemyPkmn->getBaseExp(), enemyPkmn->getLevel(), enemyPkmn->isWild(), 1);

        myPkmn->adjustEffort(
            enemyPkmn->getEffortYield(0),
            enemyPkmn->getEffortYield(1),
            enemyPkmn->getEffortYield(2),
            enemyPkmn->getEffortYield(3),
            enemyPkmn->getEffortYield(4),
            enemyPkmn->getEffortYield(5)
        );

        delay(1750);
    }
    else if (isDead(myPkmn))
    {
        // you dead
        cout << myPkmn->getNickname() << " fainted!" << endl;
        _battleDone = true;
        delay(1750);
    }
}