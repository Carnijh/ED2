#ifndef ARVAVLM_H
#define ARVAVLM_H
#include "NoAVLM.h"
#include <iostream>

class ArvAVLM
{
    NoAVLM* raiz;
    NoAVLM* inserir(int x, NoAVLM* t);
    NoAVLM* rotacionarDireita(NoAVLM* &t);
    NoAVLM* rotacionarEsquerda(NoAVLM* &t);
    NoAVLM* rotacionarDuplaEsquerda(NoAVLM* &t);
    NoAVLM* rotacionarDuplaDireita(NoAVLM* &t);
    NoAVLM* findMin(NoAVLM* t);
    NoAVLM* findMax(NoAVLM* t);
    NoAVLM* remover(int x, NoAVLM* t);
    int getAltura(NoAVLM* t){ return (t == NULL ? -1 : t->altura); }
    bool auxBusca(NoAVLM* p, int C);

public:
    ArvAVLM() { raiz = NULL; }
    void inserir(int x) { raiz = inserir(x, raiz); }
    void remover(int x) { raiz = remover(x, raiz); }
    void imprimir();
    void imprimePorNivel(NoAVLM* p, int nivel);
    bool busca(int C);
};

#endif // ARVAVLM_H
