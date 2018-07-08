#include <string>
#include <map>
#include <iostream>
#include <iterator>
#include <vector>
using namespace std;


template <typename Iterator>

Iterator comprimir(const string &naoComprimido, Iterator resultado) {
  // Construindo o dicionario.
  int tamDicionario = 256;
  map<string,int> dicionario;
  for (int i = 0; i < 256; i++)
    dicionario[string(1, i)] = i;

  string w;
  for (string::const_iterator it = naoComprimido.begin();
       it != naoComprimido.end(); ++it) {
    char c = *it;
    string wc = w + c;
    if (dicionario.count(wc))
      w = wc;
    else {
      *resultado++ = dicionario[w];
      // Add wc no dicionario.
      dicionario[wc] = tamDicionario++;
      w = string(1, c);
    }
  }

  // Saída de codificação.
  if (!w.empty())
    *resultado++ = dicionario[w];
  return resultado;
}

template <typename Iterator>

string descomprimir(Iterator begin, Iterator end) {
  // Construindo o dicionário.
  int tamDicionario = 256;
  map<int,string> dicionario;
  for (int i = 0; i < 256; i++)
    dicionario[i] = string(1, i);

  string w(1, *begin++);
  string resultado = w;
  string entrada;
  for ( ; begin != end; begin++) {
    int k = *begin;
    if (dicionario.count(k))
      entrada = dicionario[k];
    else if (k == tamDicionario)
      entrada = w + w[0];
    else
      throw "Bad compressed k";

    resultado += entrada;

    // Add w+entrada[0] no dicionario.
    dicionario[tamDicionario++] = w + entrada[0];

    w = entrada;
  }
  return resultado;
}


int main() {
  vector<int> comprimido;
  comprimir("CAROLINA RIBEIRO OLIVEIRA", back_inserter(comprimido));
  copy(comprimido.begin(), comprimido.end(), ostream_iterator<int>(cout, ", "));
  cout << endl;
  string descomprimido = descomprimir(comprimido.begin(), comprimido.end());
  cout << descomprimido << endl;
  return 0;
}
