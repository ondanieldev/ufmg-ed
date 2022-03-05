#include <algorithm>
#include <iostream>
#include <regex>

#include "Url.h"

Url::Url()
{
  this->name = "";
  this->next = NULL;
}

void Url::setName(std::string n)
{
  // just http protocol is allowed
  std::string protocol = n.substr(0, 7);
  if (protocol != "http://")
  {
    throw std::invalid_argument("invalid protocol");
  }

  // discard #<fragment>
  std::size_t fragmentPos = n.find_last_of('#');
  n = n.substr(0, fragmentPos);

  // just html pages are allowed
  std::size_t queryPos = n.find_last_of('?');
  std::string urlNameWithoutQuery = n.substr(0, queryPos);
  std::regex extRx(".*\\.(pdf|jpg|gif|mp3|avi|doc)");
  bool isUnallowedExt = std::regex_match(urlNameWithoutQuery, extRx);
  if (isUnallowedExt)
  {
    throw std::invalid_argument("invalid extension");
  }

  // discard "www"
  std::string www = n.substr(7, 4);
  if (www == "www.")
  {
    n = n.erase(7, 4);
  }

  // discard last "/"
  std::size_t lastSlash = n.find_last_of('/');
  if (lastSlash == n.length() - 1)
  {
    n.pop_back();
  }

  // get hostname
  std::string urlWithoutProtocol = n.substr(7);
  std::size_t endHost = urlWithoutProtocol.find_first_of('/');
  std::string host = urlWithoutProtocol.substr(0, endHost);

  // saves url name and depth
  this->name = n;
  this->depth = std::count(this->name.begin(), this->name.end(), '/');
  this->hostName = host;
}

std::string Url::getName()
{
  return this->name;
}

std::string Url::getHostName()
{
  return this->hostName;
}