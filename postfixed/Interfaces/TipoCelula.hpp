#ifndef TIPOCELULA_HPP
#define TIPOCELULA_HPP

#include "TipoItem.hpp"

class TipoCelula
{
public:
  TipoCelula();

private:
  TipoItem item;
  TipoCelula *prox;
  friend class PilhaEncadeada;
};

#endif