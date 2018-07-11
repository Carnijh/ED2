#include "lz77.h"
#include "string.h"

lz77::lz77(int tam_d, int tam_b) {

    tam_dicionario = tam_d;
    tam_buffer= tam_b;
    dicionario = new char[tam_dicionario];
    buffer = new char[tam_buffer];

    for(int i = 0; i < 0 ; i++){
        buffer[i] = ' ';
        dicionario[i] = ' ';
    }
}

lz77::~lz77()
{
    delete [] dicionario;
    delete [] buffer;
}

void lz77::adicionabuffer(char c){

    for(int i = 0; i < tam_buffer-1 ; i++)
       buffer[i] = buffer[i+1];

    buffer[tam_buffer-1] = c;
}

void lz77::adicionadicionario(char c){

    for(int i = 0; i < tam_dicionario-1 ; i++)
       dicionario[i] = dicionario[i+1];

    dicionario[tam_dicionario-1] = c;
}

bool lz77::verifica(char c){

    if(dicionario[tam_dicionario-1] != ' '){
        for(int i = tam_dicionario-1; i >= 0;i--){
            if(dicionario[i] == ' ')
                return false;
            if(dicionario[i] == 'c')
                return true;

        }
    }
    return false;
}

int lz77::indice(char c){

    if(dicionario[tam_dicionario-1] != ' '){
        for(int i = tam_dicionario-1; i >= 0;i--){
            if(dicionario[i] == ' ')
                return -1;
            if(dicionario[i] == 'c')
                return i;

        }
    }
    return -1;
}


void lz77::comprimir(std::string texto) {

    char cursor = texto[0];
    int local_cursor= 0;

    for(int i =0; i <tam_buffer; i++){
        buffer[i] = texto[i];
    }

    int l = 0;///comprimento da maior sequência
    int p = 0;///posição relativa (a contar do cursor) da maior sequência do dicionário
    int d = 0;
    std::string saida;

    while(cursor < texto.length()){

        for(int i =0 , j =local_cursor; i <l; i++, j++)
            adicionabuffer(texto[j]);

        for(int i =0 , j =local_cursor; i <l; i++, j++)
            adicionadicionario(texto[j]);

        d = indice(buffer[0]);

        if(!verifica(buffer[l])){
            saida = "<0,0," + buffer[l] +">";
            adicionadicionario(buffer[l]);
        }
        else{
            while((buffer[l] == dicionario[d] )&& l <tam_buffer){
                if(d == tam_dicionario-1)
                    d =indice(buffer[0]);
                l++;
                d++;
            }

            p = tam_dicionario - indice(buffer[0]);///parar saber quanto voltar em relação ao cursor
            saida = "<"+ p +","+ l + "," + buffer[l] +">";
        }
        local_cursor = local_cursor + (l+1);
        cursor = texto[local_cursor];
    }
    ~lz77();
}


void lz77::descomprimir(std::string texto) {

    std::string saida;

    while(cursor < texto.length()){

    }
}
