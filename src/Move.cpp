#include <string>
#include <iostream>
using namespace std;

#include "DBParser.h"
#include "Move.h"

Move::Move(int moveNum)
{
    DBParser db(moveNum, 3);

    _moveNum          = moveNum;
    _identifier       = db.cur_move._identifier;
    _type_id          = db.cur_move._type_id;
    _power            = db.cur_move._power;
    _pp               = db.cur_move._pp;
    _accuracy         = db.cur_move._accuracy;
    _priority         = db.cur_move._priority;
    _target_id        = db.cur_move._target_id;
    _damage_class_id  = db.cur_move._damage_class_id;
    _effect_id        = db.cur_move._effect_id;
    _effect_chance    = db.cur_move._effect_chance;
    _meta_category_id = db.cur_move._meta_category_id;
    _meta_ailment_id  = db.cur_move._meta_ailment_id;
    _min_hits         = db.cur_move._min_hits;
    _max_hits         = db.cur_move._max_hits;
    _min_turns        = db.cur_move._min_turns;
    _max_turns        = db.cur_move._max_turns;
    _recoil           = db.cur_move._recoil;
    _healing          = db.cur_move._healing;
    _crit_rate        = db.cur_move._crit_rate;
    _ailment_chance   = db.cur_move._ailment_chance;
    _flinch_chance    = db.cur_move._flinch_chance;
    _stat_chance      = db.cur_move._stat_chance;

    cout << "_meta_category_id: " << _meta_category_id << endl;
    cout << "_meta_ailment_id : " << _meta_ailment_id << endl;
}


string Move::getIdentifier()
{
    return _identifier;
}

int Move::getPower()
{
    return _power;
}

int Move::getPP()
{
    return _pp;
}

int Move::getAccuracy()
{
    return _accuracy;
}