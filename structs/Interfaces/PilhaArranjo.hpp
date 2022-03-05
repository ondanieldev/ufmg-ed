#ifndef PILHAARRANJO_HPP
#define PILHAPILHAARRANJO_HPP

#include "Pilha.hpp"
#include "TipoItem.hpp"

class PilhaArranjo : public Pilha
{
public:
  PilhaArranjo();
  void Empilha(TipoItem item);
  TipoItem Desempilha();
  void Limpa();

private:
  int topo;
  static const int MAXTAM = 100;
  TipoItem itens[MAXTAM];
};

#endif