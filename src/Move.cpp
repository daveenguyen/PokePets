#include <string>
#include <iostream>
using namespace std;

#include "DBParser.h"
#include "Move.h"
#include "Pokemon.h"

Move::Move(int moveNum)
{
    _moveNum          = moveNum;
    initMoveFromDB();
}

void Move::initMoveFromDB()
{
    DBParser db(_moveNum, 3);

    _identifier       = db.cur_move._identifier;
    // _type_id          = db.cur_move._type_id;
    setType_id(db.cur_move._type_id);
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
}

// move info

void Move::setMoveNum(int i)
{
    _moveNum = i;
    initMoveFromDB();
}

void Move::setIdentifier(string i)
{
    _identifier = i;
}

void Move::setType_id(int i)
{
    _type_id = i;
    _type.setTypeNum(_type_id);
}

void Move::setPower(int i)
{
    _power = i;
}

void Move::setPP(int i)
{
    _pp = i;
}

void Move::setAccuracy(int i)
{
    _accuracy = i;
}

void Move::setPriority(int i)
{
    _priority = i;
}

void Move::setTarget_id(int i)
{
    _target_id = i;
}

void Move::setDamage_class_id(int i)
{
    _damage_class_id = i;
}

void Move::setEffect_id(int i)
{
    _effect_id = i;
}

void Move::setEffect_chance(int i)
{
    _effect_chance = i;
}




int Move::getMoveNum()
{
    return _moveNum;
}

string Move::getIdentifier()
{
    return _identifier;
}

int Move::getType_id()
{
    return _type_id;
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

int Move::getPriority()
{
    return _priority;
}

int Move::getTarget_id()
{
    return _target_id;
}

int Move::getDamage_class_id()
{
    return _damage_class_id;
}

int Move::getEffect_id()
{
    return _effect_id;
}

int Move::getEffect_chance()
{
    return _effect_chance;
}


// meta move info
int Move::getMeta_category_id()
{
    return _meta_category_id;
}

int Move::getMeta_ailment_id()
{
    return _meta_ailment_id;
}

int Move::getMin_hits()
{
    return _min_hits;
}

int Move::getMax_hits()
{
    return _max_hits;
}

int Move::getMin_turns()
{
    return _min_turns;
}

int Move::getMax_turns()
{
    return _max_turns;
}

int Move::getRecoil()
{
    return _recoil;
}

int Move::getHealing()
{
    return _healing;
}

int Move::getCrit_rate()
{
    return _crit_rate;
}

int Move::getAilment_chance()
{
    return _ailment_chance;
}

int Move::getFlinch_chance()
{
    return _flinch_chance;
}

int Move::getStat_chance()
{
    return _stat_chance;
}

Type Move::getType()
{
    return _type;
}