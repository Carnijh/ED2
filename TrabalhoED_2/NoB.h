#ifndef NOB_H
#define NOB_H
#include <iostream>

using namespace std;

class NoB
{
    public:
        NoB(){};
        NoB(int tamanho, bool f);
        ~NoB();
        int getPosicao(int chave);
        void insere(int chave);
        void remover(int chave);
        NoB * getPai(NoB* no, NoB* raiz);
        int * info;
        NoB ** filho;
        bool folha;
        int d;
        int numchaves;
};

#endif // NOB_H
