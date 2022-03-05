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
  if (Vazia())
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

void PilhaEncadeada::print()
{
  TipoCelula *current = new TipoCelula();
  current = this->topo;
  for (int i = 0; i < this->tamanho; i++)
  {
    current->item.Imprime();
    current = current->prox;
  }
  delete current;
}

PilhaEncadeada PilhaEncadeada::reverse()
{
  TipoItem current = TipoItem();
  PilhaEncadeada aux = PilhaEncadeada();
  while (!this->Vazia())
  {
    current = this->Desempilha();
    aux.Empilha(current);
  }
  return aux;
}