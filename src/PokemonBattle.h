#ifndef POKEMONBATTLE_H
#define POKEMONBATTLE_H

#include <ctime>
#include <string>

#include "Pokemon.h" // parent class
#include "Nature.h"         // pokemon has a nature

class PokemonBattle
{
    public:

        PokemonBattle(Pokemon* myPkmn, Pokemon* enemyPkmn);
        ~PokemonBattle(){};

        void printBattleInit();
        void printBattleOptions();
        void printCommon();
        void printAttackOptions(Pokemon* pkmn);
        void delay(int ms);
        void printHpBars(Pokemon* pkmn);
        void drawPokemons();
        void printTypeWithColor(int i);
        void checkPP(int move);
        void doPlayerMove();
        void doEnemyMove();
        void doMove();
        void doEndTurn();
        bool meFirst();
        bool isDead(Pokemon* pkmn);

        void startBattle();

    private:
        Pokemon* myPkmn;
        Pokemon* enemyPkmn;
        int _state;
        int _playerMove;


};

#endif // POKEMONBATTLE_H