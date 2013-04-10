#ifndef MOVE_H
#define MOVE_H

#include <string>
using namespace std;

class Move
{
    public:

        Move(int moveNum=0);

        ~Move() {};

        string getIdentifier();
        int    getPower();
        int    getPP();
        int    getAccuracy();

    private:

        // move info
        string  _identifier;
        int     _moveNum;
        int     _type_id;
        int     _power;
        int     _pp;
        int     _accuracy;
        int     _priority;
        int     _target_id;
        int     _damage_class_id;
        int     _effect_id;
        int     _effect_chance;

        // move meta info
        int     _meta_category_id;
        int     _meta_ailment_id;
        int     _min_hits;
        int     _max_hits;
        int     _min_turns;
        int     _max_turns;
        int     _recoil;
        int     _healing;
        int     _crit_rate;
        int     _ailment_chance;
        int     _flinch_chance;
        int     _stat_chance;
};

#endif // MOVE_H