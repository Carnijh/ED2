#ifndef ARVAVL_H
#define ARVAVL_H
#include "NoAVL.h"
#include<iostream>

using namespace std;

class ArvAVL
{
    NoAVL* raiz;
    NoAVL* inserir(int x, NoAVL* t);
    NoAVL* rotacionarDireita(NoAVL* &t);
    NoAVL* rotacionarEsquerda(NoAVL* &t);
    NoAVL* rotacionarDuplaEsquerda(NoAVL* &t);
    NoAVL* rotacionarDuplaDireita(NoAVL* &t);
    NoAVL* findMin(NoAVL* t);
    NoAVL* findMax(NoAVL* t);
    NoAVL* remover(int x, NoAVL* t);
    int getAltura(NoAVL* t){ return (t == NULL ? 0 : t->altura); }
    bool auxBusca(NoAVL* p, int C);

public:
    ArvAVL() { raiz = NULL; }
    ~ArvAVL(){}
    void inserir(int x) { raiz = inserir(x, raiz); }
    void remover(int x) { raiz = remover(x, raiz); }
    void imprimir();
    void imprimePorNivel(NoAVL* p, int nivel);
    bool busca(int C);
};

#endif // ARVAVL_H
