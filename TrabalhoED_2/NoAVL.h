#ifndef NOAVL_H_INCLUDED
#define NOAVL_H_INCLUDED
#include <iostream>

class NoAVL
{
    public:
        NoAVL()     {}
        ~NoAVL()    {}
        int info;
        NoAVL *esq;
        NoAVL *dir;
        int altura;
};

#endif // NOAVL_H_INCLUDED
