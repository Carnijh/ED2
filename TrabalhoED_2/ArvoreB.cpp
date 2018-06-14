#include "ArvoreB.h"
#include "Nob.h"


ArvoreB::ArvoreB(int tamanho){

    d = tamanho;
    raiz = NULL;
}

ArvoreB::~ArvoreB(){

    deletarArvore(raiz);

}

void ArvoreB::deletarArvore(NoB* no){

    if(no == NULL)
        return;
    for(int i = 0; i <= no->numchaves; i++){
        deletarArvore(no->filho[i]);
        delete no->filho[i];
    }
}

void ArvoreB::imprimir(){

    if(raiz == NULL)
        cout<<"Nao pode imprimir, arvore vazia!"<<endl;
    else
        imprimirAux(raiz);
}

void ArvoreB::imprimirAux(NoB * no){

    if(no == NULL)
        return;
    for(int i = 0; i < no->numchaves; i++){
        imprimirAux(no->filho[i]);
        cout<<no->info[i]<<endl;
    }
}

NoB * ArvoreB::busca(int chave){

    if(raiz == NULL){
        return NULL;
    }

    NoB * p = raiz;
    int i = 0;
    NoB *aux = NULL;/*
    while(true){
        if(chave == p->info[i]){
            cout<<"Chave encontrada!"<<endl;
            return p;
        }
        if(chave > p->info[i]){
            if(i<(2*d)+1)
                i++;
            else if(p->filho[i+1] != NULL){
                p = p->filho[i+1];
                i = 0;
            }
            else return p;
        }
        else if(p->filho[i] != NULL){
                p = p->filho[i];
                i = 0;
        }
        else return p;
    }*/
    if(chave == 0){
     cout<<chave<<endl;
    }
    while(p){
        if(p->getPosicao(chave)!=-1){
            aux = p;
            int i = 0;
            for(i =0; i<(2*d)+1; i++){
                if(p->info[i]>chave){
                    p = p->filho[i];
                    break;
                }
            }
            if(i == (2*d)+1){
                p = p->filho[i];
            }
        }
        else{
            return p;
        }
    }
    return aux;
}

NoB * ArvoreB::buscaB(int chave, bool * encontrada){

    if(raiz == NULL){
        return NULL;
    }

    NoB * p = raiz;
    int i = 0;

    while(true){
        if(chave == p->info[i]){
            cout<<"Chave encontrada!"<<endl;
            *encontrada = true;
            return p;
        }
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
            else{
                *encontrada = false;
                return p;
            }
    }
}

void ArvoreB::split(NoB * no){

    NoB * aux;
    if(no == raiz){
        cout<<"alguma coisa"<<endl;
        aux = new NoB(d,false);
        cout<<"alguma coisa2"<<endl;
        aux->insere(no->info[d]);
        no->remover(no->info[d]);
        aux->filho[0] = raiz;
        aux->filho[1] = new NoB(d,true);

        for(int i= d+1,j = 0; i<((2*d)+1) ;i++, j++){
            aux->info[j] = no->info[i];
            no->info[i] = NULL;
            no->numchaves--;
            aux->numchaves++;
        }

        for(int i= d,j = 0; i<((2*d)+2) ;i++, j++){
            aux->filho[j] = no->filho[i];
            no->filho[i] = NULL;
        }
        raiz = aux;
    }
    else{

        aux = new NoB(d,true);
        int meio = no->info[d];
        NoB* pai = no->getPai(no,raiz);
        pai->insere(meio);
        remover(meio);
        pai->filho[no->getPosicao(meio)] = no->filho[no->getPosicao(meio)+1];
        pai->filho[no->getPosicao(meio)+1] = aux;

        for(int i= d+1,j = 0; i<((2*d)+1) ;i++, j++){
            aux->info[j] = no->info[i];
            no->info[i] = NULL;
            no->numchaves--;
            aux->numchaves++;
        }

        for(int i= d+2,j = 0; i<((2*d)+2)||aux->filho[i]!=NULL ;i++, j++){
            aux->filho[j] = no->filho[i];
            no->filho[i] = NULL;
        }

        if(pai->numchaves == ((2*d)+1)){
            split(pai);
        }
    }
}

void ArvoreB::inserir(int chave){

    NoB * p = busca(chave);
    cout<<"aqui"<<endl;
    if(p == NULL){
        cout<<"aqui 2"<<endl;
        p = new NoB(d,true);
        p->insere(chave);
        raiz = p;
    }
    else{
        cout<<"aqui3"<<endl;
        p->insere(chave);
        if(p->numchaves == ((2*d)+1)){
            split(p);
        }
    }
}

void ArvoreB::remover(int chave){

    bool * encontrado;
    *encontrado = false;
    NoB * p = buscaB(chave,encontrado);

    if(p == NULL){
       cout<<"Arvore vazia!"<<endl;
       return;
    }
    if(encontrado == false){
        cout<<"Chave não encontrada!"<<endl;
        return;
    }
    if(p->folha == true)
        p->remover(chave);
    else{
        NoB* aux = p;
        int posicao = p->getPosicao(chave);

        while(aux->folha!= true){
            for(int k = aux->numchaves; k >= 0; k--){
                if(aux->filho[k]!= NULL){
                    aux = aux->filho[k];
                    break;
                }
            }
        }
        int maior_imediato = aux->info[aux->numchaves-1];
        aux->remover(maior_imediato);
        p->info[posicao] = maior_imediato;
    }
    ///underflow
    if(p->numchaves < d){
        NoB* pai = p->getPai(p,raiz);
        int posicaoPai = p->getPosicaoPai(raiz,p);
        concatena(pai,p,pai->filho[posicaoPai+1]);
    }
}

void ArvoreB::concatena(NoB * pai, NoB* no,NoB* irmao){

    int posicaoPai = no->getPosicaoPai(raiz, no);
    int chavePai = pai->info[posicaoPai];
    no->insere(chavePai);
    pai->remover(chavePai);

    for(int i = 0; i<irmao->numchaves; i++)
        no->insere(irmao->info[i]);

    pai->filho[posicaoPai+1] = NULL;
}
