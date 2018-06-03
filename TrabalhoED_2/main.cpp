#include <iostream>
#include <stdlib.h>
#include <fstream>
#include "ArvoreB.h"

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
        /*if(*c >= '0' && *c <='9'){
            while(*c != ','){
                if(*c >= '0' && *c <= '9'){
                id.push_back(*c);
                }else if(*c == ','){
                    lista << id << endl;
                    linha_local.clear();
                    id.clear();
                    break;
                }
                c++;
            }
        }*/
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
                    cout << k << endl;
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
    entrada.open("entrada.txt");

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

    srand(time(NULL));

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

    ///Arvore B
    int tam = 2;
    ArvoreB arv(tam);
    arv.inserir(1);
    arv.inserir(2);

    arv.imprimir();
    for(int i = 1; i<3;i++){
        //arv.inserir(i);
        arv.imprimir();

    }
    arv.imprimir();

    /// saida arquivo com o exemplo do cenario 1 do trabalho anterior

    /// Cenario 1
{

    int n = 0;
    int n_dados = get_quant_dados(n);///pega do arquivo entrada um N
    int n_dados;
    cin>> n_dados;
    cout<<n_dados<<endl;
    clock_t t0, tf;
    double tempo_gasto;

    while(n_dados != -1){

        cout<<"N = "<<n_dados<<endl;
        int *questionid = new int[n_dados];

        randomizar(questionid,n_dados);

        ///calcula tempo
        tempo_gasto = 0;
        t0 = clock();
        quicksort(questionid,0,n_dados-1);
        imprimir(questionid,n_dados);

        tf = clock();
        tempo_gasto = ( (double) (tf - t0) ) / CLOCKS_PER_SEC;

        ofstream saida;
        saida.open("saida.txt",ios::app|ios::in);
        if(saida.is_open())
        {
            saida <<"Cenario 1, com N = "<<n_dados<<endl;
            saida <<endl;
            saida <<" comparaçoes = "<<comp<<endl;
            saida <<" copia de registro = "<<chaves_iguais<<endl;
            saida <<" tempo : "<<tempo_gasto<<endl;
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
        cin>> n_dados;
    }
}


    return 0;
}
