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

    t->altura = max(getAltura(t->esq), getAltura(t->dir));
    return t;
}

NoAVL* ArvAVL::rotacionarDireita(NoAVL* &t)
{
    NoAVL* u = t->esq;
    t->esq = u->dir;
    u->dir = t;
    t->altura = max(getAltura(t->esq), getAltura(t->dir));
    u->altura = max(getAltura(u->esq), t->altura);
    return u;
}

NoAVL* ArvAVL::rotacionarEsquerda(NoAVL* &t)
{
    NoAVL* u = t->dir;
    t->dir = u->esq;
    u->esq = t;
    t->altura = max(getAltura(t->esq), getAltura(t->dir));
    u->altura = max(getAltura(t->dir), t->altura);
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
    NoAVL* aux;

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

    // If NoAVL está desbalanceada
    // If nó esquerdo for deletado
    if(getAltura(t->esq) - getAltura(t->dir) == 2)
    {
        if(getAltura(t->esq->esq) - getAltura(t->esq->dir) == 1)
            return rotacionarEsquerda(t);
        else
            return rotacionarDuplaEsquerda(t);
    }
    // If nó direito for deletado
    else if(getAltura(t->dir) - getAltura(t->esq) == 2)
    {
        if(getAltura(t->dir->dir) - getAltura(t->dir->esq) == 1)
            return rotacionarDireita(t);
        else
            return rotacionarDuplaDireita(t);
    }
    return t;
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
