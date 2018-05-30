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
        cout<<"Chave nao encontrada arvore vazia!"<<endl;
        return NULL;
    }

    NoB * p = raiz;
    int i = 0;

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
        }
        else if(p->filho[i] != NULL){
                p = p->filho[i];
                i = 0;
            }
            else return p;
    }
}

NoB * ArvoreB::buscaB(int chave, bool * encontrada){

    if(raiz == NULL){
        cout<<"Chave nao encontrada arvore vazia!"<<endl;
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
        aux = new NoB(d,false);
        aux->insere(no->info[d+1]);
        no->remover(no->info[d+1]);
        aux->filho[0] = raiz;
        aux->filho[1] = new NoB(d,true);

        while(no->numchaves != d){
            aux->filho[1]->insere(no->info[d+1]);
            remover(no->info[d+1]);
        }
        for(int i= d+2,j = 0; i<((2*d)+2)||aux->filho[i]!=NULL ;i++, j++)
            aux->filho[j] = no->filho[i];

        raiz = aux;
    }
    else{
        aux = new NoB(d,true);
        int meio = no->info[d+1];
        NoB* pai = no->getPai(no,raiz);
        pai->insere(no->info[d+1]);
        remover(no->info[d+1]);
        pai->filho[no->getPosicao(meio)] = no->filho[no->getPosicao(meio)+1];
        pai->filho[no->getPosicao(meio)+1] = aux;

        while(no->numchaves != d){
            aux->filho[1]->insere(no->info[d+1]);
            remover(no->info[d+1]);
        }

        for(int i= d+2,j = 0; i<((2*d)+2)||aux->filho[i]!=NULL ;i++, j++)
            aux->filho[j] = no->filho[i];

        if(pai->numchaves == ((2*d)+1)){
            split(pai);
        }
    }
}

void ArvoreB::inserir(int chave){

    NoB * p = busca(chave);

    if(p == NULL){
        p = new NoB(d,true);
        p->insere(chave);
        raiz = p;
    }
    else{
        p->insere(chave);
        if(p->numchaves == ((2*d)+1)){
            split(p);
        }
    }
}

void ArvoreB::remover(int chave){

    bool * encontrado;
    * encontrado = false;
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
    ///arrumar aqui
    if(p->numchaves < d){
        NoB* pai = p->getPai(p,raiz);
        for(int i = 0;i<pai->numchaves;i++){
            if(pai->filho[i] == p){

            }
        }
    }
}

void ArvoreB::concatena(){// não faço ideia do que fazer

}
