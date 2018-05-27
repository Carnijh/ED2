#include <iostream>
#include "ArvRN.h"

using namespace std;

void preencheABB(ArvRN* a, int p, int q);

int main()
{
    ArvRN arv;

    cout << "Criando Arvore Rubro Negra" << endl;
    arv.inserir(15);
    arv.inserir(7);
    arv.inserir(3);
    arv.inserir(24);
    arv.inserir(6);
    arv.inserir(8);
    arv.inserir(10);
    arv.inserir(12);
    arv.inserir(17);
    arv.inserir(19);

    arv.imprimir();

    //cout << "Busca os valores 20 e 5" << endl;
    //cout << arv.busca(20) << endl;
    //cout << arv.busca(5) << endl;

    cout << endl << "Remover 24" << endl;
    arv.remover(24);

    cout << "Arvore Rubro Negra final" << endl;
    arv.imprimir();

    return 0;
}
