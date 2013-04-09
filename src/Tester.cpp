#include <iostream> // cin / cout

#include "DBParser.h"
#include "Pokemon.h"
#include "Type.h"

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
    Pokemon myPokemon(dexNum, lvl);

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

    cout << "  NATURE: ";
    DBParser nature(myPokemon.getNature(), 2);
    cout << nature.getNatureString() << endl;

    cout << "   LEVEL: " << myPokemon.getLevel()  << endl;
    cout << " CUR EXP: " << myPokemon.getCurExp() << endl;
    cout << "  CUR HP: " << myPokemon.getCurHP()  << endl;
    cout << "  STATUS: " << myPokemon.getStatus() << endl << endl;

    for (int i=0; i < 2 && myPokemon.getTypes(i) != 0; i++) {
        DBParser type(myPokemon.getTypes(i), 1);
        cout << " TYPE["<< i << "]: " << type.getTypeString() << endl;
    }

    cout << endl;

    cout << "___ MOVES" << endl;
    cout << " MOVE[0]: " << myPokemon.getMoves(0) << endl;
    cout << " MOVE[1]: " << myPokemon.getMoves(1) << endl;
    cout << " MOVE[2]: " << myPokemon.getMoves(2) << endl;
    cout << " MOVE[3]: " << myPokemon.getMoves(3) << endl << endl;

    cout << "___ STATS" << endl;
    cout << "      HP: " << myPokemon.getStats(0) << endl;
    cout << "     ATK: " << myPokemon.getStats(1) << endl;
    cout << "     DEF: " << myPokemon.getStats(2) << endl;
    cout << "   S.ATK: " << myPokemon.getStats(3) << endl;
    cout << "   S.DEF: " << myPokemon.getStats(4) << endl;
    cout << "   SPEED: " << myPokemon.getStats(5) << endl << endl;

    cout << "___ IV" << endl;
    cout << "      HP: " << myPokemon.getIVs(0) << endl;
    cout << "     ATK: " << myPokemon.getIVs(1) << endl;
    cout << "     DEF: " << myPokemon.getIVs(2) << endl;
    cout << "   S.ATK: " << myPokemon.getIVs(3) << endl;
    cout << "   S.DEF: " << myPokemon.getIVs(4) << endl;
    cout << "   SPEED: " << myPokemon.getIVs(5) << endl << endl;
}

void TestParser() {

    cout << "Enter num: ";
    int num;
    cin  >> num;
    cout << endl;

    DBParser db();

}

void TestType() {
    cout << "Enter num: ";
    int num;
    cin  >> num;
    cout << endl;

    Type type(num);
}