#include <iostream>
#include <string>

using namespace std;

#include "CSVReader.h"
#include "DBParser.h"
#include "Pokemon.h"
#include "Type.h"
#include "Move.h"

void TestPokemon();
void TestParser();
void TestType();

int main() {
    TestPokemon();
    // TestParser();
    // TestType();
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
    CSVReader reader;
    Pokemon myPokemon(&reader, dexNum, lvl);

    cout << "___ POKEMON INFO" << endl;
    cout << "NICKNAME: " << myPokemon.getNickname() << endl;
    cout << "  GENDER: ";
    // << myPokemon.getGender()   << endl;
    switch (myPokemon.getGender()) {
        case -1:
            cout << "Genderless" << endl;
            break;
        case 0:
            cout << "Male" << endl;
            break;
        case 1:
            cout << "Female" << endl;
            break;
        default:
            cout << "** GENDER ERROR ** " << myPokemon.getGender() << endl;
            break;
    }

    cout << " ABILITY: " << myPokemon.getAbility() << endl;

    cout << "  NATURE: " << myPokemon.getNature() << endl;

    cout << "   LEVEL: " << myPokemon.getLevel()  << endl;
    cout << " CUR EXP: " << myPokemon.getCurExp() << endl;
    cout << "  CUR HP: " << myPokemon.getCurHP()  << endl;
    cout << "  STATUS: " << myPokemon.getStatus() << endl << endl;

    for (int i=0; i < 2 && myPokemon.getTypes(i) != 0; ++i) {
        DBParser type(myPokemon.getTypes(i), 1);
        cout << " TYPE["<< i << "]: " << type.getTypeString() << endl;
    }

    cout << endl;

    for (int i=0; i < 4 && myPokemon.getMoves(i) != 0; ++i) {
        cout << "___ ";
        Move myMove(myPokemon.getMoves(i));
        cout << myMove.getIdentifier() << endl;
        cout << "   POWER: " << myMove.getPower() << endl;
        cout << "      PP: " << myMove.getPP() << endl;
        cout << "Accuracy: " << myMove.getAccuracy() << endl << endl;
    }


    cout << endl;

    cout << "___ STATS" << endl;
    cout << "      HP: " << myPokemon.getStats(0) << endl;
    cout << "     ATK: " << myPokemon.getStats(1) << endl;
    cout << "     DEF: " << myPokemon.getStats(2) << endl;
    cout << "   S.ATK: " << myPokemon.getStats(3) << endl;
    cout << "   S.DEF: " << myPokemon.getStats(4) << endl;
    cout << "   SPEED: " << myPokemon.getStats(5) << endl << endl;

    // cout << "___ IV" << endl;
    // cout << "      HP: " << myPokemon.getIVs(0) << endl;
    // cout << "     ATK: " << myPokemon.getIVs(1) << endl;
    // cout << "     DEF: " << myPokemon.getIVs(2) << endl;
    // cout << "   S.ATK: " << myPokemon.getIVs(3) << endl;
    // cout << "   S.DEF: " << myPokemon.getIVs(4) << endl;
    // cout << "   SPEED: " << myPokemon.getIVs(5) << endl << endl;

    myPokemon.adjustHP(-5);
    cout << "damaged pokemon by 5 points" << endl;
    cout << "   LEVEL: " << myPokemon.getLevel()  << endl;
    cout << " CUR EXP: " << myPokemon.getCurExp() << endl;
    cout << "      HP: " << myPokemon.getCurHP() << " / " << myPokemon.getStats(0) << endl;
    myPokemon.adjustExperience(myPokemon.getBaseExp(), myPokemon.getLevel(), false, 1);
    cout << "   LEVEL: " << myPokemon.getLevel()  << endl;
    cout << " CUR EXP: " << myPokemon.getCurExp() << endl;
    cout << "      HP: " << myPokemon.getCurHP() << " / " << myPokemon.getStats(0) << endl;
    myPokemon.adjustExperience(myPokemon.getBaseExp(), myPokemon.getLevel(), false, 1);
    cout << "   LEVEL: " << myPokemon.getLevel()  << endl;
    cout << " CUR EXP: " << myPokemon.getCurExp() << endl;
    cout << "      HP: " << myPokemon.getCurHP() << " / " << myPokemon.getStats(0) << endl;
    myPokemon.adjustExperience(myPokemon.getBaseExp(), myPokemon.getLevel(), false, 1);
    cout << "   LEVEL: " << myPokemon.getLevel()  << endl;
    cout << " CUR EXP: " << myPokemon.getCurExp() << endl;
    cout << "      HP: " << myPokemon.getCurHP() << " / " << myPokemon.getStats(0) << endl;
    myPokemon.adjustExperience(myPokemon.getBaseExp(), myPokemon.getLevel(), false, 1);
    cout << "   LEVEL: " << myPokemon.getLevel()  << endl;
    cout << " CUR EXP: " << myPokemon.getCurExp() << endl;
    cout << "      HP: " << myPokemon.getCurHP() << " / " << myPokemon.getStats(0) << endl;
    myPokemon.adjustExperience(myPokemon.getBaseExp(), myPokemon.getLevel(), false, 1);
    cout << "   LEVEL: " << myPokemon.getLevel()  << endl;
    cout << " CUR EXP: " << myPokemon.getCurExp() << endl;
    cout << "      HP: " << myPokemon.getCurHP() << " / " << myPokemon.getStats(0) << endl;
    myPokemon.adjustExperience(myPokemon.getBaseExp(), myPokemon.getLevel(), false, 1);
    cout << "   LEVEL: " << myPokemon.getLevel()  << endl;
    cout << " CUR EXP: " << myPokemon.getCurExp() << endl;
    cout << "      HP: " << myPokemon.getCurHP() << " / " << myPokemon.getStats(0) << endl;

}

void TestParser() {

    cout << "Enter num: ";
    int num;
    cin  >> num;
    cout << endl;

    // Move move(num)
    // DBParser db(num,3);
    // cout << db.cur_move._identifier << endl;
    // cout << db.cur_move._power << endl;
    // cout << db.cur_move._pp << endl;
    // cout << db.cur_move._accuracy << endl;

}

void TestType() {
    cout << "Enter num: ";
    int num;
    cin  >> num;
    cout << endl;

    Type type(num);
}