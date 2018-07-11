#include <iostream>
#include <cstdio>
#include "HeapMin.h"
#include "ArvHuff.h"
#define TAM 500
#include "NoHuffman.h"

using namespace std;

void ArvHuff::inicializarArv(ArvHuff* arv)
{
    int i;
    for(i=0;i<TAM;i++)
    {
        arv->codigo[i][0] = '\0';
    }
    arv->raiz = NULL;
}

void ArvHuff::criarArv(ArvHuff* arv, char* msg)
{
    int i,freq[TAM];
    for(i=0;i<TAM;i++) freq[i]=0;
    for(i=0;msg[i] != '\0';i++)
    {
        freq[(int)msg[i]]++;
    }
    HeapMin* heap;
    heap->criar(heap);
    for(i=0;i<TAM;i++)
    {
        if(freq[i]>0)
        {
            NoHuffman* novon;
            novon->simb = i;
            novon->freq = freq[i];
            novon->esq = NULL;
            novon->dir = NULL;
            heap->inserir(heap, novon);
        }

    }
    while(heap->fim > 1)
    {
        NoHuffman* pesq = heap->remover(heap);
        NoHuffman* pdir = heap->remover(heap);
        NoHuffman* nov = new NoHuffman();
        nov->simb = '#';
        nov->esq = pesq;
        nov->dir = pdir;
        nov->freq = pesq->freq + pdir->freq;
        heap->inserir(heap,nov);
    }
    arv->raiz = heap->remover(heap);
}

void ArvHuff::criarCod(ArvHuff* arv)
{
    char codigo[TAM];
    criarcodAux(arv, arv->raiz,codigo,-1);
}

void ArvHuff::criarcodAux(ArvHuff* arv, NoHuffman* no, char* code, int fim)
{
    if (no != NULL)
    {
        if(no->esq == NULL && no->dir == NULL)
        {
            int i;
            for(i=0;i<=fim;i++)
            {
                arv->codigo[(int)no->simb][i] = code[i];
            }
            arv->codigo[(int)no->simb][fim+1] = '\0';
        }
        else
        {
            if(no->esq != NULL)
            {
                fim++;
                code[fim] = '0';
                criarcodAux(arv, no->esq,code,fim);
                fim--;
            }
            if(no->dir != NULL)
            {
                fim++;
                code[fim] = '1';
                criarcodAux(arv,no->dir,code,fim);
                fim--;
            }
        }
    }
}
