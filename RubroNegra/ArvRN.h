#ifndef ArvRN_H_INCLUDED
#define ArvRN_H_INCLUDED

#include <iostream>
#include <cstdlib>
#include "NoRN.h"

class ArvRN
{
    private:
        NoRN *raiz;
    protected:
        void rotacionarEsquerda(NoRN *ptr);
        void rotacionarDireita(NoRN *ptr);
        void balancearInsercao(NoRN *ptr);
        void balancearRemocao(NoRN *N);
        int getCor(NoRN *N);
        void setCor(NoRN *N, int cor);
        NoRN *minValorNoRN(NoRN *N);
        NoRN *maxValorNoRN(NoRN *N);
        NoRN* inserirRN(NoRN *raiz, NoRN *ptr);
        NoRN* removerRN(NoRN *raiz, int info);
        int getAlturaNegra(NoRN *N);
        bool auxBusca(NoRN* p, int C);
    public:
        ArvRN();
        void inserir(int C);
        void remover(int info);
        void imprimir();
        void imprimePorNivel(NoRN* p, int nivel);
        bool busca(int C);
};


#endif // ArvRN_H_INCLUDED
