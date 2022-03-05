#include <iostream>

#include "./Interfaces/PilhaEncadeada.hpp"
#include "./Interfaces/TipoItem.hpp"

int main()
{
  // gets the user's input
  std::string input;
  std::cin >> input;

  // converts infixed to postfixed
  std::string s;
  TipoItem newItem;
  TipoItem lastOperator;
  PilhaEncadeada operators = PilhaEncadeada();
  PilhaEncadeada postfixeds = PilhaEncadeada();
  for (int i = 0; i < input.length(); i++)
  {
    s = input[i];
    if (isdigit(input[i]))
    {
      newItem.SetChave(s);
      postfixeds.Empilha(newItem);
    }
    else if (input[i] == '*' || input[i] == '+')
    {
      newItem.SetChave(s);
      operators.Empilha(newItem);
    }
    else if (input[i] == ')')
    {
      lastOperator = operators.Desempilha();
      postfixeds.Empilha(lastOperator);
    }
  }

  // reverse postfixeds
  PilhaEncadeada results = postfixeds.reverse();
  std::cout << "Notação pós-fixada: ";
  results.print();
  std::cout << std::endl;

  // gets the amount
  int n1, n2;
  std::string result;
  PilhaEncadeada aux = PilhaEncadeada();
  TipoItem amount = TipoItem();
  while (!results.Vazia())
  {
    result = results.Desempilha().GetChave();
    if (result == "+")
    {
      n1 = stoi(aux.Desempilha().GetChave());
      n2 = stoi(aux.Desempilha().GetChave());
      amount.SetChave(std::to_string(n1 + n2));
      results.Empilha(amount);
    }
    else if (result == "*")
    {
      n1 = stoi(aux.Desempilha().GetChave());
      n2 = stoi(aux.Desempilha().GetChave());
      amount.SetChave(std::to_string(n1 * n2));
      results.Empilha(amount);
    }
    else
    {
      aux.Empilha(result);
    }
  }

  // shows the amount
  std::cout << "Resultado: " << result << std::endl;

  return 0;
}