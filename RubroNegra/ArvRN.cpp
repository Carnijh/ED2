#include <bits/stdc++.h>
#include "ArvRN.h"

using namespace std;

ArvRN::ArvRN() {
    raiz = NULL;
}

int ArvRN::getCor(NoRN *N) {
    if (N == NULL)
        return false;

    return N->cor;
}

void ArvRN::setCor(NoRN *N, int cor) {
    if (N == NULL)
        return;

    N->cor = cor;
}

NoRN* ArvRN::inserirRN(NoRN *raiz, NoRN *ptr) {
    if (raiz == NULL)
        return ptr;

    if (ptr->info < raiz->info) {
        raiz->esq = inserirRN(raiz->esq, ptr);
        raiz->esq->pai = raiz;
    } else if (ptr->info > raiz->info) {
        raiz->dir = inserirRN(raiz->dir, ptr);
        raiz->dir->pai = raiz;
    }

    return raiz;
}

void ArvRN::inserir(int C) {
    NoRN *N = new NoRN(C);
    raiz = inserirRN(raiz, N);
    balancearInsercao(N);
}

void ArvRN::rotacionarEsquerda(NoRN *ptr) {
    NoRN *dir_filho = ptr->dir;
    ptr->dir = dir_filho->esq;

    if (ptr->dir != NULL)
        ptr->dir->pai = ptr;

    dir_filho->pai = ptr->pai;

    if (ptr->pai == NULL)
        raiz = dir_filho;
    else if (ptr == ptr->pai->esq)
        ptr->pai->esq = dir_filho;
    else
        ptr->pai->dir = dir_filho;

    dir_filho->esq = ptr;
    ptr->pai = dir_filho;
}

void ArvRN::rotacionarDireita(NoRN *ptr) {
    NoRN *esq_filho = ptr->esq;
    ptr->esq = esq_filho->dir;

    if (ptr->esq != NULL)
        ptr->esq->pai = ptr;

    esq_filho->pai = ptr->pai;

    if (ptr->pai == NULL)
        raiz = esq_filho;
    else if (ptr == ptr->pai->esq)
        ptr->pai->esq = esq_filho;
    else
        ptr->pai->dir = esq_filho;

    esq_filho->dir = ptr;
    ptr->pai = esq_filho;
}

void ArvRN::balancearInsercao(NoRN *ptr) {
    NoRN *pai = NULL;
    NoRN *avo = NULL;
    while (ptr != raiz && getCor(ptr) == true && getCor(ptr->pai) == true) {
        pai = ptr->pai;
        avo = pai->pai;
        if (pai == avo->esq) {
            NoRN *tio = avo->dir;
            if (getCor(tio) == true) {
                setCor(tio, false);
                setCor(pai, false);
                setCor(avo, true);
                ptr = avo;
            } else {
                if (ptr == pai->dir) {
                    rotacionarEsquerda(pai);
                    ptr = pai;
                    pai = ptr->pai;
                }
                rotacionarDireita(avo);
                swap(pai->cor, avo->cor);
                ptr = pai;
            }
        } else {
            NoRN *tio = avo->esq;
            if (getCor(tio) == true) {
                setCor(tio, false);
                setCor(pai, false);
                setCor(avo, true);
                ptr = avo;
            } else {
                if (ptr == pai->esq) {
                    rotacionarDireita(pai);
                    ptr = pai;
                    pai = ptr->pai;
                }
                rotacionarEsquerda(avo);
                swap(pai->cor, avo->cor);
                ptr = pai;
            }
        }
    }
    setCor(raiz, false);
}

void ArvRN::balancearRemocao(NoRN *N) {
    if (N == NULL)
        return;

    if (N == raiz) {
        raiz = NULL;
        return;
    }

    if (getCor(N) == true || getCor(N->esq) == true || getCor(N->dir) == true) {
        NoRN *filho = N->esq != NULL ? N->esq : N->dir;

        if (N == N->pai->esq) {
            N->pai->esq = filho;
            if (filho != NULL)
                filho->pai = N->pai;
            setCor(filho, false);
            delete (N);
        } else {
            N->pai->dir = filho;
            if (filho != NULL)
                filho->pai = N->pai;
            setCor(filho, false);
            delete (N);
        }
    } else {
        NoRN *irmao = NULL;
        NoRN *pai = NULL;
        NoRN *ptr = N;
        setCor(ptr, DOUBLE_BLACK);
        while (ptr != raiz && getCor(ptr) == DOUBLE_BLACK) {
            pai = ptr->pai;
            if (ptr == pai->esq) {
                irmao = pai->dir;
                if (getCor(irmao) == true) {
                    setCor(irmao, false);
                    setCor(pai, true);
                    rotacionarEsquerda(pai);
                } else {
                    if (getCor(irmao->esq) == false && getCor(irmao->dir) == false) {
                        setCor(irmao, true);
                        if(getCor(pai) == true)
                            setCor(pai, false);
                        else
                            setCor(pai, DOUBLE_BLACK);
                        ptr = pai;
                    } else {
                        if (getCor(irmao->dir) == false) {
                            setCor(irmao->esq, false);
                            setCor(irmao, true);
                            rotacionarDireita(irmao);
                            irmao = pai->dir;
                        }
                        setCor(irmao, pai->cor);
                        setCor(pai, false);
                        setCor(irmao->dir, false);
                        rotacionarEsquerda(pai);
                        break;
                    }
                }
            } else {
                irmao = pai->esq;
                if (getCor(irmao) == true) {
                    setCor(irmao, false);
                    setCor(pai, true);
                    rotacionarDireita(pai);
                } else {
                    if (getCor(irmao->esq) == false && getCor(irmao->dir) == false) {
                        setCor(irmao, true);
                        if (getCor(pai) == true)
                            setCor(pai, false);
                        else
                            setCor(pai, DOUBLE_BLACK);
                        ptr = pai;
                    } else {
                        if (getCor(irmao->esq) == false) {
                            setCor(irmao->dir, false);
                            setCor(irmao, true);
                            rotacionarEsquerda(irmao);
                            irmao = pai->esq;
                        }
                        setCor(irmao, pai->cor);
                        setCor(pai, false);
                        setCor(irmao->esq, false);
                        rotacionarDireita(pai);
                        break;
                    }
                }
            }
        }
        if (N == N->pai->esq)
            N->pai->esq = NULL;
        else
            N->pai->dir = NULL;
        delete(N);
        setCor(raiz, false);
    }
}

NoRN* ArvRN::removerRN(NoRN *no, int info) {
    if (no == NULL)
        return no;

    if (info < no->info)
        return removerRN(no->esq, info);

    if (info > no->info)
        return removerRN(no->dir, info);

    if (no->esq == NULL || no->dir == NULL)
        return no;

    NoRN *temp = minValorNoRN(no->dir);
    no->info = temp->info;
    return removerRN(no->dir, temp->info);
}

void ArvRN::remover(int info) {
    NoRN *N = removerRN(raiz, info);
    balancearRemocao(N);
}

NoRN *ArvRN::minValorNoRN(NoRN *N) {

    NoRN *ptr = N;

    while (ptr->esq != NULL)
        ptr = ptr->esq;

    return ptr;
}

NoRN* ArvRN::maxValorNoRN(NoRN *N) {
    NoRN *ptr = N;

    while (ptr->dir != NULL)
        ptr = ptr->dir;

    return ptr;
}

int ArvRN::getAlturaNegra(NoRN *N) {
    int alturaNegra = 0;
    while (N != NULL) {
        if (getCor(N) == false)
            alturaNegra++;
        N = N->esq;
    }
    return alturaNegra;
}

void ArvRN::imprimir()
{
    imprimePorNivel(raiz, 0);
}

void ArvRN::imprimePorNivel(NoRN* p, int nivel)
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

bool ArvRN::busca(int C)
{
    return auxBusca(raiz, C);
}

bool ArvRN::auxBusca(NoRN* p, int C)
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
