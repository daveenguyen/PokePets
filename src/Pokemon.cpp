#include "Pokemon.h"

Pokemon::Pokemon(Species species) {
    _nickname = species.getName();
    _species  = species.getSpecies();
    _types[0] = species.getType(0);
    _types[1] = species.getType(1);
    _gender   = species.getGenderRatio();
    _ability  = species.getAbilities();
    _level    = 1;
    _nature   = ;
    _stats    = ;
    _IVs      = ;
    _EVs      = ;
    _moves    = ;
    _curHP    = ;
}