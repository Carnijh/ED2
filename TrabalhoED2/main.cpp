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
    cout<<"aqui 1"<<endl;
    arv.imprimir();
    for(int i = 1 ; i<(tam*2);i++){
        arv.inserir(i);
    }
    cout<<"aqui 2"<<endl;
    arv.imprimir();


    return 0;
}
