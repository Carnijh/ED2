#include "ArvAVL.h"
#include<iostream>

using namespace std;

NoAVL* ArvAVL::inserir(int x, NoAVL* t)
{
    if(t == NULL)
    {
        t = new NoAVL();
        t->info = x;
        t->altura = 0;
        t->esq = t->dir = NULL;
    }
    else if(x < t->info)
    {
        t->esq = inserir(x, t->esq);
        if(getAltura(t->esq) - getAltura(t->dir) == 2)
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
        if(getAltura(t->dir) - getAltura(t->esq) == 2)
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

NoAVL* ArvAVL::rotacionarDireita(NoAVL* &t)
{
    NoAVL* u = t->esq;
    t->esq = u->dir;
    u->dir = t;
    t->altura = max(getAltura(t->esq), getAltura(t->dir))+1;
    u->altura = max(getAltura(u->esq), t->altura)+1;
    return u;
}

NoAVL* ArvAVL::rotacionarEsquerda(NoAVL* &t)
{
    NoAVL* u = t->dir;
    t->dir = u->esq;
    u->esq = t;
    t->altura = max(getAltura(t->esq), getAltura(t->dir))+1;
    u->altura = max(getAltura(t->dir), t->altura)+1 ;
    return u;
}

NoAVL* ArvAVL::rotacionarDuplaEsquerda(NoAVL* &t)
{
    t->dir = rotacionarDireita(t->dir);
    return rotacionarEsquerda(t);
}

NoAVL* ArvAVL::rotacionarDuplaDireita(NoAVL* &t)
{
    t->esq = rotacionarEsquerda(t->esq);
    return rotacionarDireita(t);
}

NoAVL* ArvAVL::findMin(NoAVL* t)
{
    if(t == NULL)
        return NULL;
    else if(t->esq == NULL)
        return t;
    else
        return findMin(t->esq);
}

NoAVL* ArvAVL::findMax(NoAVL* t)
{
    if(t == NULL)
        return NULL;
    else if(t->dir == NULL)
        return t;
    else
        return findMax(t->dir);
}

NoAVL* ArvAVL::remover(int x, NoAVL* t)
{
    NoAVL* temp;

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

    // If NoAVL is unbalanced
    // If esq NoAVL is deleted, dir case
    if(getAltura(t->esq) - getAltura(t->dir) == 2)
    {
        // dir dir case
        if(getAltura(t->esq->esq) - getAltura(t->esq->dir) == 1)
            return rotacionarEsquerda(t);
        // dir esq case
        else
            return rotacionarDuplaEsquerda(t);
    }
    // If dir NoAVL is deleted, esq case
    else if(getAltura(t->dir) - getAltura(t->esq) == 2)
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

int ArvAVL::getBalance(NoAVL* t)
{
    if(t == NULL)
        return 0;
    else
        return getAltura(t->esq) - getAltura(t->dir);
}

bool ArvAVL::busca(int C)
{
    return auxBusca(raiz, C);
}

bool ArvAVL::auxBusca(NoAVL* p, int C)
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

void ArvAVL::imprimir()
{
    imprimePorNivel(raiz, 0);
}

void ArvAVL::imprimePorNivel(NoAVL* p, int nivel)
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
