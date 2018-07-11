#include <iostream>
#include <cstring>
#include "ArvHuff.h"
#include "HeapMin.h"

using namespace std;

int main()
{
    char* nome = "banana bafana";
    ArvHuff* arvore;
    arvore->inicializarArv(arvore);
    arvore->criarArv(arvore,nome);
    arvore->criarCod(arvore);
    return 0;
}
