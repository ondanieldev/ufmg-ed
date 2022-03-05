#include <iostream>

#include "../Interfaces/FilaEncadeada.hpp"

FilaEncadeada::FilaEncadeada() : Fila()
{
  frente = new TipoCelula; // Célula cabeça;
  tras = frente;
}

FilaEncadeada::~FilaEncadeada()
{
  Limpa();
  delete frente;
}

void FilaEncadeada::Enfileira(TipoItem item)
{
  TipoCelula *nova;
  nova = new TipoCelula();
  nova->item = item;
  tras->prox = nova;
  tras = nova;
  tamanho++;
}

TipoItem FilaEncadeada::Desenfileira()
{
  TipoCelula *p;
  TipoItem aux;
  if (tamanho == 0)
    throw "Fila está vazia!";
  aux = frente->prox->item;
  p = frente;
  frente = frente->prox;
  delete p;
  tamanho--;
  return aux;
}

void FilaEncadeada::Limpa()
{
  TipoCelula *p;
  p = frente->prox;
  while (p != NULL)
  {
    frente->prox = p->prox;
    delete p;
    p = frente->prox;
  }
  tamanho = 0;
  tras = frente;
}