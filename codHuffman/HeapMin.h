#ifndef HEAPMIN_H_INCLUDED
#define HEAPMIN_H_INCLUDED
#include "NoHuffman.h"
#define TAM 100

class HeapMin {
    public:
        HeapMin();
        ~HeapMin();
        void inserir(HeapMin* heap, NoHuffman* no);
        NoHuffman* remover(HeapMin* heap);
        void criar(HeapMin* heap);
        bool vazia(HeapMin* heap);
        bool cheia(HeapMin* heap);
        void restauraOrdemIns(HeapMin* heap);
        void restauraOrdemRem(HeapMin* heap);
        NoHuffman* vetor[TAM];
        int fim;
    private:

};


#endif // HEAPMIN_H_INCLUDED
