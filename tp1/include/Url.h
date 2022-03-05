#ifndef URL_H
#define URL_H

#include <string>

class Url
{
public:
  Url();
  void setName(std::string n);
  std::string getName();
  std::string getHostName();

private:
  std::string name;
  Url *next;
  int depth;
  std::string hostName;
};

#endif