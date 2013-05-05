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
#include "Bulbasaur.h"
#include "Charmander.h"
#include "Squirtle.h"
#include "PokemonBattle.h"

#define DIVIDER_LENGTH 120

void printDividers();
void gameIntro();
void printDialogue(const string* dialogue, int indexes=1);
void battleTrainer(const string* name, int dexNum, int level, const string* pre, const string* youWin, const string* youLose);
void randomBattle();
void getPokePet();
int  getInputPrompt(const string prompt, int numOptions, const string* options);

void play();
void feed();
void clean();
void drawPetFront(int petNum);
void checkPet();
void quitGame();

void rockPaperScissors();

void PalletTown(int option);
void Route1(int option);
void ViridianCity(int option);
void Route2(int option);
void ViridianForest(int option);
void PewterCity(int option);
void Route3(int option);
void Moon(int option);
void CeruleanCity(int option);
void Route4(int option);
void Route5(int option);
void toVermillion(int option);
void VermillionCity(int option);
void Route6(int option);
void RockTunnel(int option);
void LavendarTown(int option);
void GhostTower(int option);
void Route7(int option);
void ToCeladon(int option);
void CeladonCity(int option);
void Route8(int option);
void FuchsiaCity(int option);
void Route9(int option);
void Route10(int option);
void SaffronCity(int option);
void CinnebarIsland(int option);
void Route11(int option);
void Route12(int option);
void CrystalCave(int option);
void PokePetLeague(int option);

int main()
{
    // initialize game stuff
    srand(time(NULL)); // seeding in main for RNG
    builder.setReader(&reader);

    curLocation  = 0;
    myPokePetNum = 0;
    badgeCount = 0;

    // game starts with the intro dialogue
    gameIntro();
    while (true)
    {
        printDividers();
        cout << "\nCurrent location: " << location[curLocation] << endl;
        int option = 1;

        if (myPokePetNum!=0)
        {
            option = getInputPrompt("What would you like to do?", 7, menuOption);
        }

        switch (option)
        {
            // location independent
            case 2: // play
                play();
                break;
            case 3: // feed
                feed();
                break;
            case 4: // clean
                clean();
                break;
            case 5: // check pet
                checkPet();
                break;
            case 7: // quit
                quitGame();
                break;

            // location dependent
            case 1: // travel
            case 6: // battle
            {
                switch(curLocation)
                {
                    case 0: // Pallet Town
                        PalletTown(option);
                        break;
                    case 1: // Route 1
                        Route1(option);
                        break;
                    case 2: // Viridian City
                        ViridianCity(option);
                        break;
                    case 3: // Route 2
                        Route2(option);
                        break;
                    case 4: // Viridian Forest
                        ViridianForest(option);
                        break;
                    case 5: // Pewter City
                        PewterCity(option);
                        break;
                    case 6: // Route 3
                        Route3(option);
                        break;
                    case 7: // Mt.Moon
                        Moon(option);
                        break;
                    case 8: // Cerulean City
                        CeruleanCity(option);
                        break;
                    case 9: // Route 4
                        Route4(option);
                        break;
                    case 10: // Route 5
                        Route5(option);
                        break;
                    case 11: // Underground Passage to Vermillion
                        toVermillion(option);
                        break;
                    case 12: // Vermillion City
                        VermillionCity(option);
                        break;
                    case 13: // Route 6
                        Route6(option);
                        break;
                    case 14: // Rock Tunnel
                        RockTunnel(option);
                        break;
                    case 15: // Lavendar Town
                        LavendarTown(option);
                        break;
                    case 16: // Ghost Tower
                        GhostTower(option);
                        break;
                    case 17: // Route 7
                        Route7(option);
                        break;
                    case 18: // Underground Passage to Celadon
                        ToCeladon(option);
                        break;
                    case 19: // Celadon City
                        CeladonCity(option);
                        break;
                    case 20: // Route 8
                        Route8(option);
                        break;
                    case 21: // Fuchsia City
                        FuchsiaCity(option);
                        break;
                    case 22: // Route 9
                        Route9(option);
                        break;
                    case 23: // Route 10
                        Route10(option);
                        break;
                    case 24: // Saffron City
                        SaffronCity(option);
                        break;
                    case 25: // Cinnebar Island
                        CinnebarIsland(option);
                        break;
                    case 26: // Route 11
                        Route11(option);
                        break;
                    case 27: // Route 12
                        Route12(option);
                        break;
                    case 28: // Crystal Cave
                        CrystalCave(option);
                        break;
                    case 29: // PokePet League
                        PokePetLeague(option);
                        break;
                    case 30: // Done!
                        break;
                }
                break;
            }
        }


    }
}

void printDialogue(const string* dialogue, int indexes)
{
    for (int i = 0; i < indexes; i++)
    {
        int prevIndex = 0;  // index of previous space or newline
        int curLength = 0;  // the current length of the string
        string curString = *dialogue;

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


        string tmpPrompt = rivalName + " is your rival's name.  Is that correct?";
        if (getInputPrompt(tmpPrompt, 2, yesNo)==1) done = true;

    }while (!done);
    cout << endl;

    printDialogue(&introText[11]);
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
        cout << pokes+1 << ": " << pokeOptions[pokes] << endl;
    }

    myPokePetNum = getInputPrompt("Which PokePet would you like?", 4, pokeOptions);
    if (myPokePetNum==4) myPokePetNum = 0;
    else
    {
        string tmpPrompt = "Would you like to give your " + pokeOptions[myPokePetNum-1] + " a nickname?";


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

        switch (myPokePetNum)
        {
            case 1:
                myPokemon = new Bulbasaur(&builder);
                break;
            case 2:
                myPokemon = new Charmander(&builder);
                break;
            case 3:
                myPokemon = new Squirtle(&builder);
                break;
            default:
                break;
        }

        myPokePetNum = 1 + ((myPokePetNum-1)*3);
        // myPokemon = new Pokemon(myPokePetNum, 5);


        // myPokemon->setDexNum(myPokePetNum);
        // builder.setPokemon(myPokemon);
        // builder.initSpecies();
        // myPokemon->reset();
        myPokemon->setIsWild(false);
        myPokemon->setNickname(petName);
        petName = myPokemon->getNickname();
        // test experience gain, leveling, evolving
        // while(true)
        // {
        //     char x;
        //     myPokemon->adjustExperience(myPokemon->getBaseExp(), myPokemon->getLevel(), myPokemon->isWild(), 1);
        //     cin >> x;
        // }
    }
}

void battleTrainer(const string* name, int dexNum, int level, const string* pre, const string* youWin, const string* youLose)
{
    if (myPokemon->getCurHP()>0)
    {
        Pokemon enemyPkmn(dexNum, level);
        builder.setPokemon(&enemyPkmn);
        builder.initSpecies();

        enemyPkmn.reset();
        enemyPkmn.setIsWild(false);

        if (!(*pre).empty())
        {
            cout << *name << ": ";
            printDialogue(pre);
        }
        PokemonBattle battle(myPokemon, &enemyPkmn, *name);
        battle.start();
        if (myPokemon->getCurHP()>0)
        {
            // win
            if (!(*youWin).empty())
            {
                cout << *name << ": ";
                printDialogue(youWin);
            }
        }
        else
        {
            // lose
            if (!(*youLose).empty())
            {
                cout << *name << ": ";
                printDialogue(youLose);
            }
        }
    }
    else
    {
        cout << myPokemon->getNickname() << " is hungry! Look for food!" << endl;
    }
}

void randomBattle()
{
    if (myPokemon->getCurHP()>0)
    {
        // generate random level from range
        int minLvl = levelRange[curLocation][0];
        int maxLvl = levelRange[curLocation][1];

        // add 1 due to "page counting"
        int numOfLvls = (maxLvl - minLvl + 1);
        int randLvl = rand() % numOfLvls;
        // add lvl offset
        randLvl += minLvl;

        Pokemon enemyPkmn(
            wildPokePet[curLocation][rand()%8],
            randLvl
        );

        builder.setPokemon(&enemyPkmn);
        builder.initSpecies();

        // reset both pokemon
        enemyPkmn.reset();
        myPokemon->reset();

        // start battle
        PokemonBattle battle(myPokemon, &enemyPkmn);
        battle.start();
    }
    else
    {
        cout << myPokemon->getNickname() << " is hungry! Look for food!" << endl;
    }
}



// option is either travel: 1 or battle: 6

void PalletTown(int option)
{
    if (option == 1)
    {
        // travel
        string tempoptions[] = {"Home", "Prof Haney's Lab", "Route 1"};
        int input;
        if (myPokePetNum!=0)
            input = getInputPrompt("Where would you like to go?", 3, tempoptions);
        else
            input = getInputPrompt("Where would you like to go?", 2, tempoptions);

        switch (input)
        {
            case 1:
                // home
                if (myPokePetNum==0)
                {
                    cout << "Mom: " << playerName <<
                        "! Prof Haney's been waiting for you!" << endl;
                }
                else
                {
                    cout << "Mom: You and your PokePet look hungry.  Eat!" << endl;
                    myPokemon->adjustHP(myPokemon->getStats(0)); // feed pokemon
                }
                break;

            case 2:
                // go to lab
                cout << npcName[0] << ": Hello " << playerName << "! Welcome to my Lab!" << endl;
                if (myPokePetNum==0)
                {
                    getPokePet();
                    if (myPokePetNum!=0)
                    {
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

                        // string* name, int dexNum, int level, string* pre, string* youWin, string* youLose
                        battleTrainer(&rivalName, rivalNum, 5, &rivalQuote[0], &rivalQuote[7], &rivalQuote[9]);
                    }
                }
                break;
            case 3:
                curLocation = 1; // route 1
                break;
        }

    }
    else if (option == 6)
    {
        // battle
        cout << "You cannot do that here!" << endl;
    }
}

void Route1(int option)
{
    if (option == 1)
    {
        // travel
        string tempoptions[] = {location[curLocation-1], location[curLocation+1], "Cancel"};

        switch (getInputPrompt("Where would you like to go?", 3, tempoptions))
        {
            case 1:
                // Pallet town
                curLocation--;
                break;

            case 2:
                // Viridian City
                curLocation++;
                break;
        }

    }
    else if (option == 6)
    {
        randomBattle();
    }
}


void ViridianCity(int option)
{
    if (option == 1)
    {
        // travel
        string tempoptions[] = {location[1], location[3], location[4], "Cancel"};

        switch (getInputPrompt("Where would you like to go?", 4, tempoptions))
        {
            case 1:
                // Route 1
                curLocation = 1;
                break;

            case 2:
                // Viridian City
                curLocation = 3;
                break;

            case 3:
                // Viridian City
                curLocation = 4;;
                break;
        }

    }
    else if (option == 6 && badgeCount==7)
    {
        battleTrainer(&gymLeader[7], 34, 54, &viridianCity[4], &viridianCity[6], &winLose[0]);
        if (myPokemon->getCurHP()>0)
        {
            // player won
            badgeCount++;
            cout << " Maybe you can stand up against the ELITE FOUR " << endl;
        }
    }
}

void Route2(int option)
{
     if (option == 1)
    {
        // travel
        string tempoptions[] = {location[2], "Cancel"};

        switch (getInputPrompt("Where would you like to go?", 2, tempoptions))
        {
            case 1:
                // Route 1
                curLocation = 2;
                break;
        }

    }
    else if (option == 6)
    {
        randomBattle();
    }
}

void ViridianForest(int option)
{
    if (option == 1)
    {
        // travel
        string tempoptions[] = {location[2], location[5], "Cancel"};

        switch (getInputPrompt("Where would you like to go?", 3, tempoptions))
        {
            case 1:
                // Viridian City
                curLocation = 2;
                break;

            case 2:
                // Pewter City
                curLocation = 5;
                break;
        }

    }
    else if (option == 6)
    {
        randomBattle();
    }
}

void PewterCity(int option)
{
    if (option == 1)
    {
        // travel
        string tempoptions[] = {location[4], location[6], "Cancel"};

        switch (getInputPrompt("Where would you like to go?", 3, tempoptions))
        {
            case 1:
                // Viridian Forest
                curLocation = 4;
                break;

            case 2:
                // Route 3
                if (badgeCount>=1)
                    curLocation = 6;
                else
                    cout << " You should try fighting the gym leader first  " << endl;
                break;
        }

    }
    else if (option == 6 && badgeCount==0)
    {
        battleTrainer(&gymLeader[0], 95, 12, &pewterCity[0], &pewterCity[4], &winLose[0]);
        if (myPokemon->getCurHP()>0)
        {
            // player won
            badgeCount++;
        }
    }
}

void Route3(int option)
{
     if (option == 1)
    {
        // travel
        string tempoptions[] = {location[5], location[7], "Cancel"};

        switch (getInputPrompt("Where would you like to go?", 3, tempoptions))
        {
            case 1:
                // Pewter City
                curLocation = 5;
                break;

            case 2:
                // Mt. Moon
                curLocation = 7;
                break;
        }
    }
    else if (option == 6)
    {
        randomBattle();
    }
}

void Moon(int option)
{
    if (option == 1)
    {
        // travel
        string tempoptions[] = {location[6], location[8], "Cancel"};

        switch (getInputPrompt("Where would you like to go?", 3, tempoptions))
        {
            case 1:
                // Route 3
                curLocation = 6;
                break;

            case 2:
                // Cerulean City
                curLocation = 8;
                break;
        }
    }
    else if (option == 6)
    {
        randomBattle();
    }
}

void CeruleanCity(int option)
{
    if (option == 1)
    {
        // travel
        string tempoptions[] = {location[7], location[9], location[10], location[24], "Cancel"};

        switch (getInputPrompt("Where would you like to go?", 5, tempoptions))
        {
            case 1:
                // Viridian Forest
                curLocation = 7;
                break;
            case 2:
                // Route 3
                curLocation = 9;
                break;
            case 3:
                // Route 5
                curLocation = 10;
                break;
            case 4:
                //Saffron City
                //need 5 badges to enter
                if (badgeCount>=5)
                    curLocation = 24;
                else
                    cout << " Road is closed " << endl;
                break;
        }

    }
    else if (option == 6 && badgeCount==1)
    {
        battleTrainer(&gymLeader[1], 121, 21, &ceruleanCity[0], &ceruleanCity[2], &winLose[0]);
        if (myPokemon->getCurHP()>0)
        {
            // player won
            badgeCount++;
        }
    }
}

void Route4(int option)
{
     if (option == 1)
    {
        // travel
        string tempoptions[] = {location[8], "Cancel"};

        switch (getInputPrompt("Where would you like to go?", 2, tempoptions))
        {
            case 1:
                // Cerulean City
                curLocation = 8;
                break;
        }

    }
    else if (option == 6)
    {
        randomBattle();
    }
}

void Route5(int option)
{
    if (option == 1)
    {
        // travel
        string tempoptions[] = {location[8], location[11], location[14], "Cancel"};

        switch (getInputPrompt("Where would you like to go?", 4, tempoptions))
        {
            case 1:
                // Cerulean City
                curLocation = 8;
                break;
            case 2:
                // Underground Passage
                curLocation = 11;
                break;
            case 3:
                // Rock Tunnel
                if (badgeCount>=3)
                    curLocation = 14;
                else
                    cout << " Road is blocked " << endl;
                break;
        }
    }
    else if (option == 6)
    {
        randomBattle();
    }
}

void toVermillion(int option)
{
    if (option == 1)
    {
        // travel
        string tempoptions[] = {location[10], location[12], "Cancel"};

        switch (getInputPrompt("Where would you like to go?", 3, tempoptions))
        {
            case 1:
                // Route 5
                curLocation = 10;
                break;
            case 2:
                // Vermillion City
                curLocation = 12;
                break;
        }
    }
    else if (option == 6)
    {
        cout << " You can't do that here " << endl;
    }
}

void VermillionCity(int option)
{
    if (option == 1)
    {
        // travel
        string tempoptions[] = {location[11], location[13], location[24], "Cancel"};

        switch (getInputPrompt("Where would you like to go?", 4, tempoptions))
        {
            case 1:
                // Underground Passage
                curLocation = 11;
                break;
            case 2:
                // Route 6
                curLocation = 13;
                break;
            case 3:
                // Saffron City
                if (badgeCount>=5)
                    curLocation = 24;
                else
                    cout << " Road is closed " << endl;
                break;
        }
    }
    else if (option == 6 && badgeCount==2)
    {
        battleTrainer(&gymLeader[2], 26, 26, &vermillionCity[0], &vermillionCity[4], &winLose[0]);
        if (myPokemon->getCurHP()>0)
        {
            // player won
            badgeCount++;
        }
    }
}

void Route6(int option)
{
    if (option == 1)
    {
        // travel
        string tempoptions[] = {location[12], location[15], location[23], "Cancel"};

        switch (getInputPrompt("Where would you like to go?", 4, tempoptions))
        {
            case 1:
                // Vermillion City
                curLocation = 12;
                break;
            case 2:
                // Lavendar Town
                if (badgeCount>=4)
                    curLocation = 15;
                else
                    cout << " Road is blocked " << endl;
                break;
            case 3:
                // Route 10
                if (badgeCount>=5)
                    curLocation = 23;
                else
                    cout << " Road is blocked " << endl;
                break;
        }
    }
    else if (option == 6)
    {
        randomBattle();
    }
}

void RockTunnel(int option)
{
    if (option == 1)
    {
        // travel
        string tempoptions[] = {location[10], location[15], "Cancel"};

        switch (getInputPrompt("Where would you like to go?", 3, tempoptions))
        {
            case 1:
                // Route 5
                curLocation = 10;
                break;
            case 2:
                // Lavendar Town
                curLocation = 15;
                break;
        }
    }
    else if (option == 6)
    {
        randomBattle();
    }
}

void LavendarTown(int option)
{
    if (option == 1)
    {
        // travel
        string tempoptions[] = {location[14], location[17], location[16], location[13], "Cancel"};

        switch (getInputPrompt("Where would you like to go?", 5, tempoptions))
        {
            case 1:
                // Rock Tunnel
                curLocation = 14;
                break;
            case 2:
                // Route 7
                curLocation = 17;
                break;
            case 3:
                // Ghost Tower
                curLocation = 16;
            case 4:
                // Route 6
                if (badgeCount>=4)
                    curLocation = 13;
                else
                    cout << " Road is blocked " << endl;
                break;
        }
    }
    else if (option == 6)
    {
        cout << " You can't do that here " << endl;
    }
}

void GhostTower(int option)
{
    if (option == 1)
    {
        // travel
        string tempoptions[] = {location[15], "Cancel"};

        switch (getInputPrompt("Where would you like to go?", 2, tempoptions))
        {
            case 1:
                // Lavendar Town
                curLocation = 15;
                break;
        }
    }
    else if (option == 6)
    {
        randomBattle();
    }
}

void Route7(int option)
{
    if (option == 1)
    {
        // travel
        string tempoptions[] = {location[15], location[18], location[24], "Cancel"};

        switch (getInputPrompt("Where would you like to go?", 4, tempoptions))
        {
            case 1:
                // Lavendar Town
                curLocation = 15;
                break;
            case 2:
                // Underground Passage
                curLocation = 18;
                break;
            case 3:
                // Saffron City
                if (badgeCount>=5)
                    curLocation = 24;
                else
                    cout << " Road is blocked " << endl;
                break;
        }
    }
    else if (option == 6)
    {
        randomBattle();
    }
}

void ToCeladon(int option)
{
    if (option == 1)
    {
        // travel
        string tempoptions[] = {location[17], location[19], "Cancel"};

        switch (getInputPrompt("Where would you like to go?", 3, tempoptions))
        {
            case 1:
                // Route 7
                curLocation = 17;
                break;
            case 2:
                // Celadon City
                curLocation = 19;
                break;
        }
    }
    else if (option == 6)
    {
        cout << " You can't do that here " << endl;
    }

}

void CeladonCity(int option)
{
    if (option == 1)
    {
        // travel
        string tempoptions[] = {location[18], location[20], location[24], "Cancel"};

        switch (getInputPrompt("Where would you like to go?", 4, tempoptions))
        {
            case 1:
                // Underground Passage
                curLocation = 18;
                break;
            case 2:
                // Route 8
                if (badgeCount>=4)
                    curLocation = 20;
                else
                    cout << " There's a gym leader in this town! " << endl;
                break;
            case 3:
                // Saffron City
                if (badgeCount>=5)
                    curLocation = 24;
                else
                    cout << " Road is closed " << endl;
                break;
        }
    }
    else if (option == 6 && badgeCount==3)
    {
       battleTrainer(&gymLeader[3], 45, 34, &celadonCity[0], &celadonCity[3], &winLose[0]);
        {
            // player won
            badgeCount++;
        }
    }
}

void Route8(int option)
{
    if (option == 1)
    {
        // travel
        string tempoptions[] = {location[19], location[22], "Cancel"};

        switch (getInputPrompt("Where would you like to go?", 3, tempoptions))
        {
            case 1:
                // Celadon City
                curLocation = 19;
                break;
            case 2:
                // Route 9
                curLocation = 22;
                break;
        }
    }
    else if (option == 6)
    {
        randomBattle();
    }
}

void FuchsiaCity(int option)
{
    if (option == 1)
    {
        // travel
        string tempoptions[] = {location[22], location[23], location[26], "Cancel"};

        switch (getInputPrompt("Where would you like to go?", 4, tempoptions))
        {
            case 1:
                // Route 9
                curLocation = 22;
                break;
            case 2:
                // Route 10
                if (badgeCount>=5)
                    curLocation = 23;
                else
                    cout << " Why don't you challenge the gym leader " << endl;
                break;
            case 3:
                // Route 11
                if (badgeCount>=6)
                    curLocation = 26;
                else
                    cout << " The road to Saffron City is now open! " << endl;
                break;
        }
    }
    else if (option == 6 && badgeCount==4)
    {
        battleTrainer(&gymLeader[4], 49, 40, &fuchsiaCity[0], &fuchsiaCity[3], &winLose[0]);
        if (myPokemon->getCurHP()>0)
        {
            // player won
            badgeCount++;
        }
    }
}

void Route9(int option)
{
    if (option == 1)
    {
        // travel
        string tempoptions[] = {location[20], location[21], "Cancel"};

        switch (getInputPrompt("Where would you like to go?", 3, tempoptions))
        {
            case 1:
                // Route 8
                curLocation = 20;
                break;
            case 2:
                // Fuschia City
                curLocation = 21;
                break;
        }
    }
    else if (option == 6)
    {
        randomBattle();
    }
}

void Route10(int option)
{
    if (option == 1)
    {
        // travel
        string tempoptions[] = {location[21], location[13], "Cancel"};

        switch (getInputPrompt("Where would you like to go?", 3, tempoptions))
        {
            case 1:
                // Fuschia City
                curLocation = 21;
                break;
            case 2:
                // Route 6
                curLocation = 13;
                break;
        }
    }
    else if (option == 6)
    {
        randomBattle();
    }
}

void SaffronCity(int option)
{
    if (option == 1)
    {
        // travel
        string tempoptions[] = {location[19], location[8], location[17], location[12], "Cancel"};

        switch (getInputPrompt("Where would you like to go?", 5, tempoptions))
        {
            case 1:
                // Celadon City
                curLocation = 19;
                break;
            case 2:
                // Cerulean City
                    curLocation = 8;
                break;
            case 3:
                // Route 7
                curLocation = 17;
                break;
            case 4:
                //Vermillion City
                curLocation = 12;
                break;
        }
    }
    else if (option == 6 && badgeCount==5)
    {
        battleTrainer(&gymLeader[5], 65, 46, &saffronCity[1], &saffronCity[5], &winLose[0]);
        if (myPokemon->getCurHP()>0)
        {
            // player won
            badgeCount++;
            cout << " You can go visit Cinnebar Island now! " << endl;
        }
    }
}

void CinnebarIsland(int option)
{
    if (option == 1)
    {
        // travel
        string tempoptions[] = {location[26], location[27], "Cancel"};

        switch (getInputPrompt("Where would you like to go?", 3, tempoptions))
        {
            case 1:
                // Route 11
                curLocation = 26;
                break;
            case 2:
                // Route 12
                if (badgeCount>=8)
                    curLocation = 27;
                else
                    cout << " The PokePet League is that way... I still need to obtain all badges first" << endl;
                break;
        }
    }
    else if (option == 6 && badgeCount==6)
    {
        battleTrainer(&gymLeader[6], 126, 50, &cinnebarIsland[2], &cinnebarIsland[4], &winLose[0]);
        if (myPokemon->getCurHP()>0)
        {
            // player won
            badgeCount++;
            cout << " I heard the gym in Viridian City is open again. " << endl;
        }
    }
}

void Route11(int option)
{
    if (option == 1)
    {
        // travel
        string tempoptions[] = {location[21], location[25], "Cancel"};

        switch (getInputPrompt("Where would you like to go?", 3, tempoptions))
        {
            case 1:
                // Fuschia City
                curLocation = 21;
                break;
            case 2:
                // Cinnebar Island
                curLocation = 25;
                break;
        }
    }
    else if (option == 6)
    {
        randomBattle();
    }
}

void Route12(int option)
{
    if (option == 1)
    {
        // travel
        string tempoptions[] = {location[25], location[28], "Cancel"};

        switch (getInputPrompt("Where would you like to go?", 3, tempoptions))
        {
            case 1:
                // CInnebar Island
                curLocation = 25;
                break;
            case 2:
                // Crystal Cave
                curLocation = 28;
                break;
        }
    }
    else if (option == 6)
    {
        randomBattle();
    }
}

void CrystalCave(int option)
{
    if (option == 1)
    {
        // travel
        string tempoptions[] = {location[27], location[29], "Cancel"};

        switch (getInputPrompt("Where would you like to go?", 3, tempoptions))
        {
            case 1:
                // Route 12
                curLocation = 27;
                break;
            case 2:
                // League
                curLocation = 29;
                break;
        }
    }
    else if (option == 6)
    {
        randomBattle();
    }
}

void PokePetLeague(int option)
{
    if (option == 1)
    {
        // travel
        string tempoptions[] = {location[28], "Cancel"};

        switch (getInputPrompt("Where would you like to go?", 2, tempoptions))
        {
            case 1:
                // Route 11
                curLocation = 28;
                break;
        }
    }
    else if (option == 6 && badgeCount==8)
    {
        battleTrainer(&elitefour[0], 81, 56, &Dale[1], &Dale[3], &winLose[0]);
        if (myPokemon->getCurHP()>0)
        {
            // player won
            battleTrainer(&elitefour[1], 130, 60, &Davee[0], &Davee[1], &winLose[0]);
            if (myPokemon->getCurHP()>0)
            {
                // player won
                battleTrainer(&elitefour[2], 149, 65, &Albert[0], &Albert[3], &winLose[0]);
                if (myPokemon->getCurHP()>0)
                {
                    // player won
                    battleTrainer(&elitefour[1], 94, 67, &Angel[0], &Angel[3], &winLose[0]);
                    if (myPokemon->getCurHP()>0)
                    {
                        // player won
                        cout << " You are now the champion! or...you would have been.. 
                                there is one more trainer left to fight" << endl;

                        battleTrainer(&rivalName, rivalNum, 5, &rivalQuote[6], &rivalQuote[8], &rivalQuote[9]);                            
                        
                        cout << " CONGRADUALTIONS! YOU ARE NOW THE POKEPET CHAMPION! " << endl; 
                    }
                }
            }
        }
    }
}


// location independent actions
void play()
{
    switch(getInputPrompt("What would you like to play?", 4, playMenu))
    {
        case 1:
            // rock paper scissors
            rockPaperScissors();
            break;
        case 2:
            // heads or tails
            //headsTails();
            break;
        case 3:
            // guessing game
            // guessGame();
            break;
    }

}

void rockPaperScissors()
{
    int playerChoice = getInputPrompt("Which one do you pick?",3,rpsMenu) - 1;
    int petChoice = rand()%3;
    cout << myPokemon->getNickname() << " chose " << rpsMenu[petChoice] << "!\n";
    cout << rpsMenu[playerChoice] << " vs " << rpsMenu[petChoice] << endl;
    if (playerChoice == petChoice)
        cout << gameResult[2] << endl; // draw
    else if ((playerChoice == 0 && petChoice == 2)||
             (playerChoice == 1 && petChoice == 0)||
             (playerChoice == 2 && petChoice == 1))
    {
        cout << gameResult[1] << endl; // win
        myPokemon->adjustEffort(0,4,0,0,0,0); // atk
    }
    else
    {
        cout << gameResult[0] << endl; // lose
        myPokemon->adjustEffort(0,0,4,0,0,0); // def
    }
}

void feed()
{
    switch(getInputPrompt("What would you like to feed your pet?", 8, feedMenu))
    {
        case 1:
            // Berries increases DEF
            cout << myPokemon->getNickname() << " ate the berries!" << endl;
            myPokemon->adjustHP((int)(myPokemon->getStats(0)*0.3));
            myPokemon->adjustEffort(0,0,4,0,0,0);
            break;
        case 2:
            // Poffins increases ATK
            cout << myPokemon->getNickname() << " ate the poffins!" << endl;
            myPokemon->adjustHP((int)(myPokemon->getStats(0)*0.3));
            myPokemon->adjustEffort(0,4,0,0,0,0);
            break;
        case 3:
            // Ice Cream increases HP
            cout << myPokemon->getNickname() << " ate the ice cream!" << endl;
            myPokemon->adjustHP((int)(myPokemon->getStats(0)*0.3));
            myPokemon->adjustEffort(4,0,0,0,0,0);
            break;
        case 4:
            // Soda Pop increases SDEF
            cout << myPokemon->getNickname() << " drank the soda pop!" << endl;
            myPokemon->adjustHP((int)(myPokemon->getStats(0)*0.3));
            myPokemon->adjustEffort(0,0,0,0,4,0);
            break;
        case 5:
            // Lemonade increases SATK
            cout << myPokemon->getNickname() << " drank the lemonade!" << endl;
            myPokemon->adjustHP((int)(myPokemon->getStats(0)*0.3));
            myPokemon->adjustEffort(0,0,0,4,0,0);
            break;
        case 6:
            // Water increases SPEED
            cout << myPokemon->getNickname() << " drank the water!" << endl;
            myPokemon->adjustHP((int)(myPokemon->getStats(0)*0.3));
            myPokemon->adjustEffort(0,0,0,0,0,4);
            break;
        case 7:
            // Rare Candy
            cout << myPokemon->getNickname() << " ate the rare candy!" << endl;
            myPokemon->setLevel(myPokemon->getLevel()+1);
            break;
    }
}
void clean()
{
    switch(getInputPrompt("How would you like to clean your pet?", 7, cleanMenu))
    {
        case 1:
            // Antidote Spray
            break;
        case 2:
            // Awakening Spray
            break;
        case 3:
            // Anti-Paralyze Spray
            break;
        case 4:
            // Unburn Spray
            break;
        case 5:
            // Unfreeze Spray
            break;
        case 6:
            // Bath
            break;
    }
}

void drawPetFront(int petNum)
{
    stringstream ss;
    ss << petNum;
    string str = ss.str();

    string filePathStr = "../data/xterm/front/" + str + ".xterm";

    ifstream reader;
    reader.open(filePathStr.c_str());
    for (int i = 0; i < 16; ++i)
    {
        getline(reader,filePathStr);
        cout << filePathStr << endl;
    }

}

void checkPet()
{
    switch(getInputPrompt("What would you like to check?", 3, checkPetMenu))
    {
        case 1:
            // info
            drawPetFront(myPokemon->getDexNum());
            cout << "___ " << myPokemon->getNickname() << "'s' INFO" << endl;\
            cout << "  GENDER: " << myPokemon->getGender() << endl;

            // cout << " ABILITY: " << myPokemon->getAbility() << endl;

            cout << "  NATURE: " << myPokemon->getNature() << endl;

            cout << "   LEVEL: " << myPokemon->getLevel()  << endl;
            cout << " CUR EXP: " << myPokemon->getCurExp() << " / " << myPokemon->getExpToLvl(myPokemon->getLevel()) << endl;
            cout << "  CUR HP: " << myPokemon->getCurHP()  << " / " << myPokemon->getStats(0) << endl;
            // cout << "  STATUS: " << myPokemon->getStatus() << endl;
            cout << " TYPE[0]: " << myPokemon->getType(0).getIdentifier() << endl;
            if (myPokemon->getType(1).getTypeNum() != myPokemon->getType(0).getTypeNum())
                cout << " TYPE[1]: " << myPokemon->getType(1).getIdentifier() << endl;

            cout << endl;
            cout << "      HP: " << myPokemon->getStats(0) << endl;
            cout << "     ATK: " << myPokemon->getStats(1) << endl;
            cout << "     DEF: " << myPokemon->getStats(2) << endl;
            cout << "   S.ATK: " << myPokemon->getStats(3) << endl;
            cout << "   S.DEF: " << myPokemon->getStats(4) << endl;
            cout << "   SPEED: " << myPokemon->getStats(5) << endl << endl;

            // cout << "___ " << myPokemon->getNickname() << "'s MOVES" << endl;
            for (int i=0; i < 4 && myPokemon->getMove(i).getMoveNum() != 0; ++i) {
                cout << "___ ";
                // Move myMove();
                cout << myPokemon->getMove(i).getIdentifier() << endl;
                cout << "    TYPE: " << myPokemon->getMove(i).getType().getIdentifier() << endl;
                cout << "   POWER: " << myPokemon->getMove(i).getPower() << endl;
                cout << "      PP: " << myPokemon->getMove(i).getPP() << endl;
                cout << "Accuracy: " << myPokemon->getMove(i).getAccuracy() << endl << endl;
            }

            break;
        case 2:
            // status
            drawPetFront(myPokemon->getDexNum());
            cout << "___ " << myPokemon->getNickname() << "'s STATUS" << endl;

            // hunger
            int curHP = myPokemon->getCurHP();
            int maxHP = myPokemon->getStats(0);
            double percentHp = 1 - (double(curHP)/maxHP);

            cout << "\nHunger: " << (percentHp*100) << " %" << endl;
            cout << "[" ;

            for (int i = 0; i < 30; ++i)
            {
                if (percentHp > 0)
                    cout << '=';
                else
                    cout << ' ';

                percentHp -= 0.03333333333;
            }
            cout << "]" << endl;

            // growth
            int curEVs =
                myPokemon->getEV(0) +
                myPokemon->getEV(1) +
                myPokemon->getEV(2) +
                myPokemon->getEV(3) +
                myPokemon->getEV(4) +
                myPokemon->getEV(5);
            int maxEVs = 510;
            double percentEv = double(curEVs)/maxEVs;


            cout << "\nGrowth: " << (percentEv*100) << " %" << endl;
            cout << "[" ;

            for (int i = 0; i < 30; ++i)
            {
                if (percentEv > 0)
                    cout << '=';
                else
                    cout << ' ';

                percentEv -= 0.03333333333;
            }
            cout << "]" << endl;


            // condition
            cout << "\nHealth Condition: ";
            switch (myPokemon->getStatus())
            {
                case 0:
                    // Healthy
                    cout << "Healthy\n";
                    break;
                case 1:
                    // Paralysis
                    cout << "Paralyzed\n";
                    break;
                case 2:
                    // Sleep
                    cout << "Sleeping\n";
                    break;
                case 3:
                    // Frozen
                    cout << "Frozen\n";
                    break;
                case 4:
                    // Burn
                    cout << "Burned\n";
                    break;
                case 5:
                    // Poison
                    cout << "Poisoned\n";
                    break;
                default:
                    break;
            }
            break;
    }
}

void quitGame()
{
    // cout << "SAVE CODE"
    exit(1);
}