#ifndef POKEMONBATTLE_H
#define POKEMONBATTLE_H

#include <ctime>
#include <string>

#include "Pokemon.h"
#include "Colors.h"

class PokemonBattle
{
    public:

        PokemonBattle(Pokemon* myPkmn, Pokemon* enemyPkmn);
        ~PokemonBattle(){};

        void start();

    private:
        Pokemon* myPkmn;
        Pokemon* enemyPkmn;
        int  _state;
        int  _playerMove;
        bool _battleDone;
        void printBattleInit();
        void printBattleOptions();
        void printTypeColor(int i);
        void printCommon();
        void printAttackOptions(Pokemon* pkmn);
        void delay(int ms);
        void printHpBars(Pokemon* pkmn);
        void drawPokemons();
        void checkPP(int move);
        void doPlayerMove();
        void doEnemyMove();
        void doMove();
        void doEndTurn();
        bool meFirst();
        bool isDead(Pokemon* pkmn);
        void checkPrintFaint();
};

#endif // POKEMONBATTLE_H