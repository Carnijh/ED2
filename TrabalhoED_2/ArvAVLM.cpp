#include "ArvAVLM.h"
#include<iostream>

using namespace std;

NoAVLM* ArvAVLM::inserir(int x, NoAVLM* t)
{
    if(t == NULL)
    {
        t = new NoAVLM();
        t->info = x;
        t->altura = 0;
        t->esq = t->dir = NULL;
    }
    else if(x < t->info)
    {
        t->esq = inserir(x, t->esq);
        if(getAltura(t->esq) - getAltura(t->dir) == 4)
        {
            if(x < t->esq->info)
                t = rotacionarDireita(t);
            else
                t = rotacionarDuplaDireita(t);
        }
    }
    else if(x > t->info)
    {
        t->dir = inserir(x, t->dir);
        if(getAltura(t->dir) - getAltura(t->esq) == 4)
        {
            if(x > t->dir->info)
                t = rotacionarEsquerda(t);
            else
                t = rotacionarDuplaEsquerda(t);
        }
    }

    t->altura = max(getAltura(t->esq), getAltura(t->dir));
    return t;
}

NoAVLM* ArvAVLM::rotacionarDireita(NoAVLM* &t)
{
    NoAVLM* u = t->esq;
    t->esq = u->dir;
    u->dir = t;
    t->altura = max(getAltura(t->esq), getAltura(t->dir));
    u->altura = max(getAltura(u->esq), t->altura);
    return u;
}

NoAVLM* ArvAVLM::rotacionarEsquerda(NoAVLM* &t)
{
    NoAVLM* u = t->dir;
    t->dir = u->esq;
    u->esq = t;
    t->altura = max(getAltura(t->esq), getAltura(t->dir));
    u->altura = max(getAltura(t->dir), t->altura);
    return u;
}

NoAVLM* ArvAVLM::rotacionarDuplaEsquerda(NoAVLM* &t)
{
    t->dir = rotacionarDireita(t->dir);
    return rotacionarEsquerda(t);
}

NoAVLM* ArvAVLM::rotacionarDuplaDireita(NoAVLM* &t)
{
    t->esq = rotacionarEsquerda(t->esq);
    return rotacionarDireita(t);
}

NoAVLM* ArvAVLM::findMin(NoAVLM* t)
{
    if(t == NULL)
        return NULL;
    else if(t->esq == NULL)
        return t;
    else
        return findMin(t->esq);
}

NoAVLM* ArvAVLM::findMax(NoAVLM* t)
{
    if(t == NULL)
        return NULL;
    else if(t->dir == NULL)
        return t;
    else
        return findMax(t->dir);
}

NoAVLM* ArvAVLM::remover(int x, NoAVLM* t)
{
    NoAVLM* aux;

    if(t == NULL)
        return NULL;
    // Procurando elemento
    else if(x < t->info)
        t->esq = remover(x, t->esq);
    else if(x > t->info)
        t->dir = remover(x, t->dir);
    // Elemento com 2 filhos
    else if(t->esq && t->dir)
    {
        aux = findMin(t->dir);
        t->info = aux->info;
        t->dir = remover(t->info, t->dir);
    }
    // Elemento com 1 ou 0 filhos
    else
    {
        aux = t;
        if(t->esq == NULL)
            t = t->dir;
        else if(t->dir == NULL)
            t = t->esq;
        delete aux;
    }
    if(t == NULL)
        return t;

    t->altura = max(getAltura(t->esq), getAltura(t->dir));

    // If NoAVLM está desbalanceada
    // If nó esquerdo for deletado
    if(getAltura(t->esq) - getAltura(t->dir) == 4)
    {
        if(getAltura(t->esq->esq) - getAltura(t->esq->dir) == 1)
            return rotacionarEsquerda(t);
        else
            return rotacionarDuplaEsquerda(t);
    }
    // If nó direito for deletado
    else if(getAltura(t->dir) - getAltura(t->esq) == 4)
    {
        if(getAltura(t->dir->dir) - getAltura(t->dir->esq) == 1)
            return rotacionarDireita(t);
        else
            return rotacionarDuplaDireita(t);
    }
    return t;
}

bool ArvAVLM::busca(int C)
{
    return auxBusca(raiz, C);
}

bool ArvAVLM::auxBusca(NoAVLM* p, int C)
{
    if(p == NULL)
        return false;
    else if(p->info == C)
        return true;
    else if(C < p->info)
        return auxBusca(p->esq, C);
    else
        return auxBusca(p->dir, C);
}

void ArvAVLM::imprimir()
{
    imprimePorNivel(raiz, 0);
}

void ArvAVLM::imprimePorNivel(NoAVLM* p, int nivel)
{
    if (p != NULL)
    {
        cout << "(" << nivel << ")";
        for(int i = 1; i <= nivel; i++)
            cout << "--";
        cout << p->info << endl;
        imprimePorNivel(p->esq, nivel+1);
        imprimePorNivel(p->dir, nivel+1);
    }
}
