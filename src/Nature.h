#ifndef NATURE_H
#define NATURE_H

#include <string>

class Nature
{
    public:

        Nature();
        Nature(int natureNum);

        ~Nature() {};

        string toString();
        int    getNatureNum();
        int    getDecStat();
        int    getIncStat();
        void   setNatureNum(int i);
        void   initNature();

    private:

        string _identifier;
        int    _natureNum;
        int    _decreased_stat_id;
        int    _increased_stat_id;

};

#endif // NATURE_H