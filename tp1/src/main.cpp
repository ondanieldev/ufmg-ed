#include <iostream>
#include <fstream>
#include <exception>

#include "Scheduler.h"

int main(int argc, char *argv[])
{
  Scheduler scheduler = Scheduler();
  std::string command, hostName, urlName;
  int quantity;

  std::string inputName = argv[1];
  std::size_t extIndex = inputName.find_last_of('.');
  std::string name = inputName.substr(0, extIndex);
  std::string ext = inputName.substr(extIndex);
  std::string outputName = name + "-sexo" + ext;

  std::fstream input(inputName);
  if (!input)
  {
    throw std::invalid_argument("input file does not or was not provided");
  }

  std::fstream output;
  output.open(outputName, std::fstream::out);
  output.close();
  output.open(outputName, std::fstream::in);
  if (!output)
  {
    throw std::invalid_argument("creating output file has been failed");
  }

  while (input >> command)
  {
    if (command == "ADD_URLS")
    {
      input >> quantity;
      for (int i = 0; i < quantity; ++i)
      {
        input >> urlName;
        scheduler.addUrl(urlName);
      }
    }

    else if (command == "ESCALONA_TUDO")
    {
      scheduler.scheduleAll();
    }

    else if (command == "ESCALONA")
    {
      input >> quantity;
      scheduler.scheduleByQuantity(quantity);
    }

    else if (command == "ESCALONA_HOST")
    {
      input >> hostName;
      input >> quantity;
      scheduler.scheduleByHost(hostName, quantity);
    }

    else if (command == "VER_HOST")
    {
      input >> hostName;
      scheduler.showHost(hostName);
    }

    else if (command == "LISTA_HOSTS")
    {
      scheduler.indexHosts();
    }

    else if (command == "LIMPA_HOST")
    {
      input >> hostName;
      scheduler.clearHost(hostName);
    }
  }

  input.close();
  output.close();

  return 0;
}