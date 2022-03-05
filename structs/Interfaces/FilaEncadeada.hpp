#ifndef FILAENCADEADA_HPP
#define FILAENCADEADA_HPP

#include "Fila.hpp"
#include "TipoCelula.hpp"

class FilaEncadeada : public Fila
{
public:
  FilaEncadeada();
  virtual ~FilaEncadeada();
  void Enfileira(TipoItem item);
  TipoItem Desenfileira();
  void Limpa();

private:
  TipoCelula *frente;
  TipoCelula *tras;
};

#endif