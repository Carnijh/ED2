#include <iostream>
#include "arv_splay.h"
#include <cstdio>

using namespace std;

int main()
{
    arv_splay arvoreS;
    arvoreS.insere(10);
    arvoreS.insere(5);
    arvoreS.insere(20);
    arvoreS.insere(12);
    arvoreS.insere(13);
    arvoreS.insere(25);
    arvoreS.insere(83);
    arvoreS.imprime();
    arvoreS.remove(25);
    arvoreS.imprime();
    return 0;
}
