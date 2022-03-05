#ifndef FILAARRANJO_HPP
#define FILAARRANJO_HPP

#include "Fila.hpp"
#include "TipoItem.hpp"

class FilaArranjo : public Fila
{
public:
  FilaArranjo();
  void Enfileira(TipoItem item);
  TipoItem Desenfileira();
  void Limpa();

private:
  int frente;
  int tras;
  static const int MAXTAM = 8;
  TipoItem itens[MAXTAM];
};

#endif