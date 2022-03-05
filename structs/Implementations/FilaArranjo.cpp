#include "../Interfaces/FilaArranjo.hpp"

FilaArranjo::FilaArranjo() : Fila()
{
  frente = 0;
  tras = 0;
}

void FilaArranjo::Enfileira(TipoItem item)
{
  if (tamanho == MAXTAM)
    throw "Fila Cheia!";
  itens[tras] = item;
  // fila circular
  tras = (tras + 1) % MAXTAM;
  tamanho++;
}

TipoItem FilaArranjo::Desenfileira()
{
  TipoItem aux;
  if (tamanho == 0)
    throw "Fila está vazia!";
  aux = itens[frente];
  // fila circular
  frente = (frente + 1) % MAXTAM;
  tamanho--;
  return aux;
}

void FilaArranjo::Limpa()
{
  frente = 0;
  tras = 0;
  tamanho = 0;
}