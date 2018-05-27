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

    t->altura = max(getAltura(t->esq), getAltura(t->dir))+1;
    return t;
}

NoAVLM* ArvAVLM::rotacionarDireita(NoAVLM* &t)
{
    NoAVLM* u = t->esq;
    t->esq = u->dir;
    u->dir = t;
    t->altura = max(getAltura(t->esq), getAltura(t->dir))+1;
    u->altura = max(getAltura(u->esq), t->altura)+1;
    return u;
}

NoAVLM* ArvAVLM::rotacionarEsquerda(NoAVLM* &t)
{
    NoAVLM* u = t->dir;
    t->dir = u->esq;
    u->esq = t;
    t->altura = max(getAltura(t->esq), getAltura(t->dir))+1;
    u->altura = max(getAltura(t->dir), t->altura)+1 ;
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
    NoAVLM* temp;

    // Element not found
    if(t == NULL)
        return NULL;

    // Searching for element
    else if(x < t->info)
        t->esq = remover(x, t->esq);
    else if(x > t->info)
        t->dir = remover(x, t->dir);

    // Element found
    // With 2 children
    else if(t->esq && t->dir)
    {
        temp = findMin(t->dir);
        t->info = temp->info;
        t->dir = remover(t->info, t->dir);
    }
    // With one or zero child
    else
    {
        temp = t;
        if(t->esq == NULL)
            t = t->dir;
        else if(t->dir == NULL)
            t = t->esq;
        delete temp;
    }
    if(t == NULL)
        return t;

    t->altura = max(getAltura(t->esq), getAltura(t->dir))+1;

    // If NoAVLM is unbalanced
    // If esq NoAVLM is deleted, dir case
    if(getAltura(t->esq) - getAltura(t->dir) == 4)
    {
        // dir dir case
        if(getAltura(t->esq->esq) - getAltura(t->esq->dir) == 1)
            return rotacionarEsquerda(t);
        // dir esq case
        else
            return rotacionarDuplaEsquerda(t);
    }
    // If dir NoAVLM is deleted, esq case
    else if(getAltura(t->dir) - getAltura(t->esq) == 4)
    {
        // esq esq case
        if(getAltura(t->dir->dir) - getAltura(t->dir->esq) == 1)
            return rotacionarDireita(t);
        // esq dir case
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
