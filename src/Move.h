#ifndef MOVE_H
#define MOVE_H

#include <string>
using namespace std;

#include "Type.h"

class Move
{
    public:

        Move(int moveNum=0);

        ~Move() {};

        void   initMove();

        // move info
        void    setMoveNum(int moveNum);
        void    setIdentifier(string i);
        void    setType_id(int i);
        void    setPower(int i);
        void    setPP(int i);
        void    setAccuracy(int i);
        void    setPriority(int i);
        void    setTarget_id(int i);
        void    setDamage_class_id(int i);
        void    setEffect_id(int i);
        void    setEffect_chance(int i);

        int     getMoveNum();
        string  getIdentifier();
        int     getType_id();
        int     getPower();
        int     getPP();
        int     getAccuracy();
        int     getPriority();
        int     getTarget_id();
        int     getDamage_class_id();
        int     getEffect_id();
        int     getEffect_chance();

        // move meta info
        void    setMeta_category_id(int i);
        void    setMeta_ailment_id(int i);
        void    setMin_hits(int i);
        void    setMax_hits(int i);
        void    setMin_turns(int i);
        void    setMax_turns(int i);
        void    setRecoil(int i);
        void    setHealing(int i);
        void    setCrit_rate(int i);
        void    setAilment_chance(int i);
        void    setFlinch_chance(int i);
        void    setStat_chance(int i);

        int     getMeta_category_id();
        int     getMeta_ailment_id();
        int     getMin_hits();
        int     getMax_hits();
        int     getMin_turns();
        int     getMax_turns();
        int     getRecoil();
        int     getHealing();
        int     getCrit_rate();
        int     getAilment_chance();
        int     getFlinch_chance();
        int     getStat_chance();

        Type    getType();


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

        Type    _type;
};

#endif // MOVE_H