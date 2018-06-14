#include "NoB.h"
#include <iostream>

NoB::NoB(int tam, bool f)
{
    cout<<"alguma coisa3"<<endl;
    d = tam;
    numchaves = 0;
    info = new int [d+1];
    filho = new NoB *[d+2];
    folha = f;

    for(int i = 0; i < ((2*d)+1);i++)
        info[i] = -1;
    for (int i = 0; i < ((2*d)+2);i++)
        filho[i] = NULL;
    cout<<"alguma coisa4"<<endl;
}

NoB::~NoB()
{
    delete [] info;
    delete [] filho;
}

int NoB::getPosicao(int chave){

    int posicao = -1;

    for(int i = 0; i < ((2*d)+1); i++){
        if(chave == info[i])
            posicao = i;
    }
    return posicao;
}

NoB * NoB::getPai(NoB* no, NoB* raiz){

    NoB* p = raiz;
    int i = 0;
    int chave = info[0];

    while(true){
        if(p->filho[i] == no)
            return p;
        if(chave > p->info[i]){
            if(i<(2*d)+1)
                i++;
            else if(p->filho[i+1] != NULL){
                p = p->filho[i+1];
                i = 0;
            }
        }
        else if(p->filho[i] != NULL){
                p = p->filho[i];
                i = 0;
        }
    }
}

int NoB::getPosicaoPai(NoB* raiz, NoB* no){

    NoB* p = raiz;
    int i = 0;
    int chave = info[0];

    while(true){
        if(p->filho[i] == no)
            return i;
        if(chave > p->info[i]){
            if(i<(2*d)+1)
                i++;
            else if(p->filho[i+1] != NULL){
                p = p->filho[i+1];
                i = 0;
            }
        }
        else if(p->filho[i] != NULL){
                p = p->filho[i];
                i = 0;
        }
    }
}

void NoB::insere(int chave){

    cout<<"alguma coisa3"<<endl;
    if(numchaves == 0){
        info[0] = chave;
        numchaves ++;
    }
    else{
        int posicao = getPosicao(chave);
        if (posicao == -1){
            for(int i = numchaves - 1; i >= 0 ;i--){
                if(chave > info[i]){
                    info[i+1] = chave;
                    break;
                }
                else{
                    info[i+1] = info[i];
                    filho[i+1] = filho[i];
                    info[i] = chave;
                }
            }
            numchaves ++;
        }
        else
            cout<<"Chave "<<chave<<" ja inserida"<<endl;
    }
}

void NoB::remover(int chave){

    int posicao = getPosicao(chave);

    if (posicao != -1){
        for(int i = posicao; i < numchaves-1;i++){
            info[i] = info[i+1];
        }
        numchaves --;
        for(int i = (2*d)+1; i > numchaves;i--)
            info[i] = -1;
    }
    else
        cout<<"chave"<<chave<<"nao encontrada"<<endl;
}
