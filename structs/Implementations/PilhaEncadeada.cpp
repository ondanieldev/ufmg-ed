#include <iostream>

#include "../Interfaces/PilhaEncadeada.hpp"

PilhaEncadeada::PilhaEncadeada() : Pilha()
{
  topo = NULL;
}

PilhaEncadeada::~PilhaEncadeada()
{
  Limpa();
}

void PilhaEncadeada::Empilha(TipoItem item)
{
  TipoCelula *nova;
  nova = new TipoCelula();
  nova->item = item;
  nova->prox = topo;
  topo = nova;
  tamanho++;
};

TipoItem PilhaEncadeada::Desempilha()
{
  TipoItem aux;
  TipoCelula *p;
  if (tamanho == 0)
    throw "A pilha está vazia!";
  aux = topo->item;
  p = topo;
  topo = topo->prox;
  delete p;
  tamanho--;
  return aux;
};

void PilhaEncadeada::Limpa()
{
  while (!Vazia())
    Desempilha();
}