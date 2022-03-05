#include <iostream>
#include <fstream>
#include <exception>

#include "Page.h"
#include "Quicksort.h"
#include "Storage.h"

int main(int argc, char *argv[])
{
  // Delete preview tapes
  Storage::resetTapesDir();

  // Get user input
  std::string inputPath = argv[1];
  std::string outputPath = argv[2];
  int maxEntities = std::stoi(argv[3]);
  int maxTapes = std::stoi(argv[4]);

  // Open input and output files
  std::fstream input(inputPath);
  std::fstream output(outputPath);
  if (input.fail())
  {
    throw std::invalid_argument("input file does not exits or has not been provided");
  }
  if (output.fail())
  {
    throw std::invalid_argument("output file doest not exist or has not been provided");
  }

  // Order
  Storage::generateTapes(input, maxTapes, maxEntities);
  Storage::mergeTapes(output, maxTapes);

  // Close input and output files
  input.close();
  output.close();

  return 0;
}