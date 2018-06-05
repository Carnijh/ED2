#ifndef ARV_SPLAY_H
#define ARV_SPLAY_H
#include "No.h"

class arv_splay
{
    public:
        arv_splay();
        ~arv_splay();
        void insere(int val);
        void imprime();
        No* splaying(No* no, int val);
        void remove (int val);
        void busca(int val);
    private:
        No* raiz;
        void imprimeporNivel(No* no, int nivel);
        No* auxInsere(No* no, int val);
        void libera(No* raiz);
        No* zigEsq(No* no);
        No* zagDir(No* no);
        No* auxRemove(No* no, int val);
        No* removeFolha(No* no);
        No* removeUmFilho(No* no);
        bool auxBusca(No* no, int val);
        No* menorSubArvDireita(No *no);
};

#endif // ARV_SPLAY_H
