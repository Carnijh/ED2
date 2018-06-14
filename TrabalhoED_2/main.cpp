#include <iostream>
#include <stdlib.h>
#include <fstream>
#ifdef WIN32
 #include <time.h>
#endif // WIN32
#include "ArvoreB.h"
#include "arv_splay.h"
#include "ArvAVL.h"
#include "ArvAVLM.h"
#include "ArvRN.h"

using namespace std;

void tratar_arquivo(){
    fstream arquivo;
    arquivo.open("Questions.csv");
    ofstream lista;
    string::iterator c;
    lista.open("lista.txt",ios::in);
    string linha_local;
    string linha_global;
    string id;
    bool achou_id = false;
    getline(arquivo,linha_local);
    for(int k = 0;k<600000;){
        getline(arquivo,linha_local);
        c = linha_local.begin();
        linha_global.clear();
        linha_global += linha_local;

        while((*c >= '0' && *c <= '9')&& *c != ','){
            if(achou_id == false)
                id.push_back(*c);
            c++;
        }
        if(*c == ',')
                achou_id = true;
        while(!arquivo.eof()){
            while(*c != '"' && c != linha_local.end()){
                c++;
            }
            if(*c == '"'){
                c++;
                if(c == linha_local.end()){
                    //cout << k << endl;
                    //cout << linha_global << endl;
                    break;
                }
            }
            else if(c == linha_local.end()){
                getline(arquivo,linha_local);
                linha_global += linha_local;
                c = linha_local.begin();
            }
        }
        if(achou_id == true){
            lista << id << endl;
            k++;
        }
        achou_id = false;
        id.clear();
    }
    arquivo.close();
    lista.close();
}

int get_quant_dados(int i){

    int dados;
    string converter;
    ifstream entrada;
    entrada.open("entradaInsercao.txt");

    if(entrada.is_open()){
            if(i == 6){
                return -1;
            }
            for(int j = 0; j <=i; j++){
                getline(entrada,converter,',');
            }
            dados = atoi(converter.c_str());
    }
    else{
        cout<<"Erro ao abrir o arquivo entrada!"<<endl;
        exit(1);
    }
    entrada.close();
    return dados;
}

void randomizar(int v[], int n){

    cout<<"randomizar"<<endl;

    //srand(time(NULL));
    srand(1);
    ifstream inteiros;
    inteiros.open("lista.txt");
    int *aleatoriza = new int[n];
    string converter;

    if(inteiros.is_open()){

        getline(inteiros,converter);//para não aparecer a linha 0

        for(int i = 0; i<n; i++){
            getline(inteiros,converter);
            aleatoriza[i]=atoi(converter.c_str());//converte string para inteiro
        }
        for(int i = 0; i<n; i++){
            cout<<i<<endl;

            int aux = (rand()%(n));
            bool valido = false;
            while(valido == false){
                if(aux>=0){
                    if(aleatoriza[aux]!=0)
                        valido = true;
                }
                aux = (rand()%(n));
            }
            v[i]=aleatoriza[aux];
            aleatoriza[aux] = 0;
        }
    }
    else{
        cout<<"Erro ao abrir o arquivo lista!"<<endl;
        exit(1);
    }
    inteiros.close();
    delete [] aleatoriza;

}

int main()
{
    ///Tratamento do arquivo

    /*
    cout<<"tratando arquivo"<<endl;
    tratar_arquivo();
    cout<<"tratamento finalizado"<<endl;
    */

///analise Arvore B
    cout<<"Analise Arvore B"<<endl;
    int n = 0;
    int n_dados = get_quant_dados(n);///pega do arquivo entrada um N
    cout<<n_dados<<endl;
    clock_t t0, tf;
    double tempo_gastoInsercao;
    double tempo_gastoBusca;
    double tempo_gastoRemocao;

    while(n_dados != -1){

        cout<<"N = "<<n_dados<<endl;
        int *questionid = new int[n_dados];

        randomizar(questionid,n_dados);

        ///calcula tempo
        tempo_gastoInsercao = 0;
        t0 = clock();

        ///Inserir Arvore B
        cout<<"Inserindo"<<endl;
        int d = 3;
        ArvoreB arv(d);

        for(int i = 0; i<n_dados;i++){
            arv.inserir(questionid[i]);
            cout<<i<<endl;
        }

        tf = clock();
        tempo_gastoInsercao = ( (double) (tf - t0) ) / CLOCKS_PER_SEC;

        randomizar(questionid,n_dados);

        ///calcula tempo
        tempo_gastoBusca = 0;
        t0 = clock();

        ///Busca Arvore B
        for(int i = 0; i<n_dados;i++){
            NoB * p;
            p = arv.busca(questionid[i]);
        }

        tf = clock();
        tempo_gastoBusca = ( (double) (tf - t0) ) / CLOCKS_PER_SEC;

        randomizar(questionid,n_dados);

        ///calcula tempo
        tempo_gastoRemocao = 0;
        t0 = clock();

        ///Remocao Arvore B
        for(int i = 0; i<n_dados;i++)
            arv.remover(questionid[i]);

        tf = clock();
        tempo_gastoRemocao = ( (double) (tf - t0) ) / CLOCKS_PER_SEC;

        ///saida Arvore B

        ofstream saida;

        saida.open("saidaInsercao.txt",ios::app|ios::in);
        if(saida.is_open())
        {
            saida <<"Insercao Arvore B com N = "<<n_dados<<endl;
            saida <<endl;
            saida <<" tempo : "<<tempo_gastoInsercao<<endl;
            saida <<endl;
            saida.close();
        }
        else{
            cout<<"Erro ao abrir o arquivo saida!"<<endl;
            exit(1);
        }

        saida.open("saidaBusca.txt",ios::app|ios::in);
        if(saida.is_open())
        {
            saida <<"Busca Arvore B com N = "<<n_dados<<endl;
            saida <<endl;
            saida <<" tempo : "<<tempo_gastoBusca<<endl;
            saida <<endl;
            saida.close();
        }
        else{
            cout<<"Erro ao abrir o arquivo saida!"<<endl;
            exit(1);
        }

        saida.open("saidaRemocao.txt",ios::app|ios::in);
        if(saida.is_open())
        {
            saida <<"Remocao Arvore B com N = "<<n_dados<<endl;
            saida <<endl;
            saida <<" tempo : "<<tempo_gastoRemocao<<endl;
            saida <<endl;
            saida.close();
        }
        else{
            cout<<"Erro ao abrir o arquivo saida!"<<endl;
            exit(1);
        }

        delete []questionid;
        n++;
        n_dados = get_quant_dados(n);///pega do arquivo entrada um N
    }
    cout<<"Terminada Analise Arvore B"<<endl;
/*
///analise Arvore RN

    n = 0;
    n_dados = get_quant_dados(n);///pega do arquivo entrada um N
    cout<<n_dados<<endl;

    while(n_dados != -1){

        cout<<"N = "<<n_dados<<endl;
        int *questionid = new int[n_dados];

        randomizar(questionid,n_dados);

        ///calcula tempo
        tempo_gastoInsercao = 0;
        t0 = clock();

        ///Inserir Arvore RN
        ArvRN arv;

        for(int i = 0; i<n_dados;i++)
            arv.inserir(questionid[i]);

        tf = clock();
        tempo_gastoInsercao = ( (double) (tf - t0) ) / CLOCKS_PER_SEC;

        randomizar(questionid,n_dados);

        ///calcula tempo
        tempo_gastoBusca = 0;
        t0 = clock();

        ///Busca Arvore RN
        for(int i = 0; i<n_dados;i++){
            bool achou;
            achou = arv.busca(questionid[i]);
        }

        tf = clock();
        tempo_gastoBusca = ( (double) (tf - t0) ) / CLOCKS_PER_SEC;

        randomizar(questionid,n_dados);

        ///calcula tempo
        tempo_gastoRemocao = 0;
        t0 = clock();

        ///Remocao Arvore RN
        for(int i = 0; i<n_dados;i++)
            arv.remover(questionid[i]);

        tf = clock();
        tempo_gastoRemocao = ( (double) (tf - t0) ) / CLOCKS_PER_SEC;

        ///saida Arvore RN

        ofstream saida;

        saida.open("saidaInsercao.txt",ios::app|ios::in);
        if(saida.is_open())
        {
            saida <<"Insercao Arvore RN com N = "<<n_dados<<endl;
            saida <<endl;
            saida <<" tempo : "<<tempo_gastoInsercao<<endl;
            saida <<endl;
            saida.close();
        }
        else{
            cout<<"Erro ao abrir o arquivo saida!"<<endl;
            exit(1);
        }

        saida.open("saidaBusca.txt",ios::app|ios::in);
        if(saida.is_open())
        {
            saida <<"Busca Arvore RN com N = "<<n_dados<<endl;
            saida <<endl;
            saida <<" tempo : "<<tempo_gastoBusca<<endl;
            saida <<endl;
            saida.close();
        }
        else{
            cout<<"Erro ao abrir o arquivo saida!"<<endl;
            exit(1);
        }

        saida.open("saidaRemocao.txt",ios::app|ios::in);
        if(saida.is_open())
        {
            saida <<"Remocao Arvore RN com N = "<<n_dados<<endl;
            saida <<endl;
            saida <<" tempo : "<<tempo_gastoRemocao<<endl;
            saida <<endl;
            saida.close();
        }
        else{
            cout<<"Erro ao abrir o arquivo saida!"<<endl;
            exit(1);
        }

        delete []questionid;
        n++;
        n_dados = get_quant_dados(n);///pega do arquivo entrada um N
    }


///analise Arvore Splay

    n = 0;
    n_dados = get_quant_dados(n);///pega do arquivo entrada um N
    cout<<n_dados<<endl;

    while(n_dados != -1){

        cout<<"N = "<<n_dados<<endl;
        int *questionid = new int[n_dados];

        randomizar(questionid,n_dados);

        ///calcula tempo
        tempo_gastoInsercao = 0;
        t0 = clock();


        ///Inserir Arvore Splay
        arv_splay arv;

        for(int i = 0; i<n_dados;i++)
            arv.insere(questionid[i]);

        tf = clock();
        tempo_gastoInsercao = ( (double) (tf - t0) ) / CLOCKS_PER_SEC;

        randomizar(questionid,n_dados);

        ///calcula tempo
        tempo_gastoBusca = 0;
        t0 = clock();

        ///Busca Arvore Splay
        for(int i = 0; i<n_dados;i++){
            arv.busca(questionid[i]);
        }

        tf = clock();
        tempo_gastoBusca = ( (double) (tf - t0) ) / CLOCKS_PER_SEC;

        randomizar(questionid,n_dados);

        ///calcula tempo
        tempo_gastoRemocao = 0;
        t0 = clock();

        ///Remocao Arvore Splay
        for(int i = 0; i<n_dados;i++)
            arv.remove(questionid[i]);

        tf = clock();
        tempo_gastoRemocao = ( (double) (tf - t0) ) / CLOCKS_PER_SEC;

        ///saida Arvore Splay

        ofstream saida;

        saida.open("saidaInsercao.txt",ios::app|ios::in);
        if(saida.is_open())
        {
            saida <<"Insercao Arvore Splay com N = "<<n_dados<<endl;
            saida <<endl;
            saida <<" tempo : "<<tempo_gastoInsercao<<endl;
            saida <<endl;
            saida.close();
        }
        else{
            cout<<"Erro ao abrir o arquivo saida!"<<endl;
            exit(1);
        }

        saida.open("saidaBusca.txt",ios::app|ios::in);
        if(saida.is_open())
        {
            saida <<"Busca Arvore Splay com N = "<<n_dados<<endl;
            saida <<endl;
            saida <<" tempo : "<<tempo_gastoBusca<<endl;
            saida <<endl;
            saida.close();
        }
        else{
            cout<<"Erro ao abrir o arquivo saida!"<<endl;
            exit(1);
        }

        saida.open("saidaRemocao.txt",ios::app|ios::in);
        if(saida.is_open())
        {
            saida <<"Remocao Arvore Splay com N = "<<n_dados<<endl;
            saida <<endl;
            saida <<" tempo : "<<tempo_gastoRemocao<<endl;
            saida <<endl;
            saida.close();
        }
        else{
            cout<<"Erro ao abrir o arquivo saida!"<<endl;
            exit(1);
        }

        delete []questionid;
        n++;
        n_dados = get_quant_dados(n);///pega do arquivo entrada um N
    }

///analise Arvore AVL

    n = 0;
    n_dados = get_quant_dados(n);///pega do arquivo entrada um N
    cout<<n_dados<<endl;

    while(n_dados != -1){

        cout<<"N = "<<n_dados<<endl;
        int *questionid = new int[n_dados];

        randomizar(questionid,n_dados);

        ///calcula tempo
        tempo_gastoInsercao = 0;
        t0 = clock();


        ///Inserir Arvore AVL
        ArvAVL arv;

        for(int i = 0; i<n_dados;i++)
            arv.inserir(questionid[i]);

        tf = clock();
        tempo_gastoInsercao = ( (double) (tf - t0) ) / CLOCKS_PER_SEC;

        randomizar(questionid,n_dados);

        ///calcula tempo
        tempo_gastoBusca = 0;
        t0 = clock();

        ///Busca Arvore AVL
        for(int i = 0; i<n_dados;i++){
            bool achou;
            achou = arv.busca(questionid[i]);
        }

        tf = clock();
        tempo_gastoBusca = ( (double) (tf - t0) ) / CLOCKS_PER_SEC;

        randomizar(questionid,n_dados);

        ///calcula tempo
        tempo_gastoRemocao = 0;
        t0 = clock();

        ///Remocao Arvore AVL
        for(int i = 0; i<n_dados;i++)
            arv.remover(questionid[i]);

        tf = clock();
        tempo_gastoRemocao = ( (double) (tf - t0) ) / CLOCKS_PER_SEC;

        ///saida Arvore AVL

        ofstream saida;

        saida.open("saidaInsercao.txt",ios::app|ios::in);
        if(saida.is_open())
        {
            saida <<"Insercao Arvore AVL com N = "<<n_dados<<endl;
            saida <<endl;
            saida <<" tempo : "<<tempo_gastoInsercao<<endl;
            saida <<endl;
            saida.close();
        }
        else{
            cout<<"Erro ao abrir o arquivo saida!"<<endl;
            exit(1);
        }

        saida.open("saidaBusca.txt",ios::app|ios::in);
        if(saida.is_open())
        {
            saida <<"Busca Arvore AVL com N = "<<n_dados<<endl;
            saida <<endl;
            saida <<" tempo : "<<tempo_gastoBusca<<endl;
            saida <<endl;
            saida.close();
        }
        else{
            cout<<"Erro ao abrir o arquivo saida!"<<endl;
            exit(1);
        }

        saida.open("saidaRemocao.txt",ios::app|ios::in);
        if(saida.is_open())
        {
            saida <<"Remocao Arvore AVL com N = "<<n_dados<<endl;
            saida <<endl;
            saida <<" tempo : "<<tempo_gastoRemocao<<endl;
            saida <<endl;
            saida.close();
        }
        else{
            cout<<"Erro ao abrir o arquivo saida!"<<endl;
            exit(1);
        }

        delete []questionid;
        n++;
        n_dados = get_quant_dados(n);///pega do arquivo entrada um N
    }

///analise Arvore AVLM

    n = 0;
    n_dados = get_quant_dados(n);///pega do arquivo entrada um N
    cout<<n_dados<<endl;

    while(n_dados != -1){

        cout<<"N = "<<n_dados<<endl;
        int *questionid = new int[n_dados];

        randomizar(questionid,n_dados);

        ///calcula tempo
        tempo_gastoInsercao = 0;
        t0 = clock();


        ///Inserir Arvore AVLM
        ArvAVLM arv;

        for(int i = 0; i<n_dados;i++)
            arv.inserir(questionid[i]);

        tf = clock();
        tempo_gastoInsercao = ( (double) (tf - t0) ) / CLOCKS_PER_SEC;

        randomizar(questionid,n_dados);

        ///calcula tempo
        tempo_gastoBusca = 0;
        t0 = clock();

        ///Busca Arvore AVLM
        for(int i = 0; i<n_dados;i++){
            bool achou;
            achou = arv.busca(questionid[i]);
        }

        tf = clock();
        tempo_gastoBusca = ( (double) (tf - t0) ) / CLOCKS_PER_SEC;

        randomizar(questionid,n_dados);

        ///calcula tempo
        tempo_gastoRemocao = 0;
        t0 = clock();

        ///Remocao Arvore AVLM
        for(int i = 0; i<n_dados;i++)
            arv.remover(questionid[i]);

        tf = clock();
        tempo_gastoRemocao = ( (double) (tf - t0) ) / CLOCKS_PER_SEC;

        ///saida Arvore AVLM

        ofstream saida;

        saida.open("saidaInsercao.txt",ios::app|ios::in);
        if(saida.is_open())
        {
            saida <<"Insercao Arvore AVLM com N = "<<n_dados<<endl;
            saida <<endl;
            saida <<" tempo : "<<tempo_gastoInsercao<<endl;
            saida <<endl;
            saida.close();
        }
        else{
            cout<<"Erro ao abrir o arquivo saida!"<<endl;
            exit(1);
        }

        saida.open("saidaBusca.txt",ios::app|ios::in);
        if(saida.is_open())
        {
            saida <<"Busca Arvore AVLM com N = "<<n_dados<<endl;
            saida <<endl;
            saida <<" tempo : "<<tempo_gastoBusca<<endl;
            saida <<endl;
            saida.close();
        }
        else{
            cout<<"Erro ao abrir o arquivo saida!"<<endl;
            exit(1);
        }

        saida.open("saidaRemocao.txt",ios::app|ios::in);
        if(saida.is_open())
        {
            saida <<"Remocao Arvore AVLM com N = "<<n_dados<<endl;
            saida <<endl;
            saida <<" tempo : "<<tempo_gastoRemocao<<endl;
            saida <<endl;
            saida.close();
        }
        else{
            cout<<"Erro ao abrir o arquivo saida!"<<endl;
            exit(1);
        }

        delete []questionid;
        n++;
        n_dados = get_quant_dados(n);///pega do arquivo entrada um N
    }
    */
    return 0;
}
