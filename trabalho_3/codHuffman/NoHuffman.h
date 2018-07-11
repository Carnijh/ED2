#ifndef NOHUFFMAN_H_INCLUDED
#define NOHUFFMAN_H_INCLUDED
#include "NoHuffman.h"

class NoHuffman
{
    public:
       NoHuffman(){};
       ~NoHuffman(){};
       void setEsq(NoHuffman* p)    { esq = p; };
       void setFreq(int val) { freq = val; };
       void setSimb(char novo) {simb = novo;};
       void setDir(NoHuffman* p)    { dir = p; };
       NoHuffman* getEsq()          { return esq; };
       int getFreq()         { return freq; };
       NoHuffman* getDir()          { return dir; };
       char getSimb()        {return simb;};
       int freq;
       int simb;
       NoHuffman* esq;
       NoHuffman* dir;
    private:

};

#endif // NOHUFFMAN_H_INCLUDED
