#include <iostream>
#include <regex>

#include "Url.h"
#include "Scheduler.h"
#include "Host.h"

Scheduler::Scheduler()
{
  this->hosts = Queue();
}

void Scheduler::addUrl(std::string urlName)
{
  // create url
  Url *url = new Url();
  try
  {
    url->setName(urlName);
  }
  catch (std::invalid_argument e)
  {
    return;
  }

  // find url host
  std::string hostName = url->getHostName();
  Host *host = this->hosts.search(hostName);

  // if the host exists, add the url to them
  if (host != NULL)
  {
    host->urls.add(url);
    return;
  }

  // if the host doesnt exist, create and add the url to them
  host = new Host();
  host->name = hostName;
  host->urls.add(url);
  this->hosts.enqueue(host);
}

void Scheduler::scheduleAll()
{
  Host *host = this->hosts.front;
  Url *url;

  while (host != NULL)
  {
    while (!host->urls.isEmpty())
    {
      url = host->urls.removeAtHead();
      std::cout << url->name << std::endl;
    }
    host = host->next;
  }
}

void Scheduler::scheduleByQuantity(int quantity)
{
  Host *host = this->hosts.front;
  Url *url;
  int i = 0;

  while (i < quantity && host != NULL)
  {
    if (host->urls.isEmpty())
    {
      host = host->next;
    }
    url = host->urls.removeAtHead();
    std::cout << url->name << std::endl;
    ++i;
  }
}

void Scheduler::scheduleByHost(std::string hostName, int quantity)
{
  Host *host = this->hosts.search(hostName);
  if (host == NULL)
  {
    return;
  }

  Url *url;
  int i = 0;

  while (i < quantity && !host->urls.isEmpty())
  {
    url = host->urls.removeAtHead();
    std::cout << url->name << std::endl;
    ++i;
  }
}

void Scheduler::showHost(std::string hostName)
{
  Host *host = this->hosts.search(hostName);
  if (host == NULL)
  {
    return;
  }

  host->urls.index();
}

void Scheduler::indexHosts()
{
  Host *host = this->hosts.front;

  while (host != NULL)
  {
    std::cout << host->name << std::endl;
    host = host->next;
  }
}

void Scheduler::clearHost(std::string hostName)
{
  Host *host = this->hosts.search(hostName);
  if (host == NULL)
  {
    return;
  }

  Url *url;

  while (!host->urls.isEmpty())
  {
    url = host->urls.removeAtHead();
    std::cout << url->name << std::endl;
  }
}
