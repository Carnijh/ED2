#ifndef ARVHUFF_H_INCLUDED
#define ARVHUFF_H_INCLUDED
#include "NoHuffman.h"
#define TAM 500

class ArvHuff {
    public:
        ArvHuff();
        ~ArvHuff();
        NoHuffman* raiz;
        char codigo[TAM][TAM];
        void inicializarArv(ArvHuff* arv);
        void criarArv(ArvHuff* arv, char* msg);
        void criarcodAux(ArvHuff* arv, NoHuffman* no, char* code, int fim);
        void criarCod(ArvHuff* arv);
        void codificar(ArvHuff* arv, char* msg, char* code);
        void decodificar(ArvHuff* arv, char* msg, char* code);
    private:

};

#endif // ARVHUFF_H_INCLUDED
