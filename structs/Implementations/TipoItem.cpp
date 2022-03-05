#include <iostream>

#include "../Interfaces/TipoItem.hpp"

TipoItem::TipoItem()
{
  chave = -1; // indica um item vazio
}

TipoItem::TipoItem(TipoChave c)
{
  chave = c;
}

void TipoItem::SetChave(TipoChave c)
{
  chave = c;
}

TipoChave TipoItem::GetChave()
{
  return chave;
}

void TipoItem::Imprime()
{
  std::cout << chave;
}
