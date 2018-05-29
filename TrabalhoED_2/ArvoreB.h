#ifndef ARVOREB_H
#define ARVOREB_H
#include "Nob.h"
#include <iostream>

using namespace std;

class ArvoreB
{
    public:
        ArvoreB(int tamanho);
        ~ArvoreB();
        void imprimir();
        void imprimirAux(NoB* no);
        void inserir(int chave);
        void remover(int chave);
        NoB * busca(int chave);
        NoB * getRaiz(){return raiz;}

    private:
        NoB * raiz;
        int d;
        void split(NoB * no);
        void deletarArvore(NoB* no);
};

#endif // ARVOREB_H
