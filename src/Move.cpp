#include <string>
#include <iostream>
using namespace std;

#include "CSVReader.h"
#include "Move.h"
#include "Pokemon.h"

Move::Move(int moveNum)
{
    _moveNum          = moveNum;
    initMove();
}

void Move::initMove()
{
    int token = 0;

    CSVReader _reader;

// MOVE_NAMES_CSV
    _reader.openFile(MOVE_NAMES_CSV);
    token = 0;

    while (true)
    {
        do
        {
            _reader.readLine();
            _reader.readField();
            token = _reader.getField<int>();
        } while ( token < _moveNum && !_reader.isEof());

        if (token != _moveNum || _reader.isEof())
        {
            break;
        }

        _reader.readField();
        if (_reader.getField<int>() == LANGUAGE_ID)
        {
            _reader.readField();
            // _species->setName(_reader.getField<string>());
            _identifier = _reader.getField<string>();
            break;
        }
    }



// MOVES_CSV
    _reader.openFile(MOVES_CSV);
    token = 0;

    while (true)
    {
        do
        {
            _reader.readLine();
            _reader.readField();
            token = _reader.getField<int>();
        } while ( token < _moveNum && !_reader.isEof());

        if (token != _moveNum || _reader.isEof()) break;

        _reader.readField(); // no need for identifier
        _reader.readField();
        // _moveNum = _reader.getField<int>();
        _reader.readField();
        _type_id = _reader.getField<int>();
        _reader.readField();
        _power = _reader.getField<int>();
        _reader.readField();
        _pp = _reader.getField<int>();
        _reader.readField();
        _accuracy = _reader.getField<int>();
        _reader.readField();
        _priority = _reader.getField<int>();
        _reader.readField();
        _target_id = _reader.getField<int>();
        _reader.readField();
        _damage_class_id = _reader.getField<int>();
        _reader.readField();
        _effect_id = _reader.getField<int>();
        _reader.readField();
        _effect_chance = _reader.getField<int>();
    }



// MOVE_META_CSV
    _reader.openFile(MOVE_META_CSV);
    token = 0;

    while (true)
    {
        do
        {
            _reader.readLine();
            _reader.readField();
            token = _reader.getField<int>();
        } while ( token < _moveNum && !_reader.isEof());

        if (token != _moveNum || _reader.isEof()) break;

        _reader.readField();
        _meta_category_id = _reader.getField<int>();
        _reader.readField();
        _meta_ailment_id = _reader.getField<int>();
        _reader.readField();
        _min_hits = _reader.getField<int>();
        _reader.readField();
        _max_hits = _reader.getField<int>();
        _reader.readField();
        _min_turns = _reader.getField<int>();
        _reader.readField();
        _max_turns = _reader.getField<int>();
        _reader.readField();
        _recoil = _reader.getField<int>();
        _reader.readField();
        _healing = _reader.getField<int>();
        _reader.readField();
        _crit_rate = _reader.getField<int>();
        _reader.readField();
        _ailment_chance = _reader.getField<int>();
        _reader.readField();
        _flinch_chance = _reader.getField<int>();
        _reader.readField();
        _stat_chance = _reader.getField<int>();
    }

    setType_id(_type_id);
}

// move info

void Move::setMoveNum(int i)
{
    _moveNum = i;
    initMove();
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