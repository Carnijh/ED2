#ifndef NOAVLM_H_INCLUDED
#define NOAVLM_H_INCLUDED
#include <iostream>

class NoAVLM
{
    public:
        NoAVLM()     {}
        ~NoAVLM()    {}
        int info;
        NoAVLM *esq;
        NoAVLM *dir;
        int altura;
};

#endif // NOAVLM_H_INCLUDED
