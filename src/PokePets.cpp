#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <iostream>

using namespace std;


//#define WINDOWS_OS // uncomment if using windows
#ifdef WINDOWS_OS
    #include <windows.h>
#endif

#include "gameDialogue.h"
#include "PokemonBuilder.h"
#include "Pokemon.h"
#include "PokemonBattle.h"

#define DIVIDER_LENGTH 120

void printDividers();
void gameIntro();
void printDialogue(const string* dialogue, int indexes=1);
void printPalletTown();
void battleRival();
void randomBattle();
void printRoute1();
void getPokePet();
int  getInputPrompt(const string prompt, int numOptions, const string* options);


int main()
{
    // initialize game stuff
    builder.setReader(&reader);

    curLocation  = 0;
    myPokePetNum = 0;

    // game starts with the intro dialogue
    gameIntro();
    while (true)
    {
        switch(curLocation)
        {
            case 0:
                printPalletTown();
                break;
            case 1:
                printRoute1();

        }
    }

    // then when you can actually do actions
    // you go choose your starter
    // and then battle your rival
    // then from there on you go get badge
}

void printDialogue(const string* dialogue, int indexes)
{
    for (int i = 0; i < indexes; i++)
    {
        int prevIndex = 0;  // index of previous space or newline
        int curLength = 0;  // the current length of the string
        string curString = *dialogue;
        // curString

        //http://stackoverflow.com/questions/4643512/replace-substring-with-another-substring-c
        size_t index = 0;

        // replace *playerName* name
        while (true) {
             /* Locate the substring to replace. */
             index = curString.find("*playerName*", index);
             if (index == string::npos) break;
             /* Make the replacement. */
             curString.replace(index, 12, playerName);
        }
        index = 0;

        // replace *rivalName* name
        while (true) {
             /* Locate the substring to replace. */
             index = curString.find("*rivalName*", index);
             if (index == string::npos) break;
             /* Make the replacement. */
             curString.replace(index, 11, rivalName);
        }


        index = 0;
        // replace *his/her*
        while (true) {
             /* Locate the substring to replace. */
             index = curString.find("*his/her*", index);
             if (index == string::npos) break;
             /* Make the replacement. */
             if (isBoy)
                 curString.replace(index, 9, "his");
             else
                 curString.replace(index, 9, "her");
        }

        index = 0;
        // replace *he/she*
        while (true) {
             /* Locate the substring to replace. */
             index = curString.find("*he/she*", index);
             if (index == string::npos) break;
             /* Make the replacement. */
             if (isBoy)
                 curString.replace(index, 8, "she");
             else
                 curString.replace(index, 8, "he");
        }

        for(int j = 0; j < curString.length(); ++j)
        {
            ++curLength;

            if (j >=  curString.length()-1)
            {
                for (int startIndex = j-curLength; startIndex <= j; startIndex++)
                {
                    while (startIndex<0) ++startIndex;
                    cout << curString[startIndex];
                }
                cout << endl;
            }
            else if (curString[j]=='\n')
            {
                for (int startIndex = j-curLength; startIndex <= j; startIndex++)
                {
                    cout << endl << startIndex << ": ";
                    cout << curString[startIndex];
                }
                prevIndex = j+1;
                curLength = 0;
            }
            else if (curString[j]==' ')
            {
                if (curLength > DIVIDER_LENGTH)
                {
                    for (int startIndex = j-curLength; startIndex < prevIndex; startIndex++)
                    {
                        cout << curString[startIndex];
                    }
                    cout << endl;
                    j = prevIndex+1;
                    curLength = 0;
                }
                else if(curLength == DIVIDER_LENGTH)
                {
                    for (int startIndex = j-curLength; startIndex < j; startIndex++)
                    {
                        cout << curString[startIndex];
                    }
                    cout << endl;
                    prevIndex = j+1;
                    curLength = 0;
                }
                else if (curLength < DIVIDER_LENGTH)
                {
                    prevIndex = j;
                }
            }
        }
        ++dialogue;
    }
}

void printDividers()
{
    for(int i = 0; i < DIVIDER_LENGTH; ++i)
    {
        cout << '-';
    }
    cout << endl;
}

void gameIntro()
{
    printDividers();

    printDialogue(&introText[0],6);

    bool done = false;

    do
    {
        cout << "\n\tPlease enter your name: ";
        getline(cin, playerName);

        string tmpPrompt = playerName + " is your name. Is that correct?";
        if (getInputPrompt(tmpPrompt, 2, yesNo)==1) done = true;
    }while (!done);
    done = false;
    do
    {
        string tmpMenu[] = {"Boy","Girl"};

        if (getInputPrompt(introText[6], 2, tmpMenu) == 1)
            isBoy = true;
        else
            isBoy = false;

        string tmpPrompt = "You are a ";
        tmpPrompt += ((isBoy)?"boy":"girl");
        tmpPrompt += ". Is that correct?";
        if (getInputPrompt(tmpPrompt, 2, yesNo)==1) done = true;
    }while (!done);


    printDialogue(&introText[7],4);


    done = false;

    do
    {
        cout << "\n\tPlease enter your rival's name: ";
        getline(cin, rivalName);


        string tmpPrompt = rivalName;
        tmpPrompt += " is your rival's name.  Is that correct?";
        if (getInputPrompt(tmpPrompt, 2, yesNo)==1) done = true;

    }while (!done);
    cout << endl;

    printDialogue(&introText[11]);
    printDividers();
}

int getInputPrompt(const string prompt, int numOptions, const string* options)
{
    int userInput = 0;

    cout << "\n\t" << prompt << endl;

    for (int i = 0; i < numOptions; ++i)
    {
        cout << "\t" << i+1 << ": " << options[i] << endl;
    }
    cout << "\tPlease enter a number: ";


    while ( !(cin >> userInput) || userInput < 1 || userInput > numOptions || cin.get() != '\n' )
    {
        cout << "\tInvalid input!  Try again: ";
        cin.clear ();   // reset fail flag

        // skip past invalid input
        cin.ignore (1000, '\n');  // Skip to next newline or 1000 chars
    }
    cout << endl;

    return userInput;
}

void printPalletTown()
{
    while (curLocation == 0)
    {
        cout << "Welcome to " << location[curLocation] << endl;
        string locActions[] = {"Visit Home", "Visit ", "Visit Prof Haney's Lab", "Go to Route 1"};
        locActions[1] += rivalName;
        locActions[1] += "'s home";

        switch (getInputPrompt("What would you like to do?", 4, locActions))
        {
            case 1:
            // visit home
                break;
            case 2:
            // visit rival's home
                break;
            case 3:
            {

            // visit prof haney's lab
                // get pokepet
                cout << npcName[0] << ": Hello " << playerName << "! Welcome to my Lab!" << endl;
                if (myPokePetNum==0)
                {
                    getPokePet();
                    if (myPokePetNum!=0)
                        battleRival();
                }
                break;
            }
            case 4:
            {

            // go to route 1
                if (myPokePetNum != 0)
                {
                    cout << "Travelling to Route 1!" << endl;
                    curLocation = 1;
                }
                else
                {
                    cout << "You need a PokePet to go here.  Try visiting Prof Haney's Lab." << endl;
                }
                break;
            }
            default:
                break;
        }
    }
}

void getPokePet()
{
    string pokeOptions[] = {"Bulbasaur","Charmander","Squirtle","I don't want to choose one right now"};

    for (int pokes = 0; pokes < 3; ++pokes)
    {
        int frontNum = 1+pokes*3;
        stringstream ss;
        ss << frontNum;
        string str = ss.str();

        string filePathStr = "../data/xterm/front/" + str + ".xterm";

        ifstream reader;
        reader.open(filePathStr.c_str());
        for (int i = 0; i < 16; ++i)
        {
            getline(reader,filePathStr);
            cout << filePathStr << endl;
        }
        cout << pokes+1 << endl;
    }

    myPokePetNum = getInputPrompt("Which PokePet would you like?", 4, pokeOptions);
    if (myPokePetNum==4) myPokePetNum = 0;
    else
    {
        string tmpPrompt = "Would you like to give your ";
        tmpPrompt += pokeOptions[myPokePetNum-1];
        tmpPrompt += " a nickname?";


        if (getInputPrompt(tmpPrompt, 2, yesNo)==1)
        {
            bool done = false;
            do
            {
                cout << "\n\tPlease enter a nickname: ";
                getline(cin, petName);

                string tmpPrompt = petName + " is your " + pokeOptions[myPokePetNum-1] + "'s nickname. Is that correct?";
                if ((getInputPrompt(tmpPrompt, 2, yesNo))==1) done = true;
            }while (!done);

        }

        myPokePetNum = 1 + ((myPokePetNum-1)*3);
        // myPokemon = new Pokemon(myPokePetNum, 5);
        myPokemon.setDexNum(myPokePetNum);
        builder.setPokemon(&myPokemon);
        builder.initSpecies();
        myPokemon.reset();
        myPokemon.setIsWild(false);
        myPokemon.setNickname(petName);
    }
}

void battleRival()
{
    int rivalNum = 0;
    if (myPokePetNum==1)
    {
        rivalNum = 4;
    }
    else if (myPokePetNum == 4)
    {
        rivalNum = 7;
    }
    else if (myPokePetNum == 7)
    {
        rivalNum = 1;
    }

    Pokemon enemyPkmn(rivalNum, 5);
    builder.setPokemon(&enemyPkmn);
    builder.initSpecies();

    enemyPkmn.reset();
    enemyPkmn.setIsWild(false);

    PokemonBattle battle(&myPokemon, &enemyPkmn, rivalName);
    battle.start();
}

void printRoute1()
{
    while (curLocation == 1)
    {
        cout << "You're in " << route[0] << endl;
        cout << "You're stuck here forever!" << endl;
        randomBattle();
        // cout << "Welcome to " << location[curLocation] << endl;
        // string locActions[] = {"Visit Home", "Visit ", "Visit Prof Haney's Lab", "Go to Route 1"};
        // locActions[1] += rivalName;
        // locActions[1] += "'s home";

        // switch (getInputPrompt("What would you like to do?", 4, locActions))
        // {
        //     case 1:
        //         break;
        //     default:
        //         break;
        // }
    }
}

void randomBattle()
{
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