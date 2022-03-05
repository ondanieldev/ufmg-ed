#ifndef URL_H
#define URL_H

#include <string>

class Page
{
public:
  Page();
  std::string getUrl();
  int getPopularity();
  int getTape();
  void setUrl(std::string url);
  void setPopularity(int popularity);
  void setTape(int tape);

private:
  std::string url;
  int popularity;
  int tape;
};

#endif