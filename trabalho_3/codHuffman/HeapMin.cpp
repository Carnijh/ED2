#include <iostream>
#include <cstdio>
#include "HeapMin.h"

using namespace std;

HeapMin::HeapMin()
{

}

HeapMin::~HeapMin()
{

}

void HeapMin::inserir(HeapMin* heap, NoHuffman* no)
{
    heap->fim++;
    heap->vetor[heap->fim] = no;
    restauraOrdemIns(heap);
}

NoHuffman* HeapMin::remover(HeapMin* heap)
{

    NoHuffman* no;
    no =  heap->vetor[0];
    heap->vetor[0] = heap->vetor[heap->fim];
    heap->fim--;
    restauraOrdemRem(heap);
    return no;
}

void HeapMin::criar(HeapMin* heap)
{
    heap->fim = -1;
}

bool HeapMin::vazia(HeapMin* heap)
{
    return (heap->fim == -1);
}

bool HeapMin::cheia(HeapMin* heap)
{
    return (heap->fim == TAM-1);
}

void HeapMin::restauraOrdemRem(HeapMin* heap)
{
    int ind = 0;
    while(ind < heap->fim/2)
    {
        int filhoesq = (2*ind+1);
        int filhodir = (2*ind+2);
        int maiorfilho;
        if(filhodir <= heap->fim && heap->vetor[filhoesq]->freq < heap->vetor[filhodir]->freq)
        {
            maiorfilho = filhodir;
        }
        else
        {
            maiorfilho = filhoesq;
        }
        if(heap->vetor[ind]->freq >= heap->vetor[maiorfilho]->freq)
        {
            break;
        }
        NoHuffman* tmp = heap->vetor[ind];
        heap->vetor[ind] = heap->vetor[maiorfilho];
        heap->vetor[maiorfilho] = tmp;
        ind = maiorfilho;
    }
}

void HeapMin::restauraOrdemIns(HeapMin* heap)
{
    int ind = heap->fim;
    int pai = (ind-1)/2;
    while(ind > 0 && heap->vetor[ind]->freq > heap->vetor[pai]->freq)
    {
        NoHuffman* tmp = heap->vetor[ind];
        heap->vetor[ind] = heap->vetor[pai];
        heap->vetor[pai] = tmp;
        ind = pai;
        pai = (pai-1)/2;
    }
}
