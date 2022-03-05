#ifndef TIPOITEM_HPP
#define TIPOITEM_HPP

#include <iostream>

typedef std::string TipoChave;

class TipoItem
{
public:
  TipoItem();
  TipoItem(TipoChave c);
  void SetChave(TipoChave c);
  TipoChave GetChave();
  void Imprime();

private:
  TipoChave chave;
};

#endif