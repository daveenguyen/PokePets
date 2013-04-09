#ifndef NATURE_H
#define NATURE_H

#include <string>

class Nature
{
    public:

        Nature(int natureNum);

        ~Nature() {};

    private:

        string _identifier;
        int    _natureNum;
        int    _decreased_stat_id;
        int    _increased_stat_id;

};

#endif // NATURE_H