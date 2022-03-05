#ifndef STORAGE_H
#define STORAGE_H

#include <fstream>

class Storage
{
public:
  static void resetTapesDir();
  static void generateTapes(std::fstream &input, int maxTapes, int maxEntities);
  static void mergeTapes(std::fstream &output, int maxTapes);

private:
  static std::string getTapePath(int i);
  static void populateTape(std::fstream &input, std::fstream &tape, int maxEntities);
};

#endif