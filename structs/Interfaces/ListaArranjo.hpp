#ifndef LISTAARRANJO_HPP
#define LISTAARRANJO_HPP

#include "Lista.hpp"
#include "TipoItem.hpp"

class ListaArranjo : public Lista
{
public:
  ListaArranjo() : Lista(){};
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
  static const int MAXTAM = 100;
  TipoItem itens[MAXTAM];
};

#endif