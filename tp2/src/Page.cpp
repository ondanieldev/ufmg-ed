#include "Page.h"

Page::Page()
{
  this->popularity = -1;
  this->url = "";
  this->tape = -1;
}

std::string Page::getUrl()
{
  return this->url;
}

int Page::getPopularity()
{
  return this->popularity;
}

int Page::getTape()
{
  return this->tape;
}

void Page::setUrl(std::string url)
{
  this->url = url;
}

void Page::setPopularity(int popularity)
{
  this->popularity = popularity;
}

void Page::setTape(int tape)
{
  this->tape = tape;
}