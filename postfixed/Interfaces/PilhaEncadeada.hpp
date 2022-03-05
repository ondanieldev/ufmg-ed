#ifndef PILHAENCADEADA_HPP
#define PILHAENCADEADA_HPP

#include "Pilha.hpp"
#include "TipoItem.hpp"
#include "TipoCelula.hpp"

class PilhaEncadeada : public Pilha
{
public:
  PilhaEncadeada();
  virtual ~PilhaEncadeada();
  void Empilha(TipoItem item);
  TipoItem Desempilha();
  void Limpa();
  void print();
  PilhaEncadeada reverse();

private:
  TipoCelula *topo;
};

#endif