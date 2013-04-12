#ifndef TYPE_H
#define TYPE_H

#include <string>

class Type
{
    public:

        Type(int typeNum=0);

        ~Type() {};

        void initType(int typeNum);
        int  getEfficacy(int i);

    private:

        string _identifier;
        int    _typeNum;
        int    _efficacy[17];

};

#endif // TYPE_H