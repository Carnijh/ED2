#include <iostream>
#include "ArvAVLM.h"

using namespace std;

int main()
{
    ArvAVLM t;
    t.inserir(20);
    t.inserir(25);
    t.inserir(15);
    t.inserir(10);
    t.inserir(30);
    t.inserir(5);
    t.inserir(35);
    t.inserir(67);
    t.inserir(43);
    t.inserir(21);
    t.inserir(10);
    t.inserir(89);
    t.inserir(38);
    t.inserir(69);
    t.imprimir();
    t.remover(5);
    t.remover(35);
    t.remover(65);
    t.remover(89);
    t.remover(43);
    t.remover(88);
    t.remover(20);
    t.remover(38);
    t.imprimir();

    return 0;
}
