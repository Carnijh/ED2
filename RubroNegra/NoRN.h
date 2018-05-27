#ifndef NoRN_H_INCLUDED
#define NoRN_H_INCLUDED

enum Cor {RED, BLACK, DOUBLE_BLACK};

class NoRN
{
public:
	NoRN(int c) { info = c; cor = RED; esq = NULL; dir = NULL; pai = NULL; }
	~NoRN() {}
    int info;
	int cor;
	NoRN *esq;
	NoRN *dir;
	NoRN *pai;
};

#endif // NoRN_H_INCLUDED
