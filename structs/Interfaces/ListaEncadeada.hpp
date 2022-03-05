#ifndef LISTAENCADEADA_HPP
#define LISTAENCADEADA_HPP

#include "Lista.hpp"
#include "TipoItem.hpp"
#include "TipoCelula.hpp"

class ListaEncadeada : public Lista
{
public:
  ListaEncadeada();
  ~ListaEncadeada();
  TipoItem GetItem(int pos);
  void SetItem(TipoItem item, int pos);
  void InsereInicio(TipoItem item);
  void InsereFinal(TipoItem item);
  void InserePosicao(TipoItem item, int pos);
  TipoItem RemoveInicio();
  TipoItem RemoveFinal();
  TipoItem RemovePosicao(int pos);
  TipoItem Pesquisa(TipoChave c);
  void Imprime();
  void Limpa();

private:
  TipoCelula *primeiro;
  TipoCelula *ultimo;
  TipoCelula *Posiciona(int pos, bool antes);
};

#endif