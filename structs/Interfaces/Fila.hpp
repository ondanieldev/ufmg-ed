#ifndef FILA_HPP
#define FILA_HPP

#include "TipoItem.hpp"

class Fila
{
public:
  Fila() { tamanho = 0; };
  int GetTamanho() { return tamanho; };
  bool Vazia() { return tamanho == 0; };
  virtual void Enfileira(TipoItem item) = 0;
  virtual TipoItem Desenfileira() = 0;
  virtual void Limpa() = 0;

protected:
  int tamanho;
};

#endif FILA_HPP