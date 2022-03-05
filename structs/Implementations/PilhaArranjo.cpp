#include "../Interfaces/PilhaArranjo.hpp"

PilhaArranjo::PilhaArranjo() : Pilha()
{
  topo = -1;
}

void PilhaArranjo::Empilha(TipoItem item)
{
  if (tamanho == MAXTAM)
    throw "A pilha está cheia!";
  topo++;
  itens[topo] = item;
  tamanho++;
};

TipoItem PilhaArranjo::Desempilha()
{
  TipoItem aux;
  if (tamanho == 0)
    throw "A pilha está vazia!";
  aux = itens[topo];
  topo--;
  tamanho--;
  return aux;
  ;
};

void PilhaArranjo::Limpa()
{
  topo = -1;
  tamanho = 0;
};