#ifndef ArvRN_H_INCLUDED
#define ArvRN_H_INCLUDED

#include <iostream>
#include <cstdlib>
#include "NoRN.h"

class ArvRN
{
    public:
        ArvRN();
        ~ArvRN();
        bool vazia(); // verifica se a �rvore est� vazia
        bool busca(int C);
        void insere(int C);
        void remove(int C);
        void imprime();
        float mediaCaminho(int ch);
        int maior();
        int meNoRNr();
        void removeMaior();
        void removeMeNoRNr();
        int contaParesCaminho(int x);
        NoRN* maiorSubArvEsquerda(NoRN *p);

    private:
        NoRN* raiz; // ponteiro para o NoRN raiz da �rvore
        bool auxBusca(NoRN *p, int C);
        NoRN* auxInsere(NoRN *p, int C);
        NoRN* auxRemove(NoRN *p, int C);
        NoRN* meNoRNrSubArvDireita(NoRN *p);
        NoRN* removeFolha(NoRN *p);
        NoRN* remove1Filho(NoRN *p);
        void imprimePorNivel(NoRN* p, int nivel);
        NoRN* libera(NoRN *p);
};


#endif // ArvRN_H_INCLUDED


