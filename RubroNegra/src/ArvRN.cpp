#include <iostream>
#include "ArvRN.h"

using namespace std;

ArvRN::ArvRN()
{
    raiz = NULL;
}

bool ArvRN::vazia()
{
    return raiz == NULL;
}

void ArvRN::insere(int C)
{
    raiz = auxInsere(raiz, C);
}

NoRN* ArvRN::auxInsere(NoRN *p, int C)
{
    if(p == NULL)
    {
        p = new NoRN;
        p->setInfo(C);
        p->setEsq(NULL);
        p->setDir(NULL);
    }
    else if(C < p->getInfo())
        p->setEsq(auxInsere(p->getEsq(), C));
    else
        p->setDir(auxInsere(p->getDir(), C));
    return p;
}

bool ArvRN::busca(int C)
{
    return auxBusca(raiz, C);
}

bool ArvRN::auxBusca(NoRN* p, int C)
{
    if(p == NULL)
        return false;
    else if(p->getInfo() == C)
        return true;
    else if(C < p->getInfo())
        return auxBusca(p->getEsq(), C);
    else
        return auxBusca(p->getDir(), C);
}

void ArvRN::remove(int C)
{
    raiz = auxRemove(raiz, C);
}

NoRN* ArvRN::auxRemove(NoRN* p, int C)
{
    if(p == NULL)
        return NULL;
    else if(C < p->getInfo())
        p->setEsq(auxRemove(p->getEsq(), C));
    else if(C > p->getInfo())
        p->setDir(auxRemove(p->getDir(), C));
    else
    {
        if(p->getEsq() == NULL && p->getDir() == NULL)
            p = removeFolha(p);
        else if((p->getEsq() == NULL) || (p->getDir() == NULL))
            p = remove1Filho(p);
        else
        {
            NoRN *aux = maiorSubArvEsquerda(p);
            int auxC = aux->getInfo();
            p->setInfo(auxC);
            aux->setInfo(C);
            p->setEsq(auxRemove(p->getEsq(), C));
        }
    }
    return p;
}

NoRN* ArvRN::removeFolha(NoRN *p)
{
    delete p;
    return NULL;
}

NoRN* ArvRN::remove1Filho(NoRN *p)
{
    NoRN *aux;
    if(p->getEsq() == NULL)
        aux = p->getDir();
    else
        aux = p->getEsq();
    delete p;
    return aux;
}

NoRN* ArvRN::meNoRNrSubArvDireita(NoRN *p)
{
    NoRN *aux = p->getDir();
    while(aux->getEsq() != NULL)
        aux = aux->getEsq();
    return aux;
}

void ArvRN::imprime()
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
        cout << p->getInfo() << endl;
        imprimePorNivel(p->getEsq(), nivel+1);
        imprimePorNivel(p->getDir(), nivel+1);
    }
}

ArvRN::~ArvRN()
{
    raiz = libera(raiz);
}

NoRN* ArvRN::libera(NoRN *p)
{
    if(p != NULL)
    {
        p->setEsq(libera(p->getEsq()));
        p->setDir(libera(p->getDir()));
        delete p;
        p = NULL;
    }
    return p;
}

float ArvRN::mediaCaminho(int ch)
{
    int soma = 0, cont = 0;
    if(raiz != NULL)
    {
        NoRN *p = raiz;
        while(p->getInfo() != ch && p != NULL)
        {
            cont = cont + 1;
            soma = soma + p->getInfo();
            if(ch > p->getInfo())
                p = p->getDir();
            else
                p = p->getEsq();
        }
        if(p != NULL) // soma contribuicao do NoRN com valor ch
        {
            cont = cont + 1;
            soma = soma + p->getInfo();
        }
    }
    return (float)soma/cont;
}

int ArvRN::maior()
{
    NoRN* p;
    for(p=raiz; p!=NULL; p=p->getDir())
    {
        if(p->getDir()==NULL)
            return p->getInfo();
    }
}

int ArvRN::meNoRNr()
{
    NoRN* p;
    for(p=raiz; p!=NULL; p=p->getEsq())
    {
        if(p->getEsq()==NULL)
            return p->getInfo();
    }
}

void ArvRN::removeMaior()
{
    NoRN* pai=NULL;
    NoRN* p=raiz;
    while(p->getDir()!=NULL)
    {
        pai=p;
        p=p->getDir();
    }
    if(pai==NULL)
        raiz=p->getEsq();
    else
        pai->setDir(p->getEsq());
    delete p;
}

void ArvRN::removeMeNoRNr()
{
    NoRN* pai=NULL;
    NoRN* p=raiz;
    while(p->getEsq()!=NULL)
    {
        pai=p;
        p=p->getEsq();
    }
    if(pai==NULL)
        raiz=p->getDir();
    else
        pai->setEsq(p->getDir());
    delete p;
}

int ArvRN::contaParesCaminho(int x)
{
    NoRN* p=raiz;
    int cont=0;
    while(p->getInfo() != x && p!=NULL)
    {
        if(p->getInfo()%2==0)
            cont++;
        if(x<p->getInfo())
            p=p->getEsq();
        else
            p=p->getDir();
    }
    if(x%2==0)
        return cont+1;
    else
        return cont;
}

NoRN* ArvRN::maiorSubArvEsquerda(NoRN *p)
{
    NoRN *aux = p->getEsq();
    while(aux->getDir() != NULL)
        aux = aux->getDir();
    return aux;
}
