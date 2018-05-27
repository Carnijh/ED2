#ifndef NoRN_H_INCLUDED
#define NoRN_H_INCLUDED

class NoRN
{
  public:
    NoRN()                  {};
    ~NoRN()                 {};
    void setEsq(NoRN* p)    { esq = p; };
    void setInfo(int val) { info = val; };
    void setDir(NoRN* p)    { dir = p; };
    NoRN* getEsq()          { return esq; };
    int getInfo()         { return info; };
    NoRN* getDir()          { return dir; };
  private:
    NoRN* esq; // ponteiro para o filho a esquerda
    int info; // informação do NoRN (int)
    NoRN* dir; // ponteiro para o filho a direita
};

#endif // NoRN_H_INCLUDED
