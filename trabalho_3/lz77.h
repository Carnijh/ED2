#ifndef LZ77_H
#define LZ77_H
#include <iostream>
#include <string.h>
#include <stdlib.h>


class lz77
{
    public:
        lz77(int tam_d, int tam_b);
        ~lz77();
        void adicionabuffer(char c);
        void adicionadicionario(char c);
        bool verifica(char c);
        int indice(char c);
        void comprimir(std::string texto);
        void descomprimir(std::string texto)


    private:
        int tam_dicionario;
        int tam_buffer;
        char * buffer;
        char * dicionario;
};

#endif // LZ77_H
